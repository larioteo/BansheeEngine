//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System;
using System.Collections.Generic;
using BansheeEngine;
 
namespace BansheeEditor
{
    /** @addtogroup Inspector
     *  @{
     */

    /// <summary>
    /// Inspectable field displays GUI elements for a single <see cref="SerializableProperty"/>. This is a base class that
    /// should be specialized for all supported types contained by <see cref="SerializableProperty"/>. Inspectable fields
    /// can and should be created recursively - normally complex types like objects and arrays will contain fields of their 
    /// own, while primitive types like integer or boolean will consist of only a GUI element.
    /// </summary>
    public abstract class InspectableField
    {
        private const int IndentAmount = 5;

        protected Inspector parent;
        protected InspectableFieldLayout layout;
        protected SerializableProperty property;
        protected string title;
        protected string path;
        protected int depth;
        protected SerializableProperty.FieldType type; 

        /// <summary>
        /// Property this field is displaying contents of.
        /// </summary>
        public SerializableProperty Property
        {
            get { return property; }
            set
            {
                if (value == null)
                    throw new ArgumentException("Cannot assign a null property to an inspectable field.");

                if (value.Type != type)
                {
                    throw new ArgumentException(
                        "Attempting to initialize an inspectable field with a property of invalid type.");
                }

                property = value;
            }
        }

        /// <summary>
        /// Creates a new inspectable field GUI for the specified property.
        /// </summary>
        /// <param name="parent">Parent Inspector this field belongs to.</param>
        /// <param name="title">Name of the property, or some other value to set as the title.</param>
        /// <param name="path">Full path to this property (includes name of this property and all parent properties).</param>
        /// <param name="type">Type of property this field will be used for displaying.</param>
        /// <param name="depth">Determines how deep within the inspector nesting hierarchy is this field. Some fields may
        ///                     contain other fields, in which case you should increase this value by one.</param>
        /// <param name="layout">Parent layout that all the field elements will be added to.</param>
        /// <param name="property">Serializable property referencing the array whose contents to display.</param>
        public InspectableField(Inspector parent, string title, string path, SerializableProperty.FieldType type, 
            int depth, InspectableFieldLayout layout, SerializableProperty property)
        {
            this.parent = parent;
            this.layout = layout;
            this.title = title;
            this.path = path;
            this.type = type;
            this.depth = depth;

            Property = property;
        }

        /// <summary>
        /// Checks if contents of the field have been modified, and updates them if needed.
        /// </summary>
        /// <param name="layoutIndex">Index in the parent's layout at which to insert the GUI elements for this field.
        ///                           </param>
        /// <returns>State representing was anything modified between two last calls to <see cref="Refresh"/>.</returns>
        public virtual InspectableState Refresh(int layoutIndex)
        {
            return InspectableState.NotModified;
        }

        /// <summary>
        /// Returns the total number of GUI elements in the field's layout.
        /// </summary>
        /// <returns>Number of GUI elements in the field's layout.</returns>
        public int GetNumLayoutElements()
        {
            return layout.NumElements;
        }

        /// <summary>
        /// Returns an optional title layout. Certain fields may contain separate title and content layouts. Parent fields
        /// may use the separate title layout instead of the content layout to append elements. Having a separate title 
        /// layout is purely cosmetical.
        /// </summary>
        /// <returns>Title layout if the field has one, null otherwise.</returns>
        public virtual GUILayoutX GetTitleLayout()
        {
            return null;
        }

        /// <summary>
        /// Initializes the GUI elements for the field.
        /// </summary>
        /// <param name="layoutIndex">Index at which to insert the GUI elements.</param>
        protected internal abstract void Initialize(int layoutIndex);

        /// <summary>
        /// Destroys all GUI elements in the inspectable field.
        /// </summary>
        public virtual void Destroy()
        {
            layout.DestroyElements();
        }

        /// <summary>
        /// Allows the user to override the default inspector GUI for a specific field in an object. If this method
        /// returns null the default field will be used instead.
        /// </summary>
        /// <param name="field">Field to generate inspector GUI for.</param>
        /// <param name="parent">Parent Inspector the GUI will be rendered on.</param>
        /// <param name="path">Full path to the provided field (includes name of this field and all parent fields).</param>
        /// <param name="layout">Parent layout that all the field elements will be added to.</param>
        /// <param name="layoutIndex">Index into the parent layout at which to insert the GUI elements for the field .</param>
        /// <param name="depth">
        /// Determines how deep within the inspector nesting hierarchy is this field. Some fields may contain other fields,
        /// in which case you should increase this value by one.
        /// </param>
        /// <returns>
        /// Inspectable field implementation that can be used for displaying the GUI for the provided field. Or null if
        /// default field GUI should be used instead.
        /// </returns>
        public delegate InspectableField FieldOverrideCallback(SerializableField field, Inspector parent, string path,
            InspectableFieldLayout layout, int layoutIndex, int depth);

        /// <summary>
        /// Creates inspectable fields all the fields/properties of the specified object.
        /// </summary>
        /// <param name="obj">Object whose fields the GUI will be drawn for.</param>
        /// <param name="parent">Parent Inspector to draw in.</param>
        /// <param name="path">Full path to the field this provided object was retrieved from.</param>
        /// <param name="depth">
        /// Determines how deep within the inspector nesting hierarchy is this objects. Some fields may contain other
        /// fields, in which case you should increase this value by one.
        /// </param>
        /// <param name="layout">Parent layout that all the field GUI elements will be added to.</param>
        /// <param name="overrideCallback">
        /// Optional callback that allows you to override the look of individual fields in the object. If non-null the
        /// callback will be called with information about every field in the provided object. If the callback returns
        /// non-null that inspectable field will be used for drawing the GUI, otherwise the default inspector field type
        /// will be used.
        /// </param>
        public static List<InspectableField> CreateFields(SerializableObject obj, Inspector parent, string path, 
            int depth, GUILayoutY layout, FieldOverrideCallback overrideCallback = null)
        {
            // Retrieve fields and sort by order
            SerializableField[] fields = obj.Fields;
            Array.Sort(fields,
                (x, y) =>
                {
                    int orderX = x.Flags.HasFlag(SerializableFieldAttributes.Order) ? x.Style.Order : 0;
                    int orderY = y.Flags.HasFlag(SerializableFieldAttributes.Order) ? y.Style.Order : 0;

                    return orderX.CompareTo(orderY);
                });

            // Generate per-field GUI while grouping by category
            Dictionary<string, Tuple<int, GUILayoutY>> categories = new Dictionary<string, Tuple<int, GUILayoutY>>();

            int rootIndex = 0;
            List<InspectableField> inspectableFields = new List<InspectableField>();
            foreach (var field in fields)
            {
                if (!field.Flags.HasFlag(SerializableFieldAttributes.Inspectable))
                    continue;

                string category = null;
                if (field.Flags.HasFlag(SerializableFieldAttributes.Category))
                    category = field.Style.CategoryName;

                Tuple<int, GUILayoutY> categoryInfo = null;
                if (!string.IsNullOrEmpty(category))
                {
                    if (!categories.TryGetValue(category, out categoryInfo))
                    {
                        InspectableFieldLayout fieldLayout = new InspectableFieldLayout(layout);
                        GUILayoutY categoryRootLayout = fieldLayout.AddLayoutY(rootIndex);
                        GUILayoutX guiTitleLayout = categoryRootLayout.AddLayoutX();

                        bool isExpanded = parent.Persistent.GetBool(path + "/[" + category + "]_Expanded");

                        GUIToggle guiFoldout = new GUIToggle(category, EditorStyles.Foldout);
                        guiFoldout.Value = isExpanded;
                        guiFoldout.AcceptsKeyFocus = false;
                        guiFoldout.OnToggled += x =>
                        {
                            parent.Persistent.SetBool(path + "/[" + category + "]_Expanded", x);
                        };
                        guiTitleLayout.AddElement(guiFoldout);

                        GUILayoutX categoryContentLayout = categoryRootLayout.AddLayoutX();
                        categoryContentLayout.AddSpace(IndentAmount);

                        GUIPanel guiContentPanel = categoryContentLayout.AddPanel();
                        GUILayoutX guiIndentLayoutX = guiContentPanel.AddLayoutX();
                        guiIndentLayoutX.AddSpace(IndentAmount);
                        GUILayoutY guiIndentLayoutY = guiIndentLayoutX.AddLayoutY();
                        guiIndentLayoutY.AddSpace(IndentAmount);
                        GUILayoutY categoryLayout = guiIndentLayoutY.AddLayoutY();
                        guiIndentLayoutY.AddSpace(IndentAmount);
                        guiIndentLayoutX.AddSpace(IndentAmount);
                        categoryContentLayout.AddSpace(IndentAmount);

                        short backgroundDepth = (short)(Inspector.START_BACKGROUND_DEPTH - depth - 1);
                        string bgPanelStyle = depth % 2 == 0
                            ? EditorStylesInternal.InspectorContentBgAlternate
                            : EditorStylesInternal.InspectorContentBg;
                        GUIPanel backgroundPanel = guiContentPanel.AddPanel(backgroundDepth);
                        GUITexture inspectorContentBg = new GUITexture(null, bgPanelStyle);
                        backgroundPanel.AddElement(inspectorContentBg);

                        categories[category] = new Tuple<int, GUILayoutY>(0, categoryLayout);
                        rootIndex++;
                    }
                }

                int currentIndex;
                GUILayoutY parentLayout;
                if (categoryInfo != null)
                {
                    currentIndex = categoryInfo.Item1;
                    parentLayout = categoryInfo.Item2;
                }
                else
                {
                    currentIndex = rootIndex;
                    parentLayout = layout;
                }

                string fieldName = field.Name;
                string childPath = string.IsNullOrEmpty(path) ? fieldName : path + "/" + fieldName;

                InspectableField inspectableField = null;

                if(overrideCallback != null)
                    inspectableField = overrideCallback(field, parent, path, new InspectableFieldLayout(parentLayout), 
                        currentIndex, depth);

                if (inspectableField == null)
                {
                    inspectableField = CreateField(parent, fieldName, childPath,
                        currentIndex, depth, new InspectableFieldLayout(parentLayout), field.GetProperty(), 
                        InspectableFieldStyle.Create(field));
                }

                inspectableFields.Add(inspectableField);
                currentIndex += inspectableField.GetNumLayoutElements();

                if (categoryInfo != null)
                    categories[category] = new Tuple<int, GUILayoutY>(currentIndex, parentLayout);
                else
                    rootIndex = currentIndex;
            }

            return inspectableFields;
        }

        /// <summary>
        /// Creates a new inspectable field, automatically detecting the most appropriate implementation for the type
        /// contained in the provided serializable property. This may be one of the built-in inspectable field implemetations
        /// (like ones for primitives like int or bool), or a user defined implementation defined with a 
        /// <see cref="CustomInspector"/> attribute.
        /// </summary>
        /// <param name="parent">Parent Inspector this field belongs to.</param>
        /// <param name="title">Name of the property, or some other value to set as the title.</param>
        /// <param name="path">Full path to this property (includes name of this property and all parent properties).</param>
        /// <param name="layoutIndex">Index into the parent layout at which to insert the GUI elements for the field .</param>
        /// <param name="depth">Determines how deep within the inspector nesting hierarchy is this field. Some fields may
        ///                     contain other fields, in which case you should increase this value by one.</param>
        /// <param name="layout">Parent layout that all the field elements will be added to.</param>
        /// <param name="property">Serializable property referencing the array whose contents to display.</param>
        /// <param name="style">Information that can be used for customizing field rendering and behaviour.</param>
        /// <returns>Inspectable field implementation that can be used for displaying the GUI for a serializable property
        ///          of the provided type.</returns>
        public static InspectableField CreateField(Inspector parent, string title, string path, int layoutIndex, 
            int depth, InspectableFieldLayout layout, SerializableProperty property, InspectableFieldStyleInfo style = null)
        {
            InspectableField field = null;

            Type type = property.InternalType;
            if (type.IsGenericType && type.GetGenericTypeDefinition() == typeof(RRef<>))
                type = type.GenericTypeArguments[0];

            Type customInspectable = InspectorUtility.GetCustomInspectable(type);
            if (customInspectable != null)
            {
                field = (InspectableField) Activator.CreateInstance(customInspectable, parent, title, path, depth, layout, 
                    property, style);
            }
            else
            {
                switch (property.Type)
                {
                    case SerializableProperty.FieldType.Int:
                        if (style != null && style.StyleFlags.HasFlag(InspectableFieldStyleFlags.AsLayerMask))
                            field = new InspectableLayerMask(parent, title, path, depth, layout, property);
                        else
                        {
                            if (style?.RangeStyle == null || !style.RangeStyle.Slider)
                                field = new InspectableInt(parent, title, path, depth, layout, property, style);
                            else
                                field = new InspectableRangedInt(parent, title, path, depth, layout, property, style);
                        }

                        break;
                    case SerializableProperty.FieldType.Float:
                        if (style?.RangeStyle == null || !style.RangeStyle.Slider)
                            field = new InspectableFloat(parent, title, path, depth, layout, property, style);
                        else
                            field = new InspectableRangedFloat(parent, title, path, depth, layout, property, style);
                        break;
                    case SerializableProperty.FieldType.Bool:
                        field = new InspectableBool(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Color:
                        field = new InspectableColor(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.ColorGradient:
                        field = new InspectableColorGradient(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Curve:
                        field = new InspectableCurve(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.FloatDistribution:
                        field = new InspectableFloatDistribution(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Vector2Distribution:
                        field = new InspectableVector2Distribution(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Vector3Distribution:
                        field = new InspectableVector3Distribution(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.ColorDistribution:
                        field = new InspectableColorDistribution(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.String:
                        field = new InspectableString(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Vector2:
                        field = new InspectableVector2(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Vector3:
                        field = new InspectableVector3(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Vector4:
                        field = new InspectableVector4(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Quaternion:
                        if (style != null && style.StyleFlags.HasFlag(InspectableFieldStyleFlags.AsQuaternion))
                            field = new InspectableQuaternion(parent, title, path, depth, layout, property);
                        else
                            field = new InspectableEuler(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Resource:
                        field = new InspectableResource(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.RRef:
                        field = new InspectableRRef(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.GameObjectRef:
                        field = new InspectableGameObjectRef(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Object:
                        field = new InspectableObject(parent, title, path, depth, layout, property, style);
                        break;
                    case SerializableProperty.FieldType.Array:
                        field = new InspectableArray(parent, title, path, depth, layout, property, style);
                        break;
                    case SerializableProperty.FieldType.List:
                        field = new InspectableList(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Dictionary:
                        field = new InspectableDictionary(parent, title, path, depth, layout, property);
                        break;
                    case SerializableProperty.FieldType.Enum:
                        field = new InspectableEnum(parent, title, path, depth, layout, property);
                        break;
                }
            }

            if (field == null)
                throw new Exception("No inspector exists for the provided field type.");

            field.Initialize(layoutIndex);
            field.Refresh(layoutIndex);

            return field;
        }
    }

    /** @} */
}
