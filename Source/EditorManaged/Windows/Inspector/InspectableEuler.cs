//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2019 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using BansheeEngine;

namespace BansheeEditor
{
    /** @addtogroup Inspector
     *  @{
     */

    /// <summary>
    /// Displays GUI for a serializable property containing a quaternion, displayed as euler angles.
    /// </summary>
    public class InspectableEuler : InspectableField
    {
        private GUIVector3Field guiField;
        private InspectableState state;

        private Quaternion quatValue = Quaternion.Identity;

        /// <summary>
        /// Creates a new inspectable euler angle GUI for the specified property.
        /// </summary>
        /// <param name="parent">Parent Inspector this field belongs to.</param>
        /// <param name="title">Name of the property, or some other value to set as the title.</param>
        /// <param name="path">Full path to this property (includes name of this property and all parent properties).</param>
        /// <param name="depth">Determines how deep within the inspector nesting hierarchy is this field. Some fields may
        ///                     contain other fields, in which case you should increase this value by one.</param>
        /// <param name="layout">Parent layout that all the field elements will be added to.</param>
        /// <param name="property">Serializable property referencing the field whose contents to display.</param>
        public InspectableEuler(Inspector parent, string title, string path, int depth, InspectableFieldLayout layout,
            SerializableProperty property)
            : base(parent, title, path, SerializableProperty.FieldType.Quaternion, depth, layout, property)
        {

        }

        /// <inheritoc/>
        protected internal override void Initialize(int layoutIndex)
        {
            if (property.Type == SerializableProperty.FieldType.Quaternion)
            {
                guiField = new GUIVector3Field(new GUIContent(title));
                guiField.Value = quatValue.ToEuler();

                guiField.OnChanged += OnFieldValueChanged;
                guiField.OnConfirmed += OnFieldValueConfirm;
                guiField.OnFocusLost += OnFieldValueConfirm;

                layout.AddElement(layoutIndex, guiField);
            }
        }

        /// <inheritdoc/>
        public override InspectableState Refresh(int layoutIndex)
        {
            if (guiField != null && !guiField.HasInputFocus)
            {
                Quaternion quaternion = property.GetValue<Quaternion>();
                if (quaternion != quatValue)
                {
                    guiField.Value = quaternion.ToEuler();
                    quatValue = quaternion;
                }
            }

            InspectableState oldState = state;
            if (state.HasFlag(InspectableState.Modified))
                state = InspectableState.NotModified;

            return oldState;
        }

        /// <summary>
        /// Triggered when the user changes the field value.
        /// </summary>
        /// <param name="newValue">New value of the 3D vector field.</param>
        private void OnFieldValueChanged(Vector3 newValue)
        {
            quatValue = Quaternion.FromEuler(newValue);

            property.SetValue(quatValue);
            state |= InspectableState.ModifyInProgress;
        }

        /// <summary>
        /// Triggered when the user confirms input in the 3D vector field.
        /// </summary>
        private void OnFieldValueConfirm()
        {
            if (state.HasFlag(InspectableState.ModifyInProgress))
                state |= InspectableState.Modified;
        }
    }

    /** @} */
}
