//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System;
using BansheeEngine;

namespace BansheeEditor
{
    /** @addtogroup Inspector
     *  @{
     */

    /// <summary>
    /// Displays GUI for a serializable property containing an array. Array contents are displayed as rows of entries 
    /// that can be shown, hidden or manipulated.
    /// </summary>
    public class InspectableArray : InspectableField
    {
        private InspectableArrayGUI arrayGUIField;
        private InspectableFieldStyleInfo style;

        /// <summary>
        /// Style applied to the elements of the array and the array itself.
        /// </summary>
        internal InspectableFieldStyleInfo Style
        {
            get { return style; }
        }

        /// <summary>
        /// Creates a new inspectable array GUI for the specified property.
        /// </summary>
        /// <param name="parent">Parent Inspector this field belongs to.</param>
        /// <param name="title">Name of the property, or some other value to set as the title.</param>
        /// <param name="path">Full path to this property (includes name of this property and all parent properties).</param>
        /// <param name="depth">Determines how deep within the inspector nesting hierarchy is this field. Some fields may
        ///                     contain other fields, in which case you should increase this value by one.</param>
        /// <param name="layout">Parent layout that all the field elements will be added to.</param>
        /// <param name="property">Serializable property referencing the array whose contents to display.</param>
        /// <param name="style">Information that can be used for customizing field rendering and behaviour.</param>
        public InspectableArray(Inspector parent, string title, string path, int depth, InspectableFieldLayout layout, 
            SerializableProperty property, InspectableFieldStyleInfo style)
            : base(parent, title, path, SerializableProperty.FieldType.Array, depth, layout, property)
        {
            this.style = style;
        }

        /// <inheritdoc/>
        public override GUILayoutX GetTitleLayout()
        {
            return arrayGUIField.GetTitleLayout();
        }

        /// <inheritdoc/>
        public override InspectableState Refresh(int layoutIndex)
        {
            return arrayGUIField.Refresh();
        }

        /// <inheritdoc/>
        protected internal override void Initialize(int layoutIndex)
        {
            GUILayout arrayLayout = layout.AddLayoutY(layoutIndex);

            arrayGUIField = InspectableArrayGUI.Create(parent, title, path, property, arrayLayout, depth, style);
            arrayGUIField.IsExpanded = parent.Persistent.GetBool(path + "_Expanded");
            arrayGUIField.OnExpand += x => parent.Persistent.SetBool(path + "_Expanded", x);
        }

        /// <summary>
        /// Handles creation of GUI elements for a GUI list field that displays a <see cref="SerializableArray"/> object.
        /// </summary>
        private class InspectableArrayGUI : GUIListFieldBase
        {
            private Array array;
            private int numElements;
            private Inspector parent;
            private SerializableProperty property;
            private string path;
            private InspectableFieldStyleInfo style;

            /// <summary>
            /// Returns the parent inspector the array GUI belongs to.
            /// </summary>
            public Inspector Inspector
            {
                get { return parent; }
            }

            /// <summary>
            /// Returns a property path to the array field (name of the array field and all parent object fields).
            /// </summary>
            public string Path
            {
                get { return path; }
            }

            /// <summary>
            /// Style applied to the elements of the array and the array itself.
            /// </summary>
            public InspectableFieldStyleInfo Style
            {
                get { return style; }
            }

            /// <summary>
            /// Constructs a new inspectable array GUI.
            /// </summary>
            /// <param name="parent">Parent Inspector this field belongs to.</param>
            /// <param name="title">Label to display on the list GUI title.</param>
            /// <param name="path">Full path to this property (includes name of this property and all parent properties).
            /// </param>
            /// <param name="property">Serializable property referencing a single-dimensional array.</param>
            /// <param name="layout">Layout to which to append the list GUI elements to.</param>
            /// <param name="depth">Determines at which depth to render the background. Useful when you have multiple
            ///                     nested containers whose backgrounds are overlaping. Also determines background style,
            ///                     depths divisible by two will use an alternate style.</param>
            /// <param name="style">Information that can be used for customizing field rendering and behaviour.</param>
            public InspectableArrayGUI(Inspector parent, LocString title, string path, SerializableProperty property, 
                GUILayout layout, int depth, InspectableFieldStyleInfo style)
                : base(title, layout, depth)
            {
                this.property = property;
                this.parent = parent;
                this.path = path;
                this.style = style;

                array = property.GetValue<Array>();
                if (array != null)
                    numElements = array.Length;
            }

            /// <summary>
            /// Creates a new inspectable array GUI object that displays the contents of the provided serializable property.
            /// </summary>
            /// <param name="parent">Parent Inspector this field belongs to.</param>
            /// <param name="title">Label to display on the list GUI title.</param>
            /// <param name="path">Full path to this property (includes name of this property and all parent properties).
            /// </param>
            /// <param name="property">Serializable property referencing a single-dimensional array.</param>
            /// <param name="layout">Layout to which to append the list GUI elements to.</param>
            /// <param name="depth">Determines at which depth to render the background. Useful when you have multiple
            ///                     nested containers whose backgrounds are overlaping. Also determines background style,
            ///                     depths divisible by two will use an alternate style.</param>
            /// <param name="style">Information that can be used for customizing field rendering and behaviour.</param>
            public static InspectableArrayGUI Create(Inspector parent, LocString title, string path, 
                SerializableProperty property, GUILayout layout, int depth, InspectableFieldStyleInfo style)
            {
                InspectableArrayGUI guiArray = new InspectableArrayGUI(parent, title, path, property, layout, depth, style);
                guiArray.BuildGUI();
                
                return guiArray;
            }

            /// <inheritdoc/>
            public override InspectableState Refresh()
            {
                // Check if any modifications to the array were made outside the inspector
                Array newArray = property.GetValue<Array>();
                if (array == null && newArray != null)
                {
                    array = newArray;
                    numElements = array.Length;
                    BuildGUI();
                }
                else if (newArray == null && array != null)
                {
                    array = null;
                    numElements = 0;
                    BuildGUI();
                }
                else
                {
                    if (array != null)
                    {
                        if (numElements != array.Length)
                        {
                            numElements = array.Length;
                            BuildGUI();
                        }
                    }
                }

                return base.Refresh();
            }

            /// <inheritdoc/>
            protected override GUIListFieldRow CreateRow()
            {
                return new InspectableArrayGUIRow();
            }

            /// <inheritdoc/>
            protected override bool IsNull()
            {
                return array == null;
            }

            /// <inheritdoc/>
            protected override int GetNumRows()
            {
                if (array != null)
                    return array.Length;

                return 0;
            }

            /// <inheritdoc/>
            protected internal override object GetValue(int seqIndex)
            {
                SerializableArray serzArray = property.GetArray();

                // Create a property wrapper for native arrays so we get notified when the array values change
                if (style.StyleFlags.HasFlag(InspectableFieldStyleFlags.NativeWrapper))
                {
                    SerializableProperty.Getter getter = () =>
                    {
                        Array array = property.GetValue<Array>();

                        if (array != null)
                            return array.GetValue(seqIndex);
                        else
                            return null;
                    };

                    SerializableProperty.Setter setter = (object value) =>
                    {
                        Array array = property.GetValue<Array>();

                        if (array != null)
                        {
                            array.SetValue(value, seqIndex);
                            property.SetValue(array);
                        }
                    };

                    return new SerializableProperty(serzArray.ElementPropertyType, serzArray.ElementType, getter, setter);
                }
                else
                    return serzArray.GetProperty(seqIndex);
            }

            /// <inheritdoc/>
            protected internal override void SetValue(int seqIndex, object value)
            {
                // Setting the value should be done through the property
                throw new InvalidOperationException();
            }

            /// <inheritdoc/>
            protected override void CreateList()
            {
                array = property.CreateArrayInstance(new int[1] { 0 });
                property.SetValue(array);
                numElements = 0;
            }

            /// <inheritdoc/>
            protected override void ResizeList()
            {
                int size = guiSizeField.Value; // TODO - Support multi-rank arrays

                Array newArray = property.CreateArrayInstance(new int[] { size });
                int maxSize = MathEx.Min(size, array.Length);

                for (int i = 0; i < maxSize; i++)
                    newArray.SetValue(array.GetValue(i), i);

                property.SetValue(newArray);
                array = newArray;
                numElements = size;
            }

            /// <inheritdoc/>
            protected override void ClearList()
            {
                // Native arrays cannot be set to null, so just clear their size to zero instead
                if (style.StyleFlags.HasFlag(InspectableFieldStyleFlags.NativeWrapper))
                    CreateList();
                else
                {
                    property.SetValue<object>(null);
                    array = null;
                    numElements = 0;
                }
            }

            /// <inheritdoc/>
            protected internal override void DeleteElement(int index)
            {
                int size = MathEx.Max(0, array.Length - 1);
                Array newArray = property.CreateArrayInstance(new int[] { size });

                int destIdx = 0;
                for (int i = 0; i < array.Length; i++)
                {
                    if (i == index)
                        continue;

                    newArray.SetValue(array.GetValue(i), destIdx);
                    destIdx++;
                }

                property.SetValue(newArray);
                array = newArray;
                numElements = array.Length;
            }

            /// <inheritdoc/>
            protected internal override void CloneElement(int index)
            {
                SerializableArray array = property.GetArray();

                int size = array.GetLength() + 1;
                Array newArray = property.CreateArrayInstance(new int[] { size });

                object clonedEntry = null;
                for (int i = 0; i < array.GetLength(); i++)
                {
                    object value = array.GetProperty(i).GetValue<object>();

                    newArray.SetValue(value, i);

                    if (i == index)
                    {
                        clonedEntry = SerializableUtility.Clone(array.GetProperty(i).GetValue<object>());
                    }
                }

                newArray.SetValue(clonedEntry, size - 1);

                property.SetValue(newArray);
                this.array = newArray;
                numElements = newArray.Length;
            }

            /// <inheritdoc/>
            protected internal override void MoveUpElement(int index)
            {
                if ((index - 1) >= 0)
                {
                    object previousEntry = array.GetValue(index - 1);

                    array.SetValue(array.GetValue(index), index - 1);
                    array.SetValue(previousEntry, index);

                    // Natively wrapped arrays are passed by copy
                    if(style.StyleFlags.HasFlag(InspectableFieldStyleFlags.NativeWrapper))
                        property.SetValue(array);
                }
            }

            /// <inheritdoc/>
            protected internal override void MoveDownElement(int index)
            {
                if ((index + 1) < array.Length)
                {
                    object nextEntry = array.GetValue(index + 1);

                    array.SetValue(array.GetValue(index), index + 1);
                    array.SetValue(nextEntry, index);

                    // Natively wrapped arrays are passed by copy
                    if(style.StyleFlags.HasFlag(InspectableFieldStyleFlags.NativeWrapper))
                        property.SetValue(array);
                }
            }
        }

        /// <summary>
        /// Contains GUI elements for a single entry in the array.
        /// </summary>
        private class InspectableArrayGUIRow : GUIListFieldRow
        {
            private InspectableField field;

            /// <inheritdoc/>
            protected override GUILayoutX CreateGUI(GUILayoutY layout)
            {
                InspectableArrayGUI arrayParent = (InspectableArrayGUI)parent;
                SerializableProperty property = GetValue<SerializableProperty>();

                InspectableFieldStyleInfo styleInfo = arrayParent.Style.Clone();
                styleInfo.StyleFlags &= ~InspectableFieldStyleFlags.NativeWrapper;

                string entryPath = arrayParent.Path + "[" + SeqIndex + "]";
                field = CreateField(arrayParent.Inspector, SeqIndex + ".", entryPath, 0, Depth + 1,
                    new InspectableFieldLayout(layout), property, styleInfo);

                return field.GetTitleLayout();
            }

            /// <inheritdoc/>
            protected internal override InspectableState Refresh()
            {
                field.Property = GetValue<SerializableProperty>();
                return field.Refresh(0);
            }
        }
    }

    /** @} */
}
