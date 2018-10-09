//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using BansheeEngine;

namespace BansheeEditor
{
    /** @addtogroup Inspector
     *  @{
     */

    /// <summary>
    /// Displays GUI for a serializable property containing a <see cref="Resource"/> reference.
    /// </summary>
    public class InspectableRRef : InspectableField
    {
        private GUIResourceField guiField;
        private InspectableState state;

        /// <summary>
        /// Creates a new inspectable resource reference GUI for the specified property.
        /// </summary>
        /// <param name="parent">Parent Inspector this field belongs to.</param>
        /// <param name="title">Name of the property, or some other value to set as the title.</param>
        /// <param name="path">Full path to this property (includes name of this property and all parent properties).</param>
        /// <param name="depth">Determines how deep within the inspector nesting hierarchy is this field. Some fields may
        ///                     contain other fields, in which case you should increase this value by one.</param>
        /// <param name="layout">Parent layout that all the field elements will be added to.</param>
        /// <param name="property">Serializable property referencing the field whose contents to display.</param>
        public InspectableRRef(Inspector parent, string title, string path, int depth, InspectableFieldLayout layout,
            SerializableProperty property)
            : base(parent, title, path, SerializableProperty.FieldType.RRef, depth, layout, property)
        {

        }

        /// <inheritoc/>
        protected internal override void Initialize(int layoutIndex)
        {
            if (property.Type == SerializableProperty.FieldType.RRef)
            {
                System.Type type = property.InternalType;
                if (type.IsGenericType && type.GetGenericTypeDefinition() == typeof(RRef<>))
                    type = type.GenericTypeArguments[0];

                guiField = new GUIResourceField(type, new GUIContent(title));
                guiField.OnChanged += OnFieldValueChanged;

                layout.AddElement(layoutIndex, guiField);
            }
        }

        /// <inheritdoc/>
        public override InspectableState Refresh(int layoutIndex)
        {
            if (guiField != null)
                guiField.ValueRef = property.GetValue<RRefBase>();

            InspectableState oldState = state;
            if (state.HasFlag(InspectableState.Modified))
                state = InspectableState.NotModified;

            return oldState;
        }

        /// <summary>
        /// Triggered when the user drops a new resource onto the field, or clears the current value.
        /// </summary>
        /// <param name="newValue">New resource to reference.</param>
        private void OnFieldValueChanged(RRefBase newValue)
        {
            property.SetValue(newValue);
            state = InspectableState.Modified;
        }
    }

    /** @} */
}
