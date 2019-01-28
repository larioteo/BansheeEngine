//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2018 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using BansheeEngine;

namespace BansheeEditor
{
    /** @addtogroup Inspector
     *  @{
     */

    /// <summary>
    /// Displays GUI for a serializable property containing a 2D vector distribution. GUI elements will switch between
    /// vector and curve input depending on the distribution type. 
    /// </summary>
    public class InspectableVector2Distribution : InspectableField
    {
        private GUIVector2DistributionField guiDistributionField;
        private InspectableState state;

        /// <summary>
        /// Creates a new inspectable 2D vector distribution GUI for the specified property.
        /// </summary>
        /// <param name="parent">Parent Inspector this field belongs to.</param>
        /// <param name="title">Name of the property, or some other value to set as the title.</param>
        /// <param name="path">Full path to this property (includes name of this property and all parent properties).</param>
        /// <param name="depth">Determines how deep within the inspector nesting hierarchy is this field. Some fields may
        ///                     contain other fields, in which case you should increase this value by one.</param>
        /// <param name="layout">Parent layout that all the field elements will be added to.</param>
        /// <param name="property">Serializable property referencing the field whose contents to display.</param>
        public InspectableVector2Distribution(Inspector parent, string title, string path, int depth, 
            InspectableFieldLayout layout, SerializableProperty property)
            : base(parent, title, path, SerializableProperty.FieldType.Vector2Distribution, depth, layout, property)
        { }

        /// <inheritoc/>
        protected internal override void Initialize(int layoutIndex)
        {
            if (property != null)
            {
                guiDistributionField = new GUIVector2DistributionField(new GUIContent(title));
                guiDistributionField.OnChanged += OnFieldValueChanged;
                guiDistributionField.OnConfirmed += OnFieldValueConfirm;
                guiDistributionField.OnFocusLost += OnFieldValueConfirm;

                layout.AddElement(layoutIndex, guiDistributionField);
            }
        }

        /// <inheritdoc/>
        public override InspectableState Refresh(int layoutIndex)
        {
            if (guiDistributionField != null && !guiDistributionField.HasInputFocus)
                guiDistributionField.Value = property.GetValue<Vector2Distribution>();

            InspectableState oldState = state;
            if (state.HasFlag(InspectableState.Modified))
                state = InspectableState.NotModified;

            return oldState;
        }

        /// <summary>
        /// Triggered when the user edits the distribution.
        /// </summary>
        private void OnFieldValueChanged()
        {
            property.SetValue(guiDistributionField.Value);
            state |= InspectableState.ModifyInProgress;
        }

        /// <summary>
        /// Triggered when the user confirms input in the float fields used for displaying the non-curve distribution.
        /// </summary>
        private void OnFieldValueConfirm()
        {
            if (state.HasFlag(InspectableState.ModifyInProgress))
                state |= InspectableState.Modified;
        }
    }

    /** @} */
}