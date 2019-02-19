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
    /// Displays GUI elements for all the inspectable fields in an object.
    /// </summary>
    public abstract class Inspector
    {
        public const short START_BACKGROUND_DEPTH = 50;

        /// <summary>
        /// Returns the main GUI layout for the inspector.
        /// </summary>
        protected GUILayoutY Layout
        {
            get { return layout; }
        }

        /// <summary>
        /// Returns the main GUI panel for the inspector. <see cref="Layout"/> is a child of this panel.
        /// </summary>
        protected GUIPanel GUI
        {
            get { return mainPanel; }
        }

        /// <summary>
        /// Returns the secondary GUI panel. Located at the bottom of the inspector window and unlike <see cref="GUI"/> has
        /// no padding or styling applied. Only available when inspecting resources.
        /// </summary>
        protected GUIPanel PreviewGUI
        {
            get { return previewPanel; }
        }

        /// <summary>
        /// Returns the object the inspector is currently displaying. If the current object is a resource use
        /// <see cref="InspectedResourcePath"/> instead;
        /// </summary>
        protected object InspectedObject
        {
            get { return inspectedObject; }
        }

        /// <summary>
        /// Returns the path to the resource the inspector is currently displaying.
        /// </summary>
        protected string InspectedResourcePath
        {
            get { return inspectedResourcePath; }
        }

        /// <summary>
        /// A set of properties that the inspector can read/write. They will be persisted even after the inspector is closed
        /// and restored when it is re-opened.
        /// </summary>
        protected internal SerializableProperties Persistent
        {
            get { return persistent; }
        }

        private GUIPanel rootGUI;
        private GUIPanel mainPanel;
        private GUIPanel previewPanel;
        private GUILayoutY layout;
        private object inspectedObject;
        private string inspectedResourcePath;
        private SerializableProperties persistent;

        /// <summary>
        /// Common code called by both Initialize() overloads.
        /// </summary>
        /// <param name="mainGui">Primary GUI panel to add the GUI elements to.</param>
        /// <param name="previewGui">Secondary GUI panel located at the bottom of the inspector window, aimed primarily for
        /// resource previews, but can be used for any purpose.</param>
        /// <param name="persistent">A set of properties that the inspector can read/write. They will be persisted even 
        ///                          after the inspector is closed and restored when it is re-opened.</param>
        private void InitializeBase(GUIPanel mainGui, GUIPanel previewGui, SerializableProperties persistent)
        {
            rootGUI = mainGui;
            this.persistent = persistent;

            GUILayout contentLayoutX = mainGui.AddLayoutX();
            contentLayoutX.AddSpace(5);
            GUILayout contentLayoutY = contentLayoutX.AddLayoutY();
            contentLayoutY.AddSpace(5);
            GUIPanel contentPanel = contentLayoutY.AddPanel();
            contentLayoutY.AddSpace(5);
            contentLayoutX.AddSpace(5);

            GUIPanel backgroundPanel = mainGui.AddPanel(START_BACKGROUND_DEPTH);
            GUITexture inspectorContentBg = new GUITexture(null, EditorStylesInternal.InspectorContentBg);
            backgroundPanel.AddElement(inspectorContentBg);

            mainPanel = contentPanel;
            previewPanel = previewGui;
            layout = GUI.AddLayoutY();
        }

        /// <summary>
        /// Initializes the inspector using an object instance. Must be called after construction.
        /// </summary>
        /// <param name="gui">GUI panel to add the GUI elements to.</param>
        /// <param name="instance">Instance of the object whose fields to display GUI for.</param>
        /// <param name="persistent">A set of properties that the inspector can read/write. They will be persisted even 
        ///                          after the inspector is closed and restored when it is re-opened.</param>
        internal virtual void Initialize(GUIPanel gui, object instance, SerializableProperties persistent)
        {
            InitializeBase(gui, null, persistent);

            inspectedObject = instance;

            Initialize();
            Refresh();
        }

        /// <summary>
        /// Initializes the inspector using a resource path. Must be called after construction.
        /// </summary>
        /// <param name="mainGui">Primary GUI panel to add the GUI elements to.</param>
        /// <param name="previewGui">Secondary GUI panel located at the bottom of the inspector window, aimed primarily for
        /// resource previews, but can be used for any purpose.</param>
        /// <param name="path">Path to the resource for which to display GUI for.</param>
        /// <param name="persistent">A set of properties that the inspector can read/write. They will be persisted even 
        ///                          after the inspector is closed and restored when it is re-opened.</param>
        internal virtual void Initialize(GUIPanel mainGui, GUIPanel previewGui, string path, 
            SerializableProperties persistent)
        {
            InitializeBase(mainGui, previewGui, persistent);

            inspectedResourcePath = path;

            Initialize();
            Refresh();
        }

        /// <summary>
        /// Loads the currently inspected resource into the <see cref="InspectedObject"/> field. By default resources
        /// are not loaded and you can only retrieve their path through <see cref="InspectedResourcePath"/>.
        /// </summary>
        protected void LoadResource()
        {
            if(!string.IsNullOrEmpty(inspectedResourcePath))
                inspectedObject = ProjectLibrary.Load<Resource>(inspectedResourcePath);
        }

        /// <summary>
        /// Hides or shows the inspector GUI elements.
        /// </summary>
        /// <param name="visible">True to make the GUI elements visible.</param>
        internal virtual void SetVisible(bool visible)
        {
            rootGUI.Active = visible;
        }
        
        /// <summary>
        /// Destroys all inspector GUI elements.
        /// </summary>
        internal void Destroy()
        {
            Layout.Destroy();
            GUI.Destroy();
        }

        /// <summary>
        /// Called when the inspector is first created.
        /// </summary>
        protected internal abstract void Initialize();

        /// <summary>
        /// Checks if contents of the inspector have been modified, and updates them if needed.
        /// </summary>
        /// <returns>State representing was anything modified between two last calls to <see cref="Refresh"/>.</returns>
        protected internal abstract InspectableState Refresh();
    }

    /** @} */
}
