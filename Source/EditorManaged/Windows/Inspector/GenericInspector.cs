//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System.Collections.Generic;
using bs;

namespace bs.Editor
{
    /** @addtogroup Inspector
     *  @{
     */

    /// <summary>
    /// Default implementation of the inspector used when no specified inspector is provided for the type. Inspector 
    /// displays GUI for all the inspectable fields in the object.
    /// </summary>
    internal sealed class GenericInspector : Inspector
    {
        private bool isEmpty = true;
        private GenericInspectorDrawer drawer;

        /// <inheritdoc/>
        protected internal override void Initialize()
        {
            if (InspectedObject == null)
                LoadResource();

            drawer = new GenericInspectorDrawer(InspectedObject, new InspectableContext(Persistent), Layout);

            isEmpty = drawer.Fields.Count == 0;
            base.SetVisible(!isEmpty);
        }

        /// <inheritdoc/>
        protected internal override InspectableState Refresh()
        {
            return drawer.Refresh();
        }

        /// <inheritdoc/>
        internal override void SetVisible(bool visible)
        {
            base.SetVisible(!isEmpty && visible);
        }
    }

    /// <summary>
    /// Helper class that draws the default inspector elements for an object, with an optional callback to render custom
    /// inspectors for certain types.
    /// </summary>
    internal sealed class GenericInspectorDrawer
    {
        /// <summary>
        /// List of fields created and updated by the drawer.
        /// </summary>
        public List<InspectableField> Fields { get; } = new List<InspectableField>();

        /// <summary>
        /// Creates new generic inspector field drawer for the specified object.
        /// </summary>
        /// <param name="obj">Object whose fields to create the GUI for.</param>
        /// <param name="context">Context shared by all inspectable fields created by the same parent.</param>
        /// <param name="layout">Parent layout that all the field GUI elements will be added to.</param>
        /// <param name="overrideCallback">
        /// Optional callback that allows you to override the look of individual fields in the object. If non-null the
        /// callback will be called with information about every field in the provided object. If the callback returns
        /// non-null that inspectable field will be used for drawing the GUI, otherwise the default inspector field type
        /// will be used.
        /// </param>
        public GenericInspectorDrawer(object obj, InspectableContext context, GUILayoutY layout, 
            InspectableField.FieldOverrideCallback overrideCallback = null)
        {
            if (obj == null)
                return;

            SerializableObject serializableObject = new SerializableObject(obj.GetType(), obj);
            Fields = InspectableField.CreateFields(serializableObject, context, "", 0, layout, overrideCallback);
        }

        /// <summary>
        /// Checks if contents of the inspector fields have been modified, and updates them if needed.
        /// </summary>
        /// <returns>State representing was anything modified between two last calls to <see cref="Refresh"/>.</returns>
        public InspectableState Refresh()
        {
            InspectableState state = InspectableState.NotModified;

            int currentIndex = 0;
            foreach (var field in Fields)
            {
                state |= field.Refresh(currentIndex);
                currentIndex += field.GetNumLayoutElements();
            }

            return state;
        }
    }

    /** @} */
}
