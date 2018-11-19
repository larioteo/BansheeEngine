//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using BansheeEngine;
using System.Linq;

namespace BansheeEditor
{
    /** @addtogroup Scene-Editor
     *  @{
     */

    /// <summary>
    /// Drop down window that displays options used by the scene camera.
    /// </summary>
    [DefaultSize(200, 30)]
    internal class SceneCameraOptionsDropdown : DropDownWindow
    {

        private SceneWindow parent;

        private SceneCameraOptions CameraOptions;

        /// <summary>
        /// Initializes the drop down window by creating the necessary GUI. Must be called after construction and before
        /// use.
        /// </summary>
        /// <param name="parent">Scene window that this drop down window is a part of.</param>
        /// <param name="cameraOptions">Reference to the current scene camera options.</param>
        internal void Initialize(SceneWindow parent, SceneCameraOptions cameraOptions)
        {
            this.parent = parent;
            CameraOptions = cameraOptions;

            GUIListBoxField cameraScrollSpeedField = new GUIListBoxField(SceneCameraOptions.ScrollSpeeds.ToList().Select(o => o.ToString()).ToArray(),
                new LocEdString("Scroll speed"));

            cameraScrollSpeedField.SelectElement(SceneCameraOptions.ScrollSpeeds.ToList().FindIndex(item => item == CameraOptions.ScrollSpeed));

            cameraScrollSpeedField.OnSelectionChanged += OnCameraScrollSpeedChanged;

            GUILayoutY vertLayout = GUI.AddLayoutY();
            vertLayout.AddFlexibleSpace();
            GUILayoutX cameraScrollSpeedLayout = vertLayout.AddLayoutX();
            cameraScrollSpeedLayout.AddFlexibleSpace();
            cameraScrollSpeedLayout.AddElement(cameraScrollSpeedField);
            cameraScrollSpeedLayout.AddFlexibleSpace();
            vertLayout.AddFlexibleSpace();
        }

        /// <summary>
        /// Triggered when the scroll speed of the scene camera is changed.
        /// </summary>
        /// <param name="index">The index of the selected scroll speed.</param>
        private void OnCameraScrollSpeedChanged(int index)
        {
            CameraOptions.SetScrollSpeed(SceneCameraOptions.ScrollSpeeds[index]);
        }
    }
}