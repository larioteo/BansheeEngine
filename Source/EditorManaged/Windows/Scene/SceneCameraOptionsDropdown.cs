//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using BansheeEngine;
using System;

namespace BansheeEditor
{
    /** @addtogroup Scene-Editor
     *  @{
     */

    /// <summary>
    /// Drop down window that displays options used by the scene camera.
    /// </summary>
    [DefaultSize(350, 150)]
    internal class SceneCameraOptionsDropdown : DropDownWindow
    {
        private SceneWindow Parent;

        private GUIFloatField nearClipPlaneInput;
        private GUIFloatField farClipPlaneInput;
        private GUIFloatField cameraOrthographicSize;
        private GUISliderField cameraFieldOfView;

        /// <summary>
        /// Initializes the drop down window by creating the necessary GUI. Must be called after construction and before
        /// use.
        /// </summary>
        /// <param name="parent">Scene window that this drop down window is a part of.</param>
        /// <param name="cameraOptions">Reference to the current scene camera options.</param>
        internal void Initialize(SceneWindow parent)
        {
            this.Parent = parent;

            GUIEnumField cameraProjectionTypeField = new GUIEnumField(typeof(ProjectionType), new LocEdString("Projection type"));
            cameraProjectionTypeField.Value = (ulong)Parent.ProjectionType;
            cameraProjectionTypeField.OnSelectionChanged += SetCameraProjectionType;

            nearClipPlaneInput = new GUIFloatField(new LocEdString("Near plane"));
            nearClipPlaneInput.Value = Parent.NearClipPlane;
            nearClipPlaneInput.OnChanged += OnNearClipPlaneChanged;
            nearClipPlaneInput.SetRange(SceneCameraOptions.MinNearClipPlane, SceneCameraOptions.MaxNearClipPlane);

            farClipPlaneInput = new GUIFloatField(new LocEdString("Far plane"));
            farClipPlaneInput.Value = Parent.FarClipPlane;
            farClipPlaneInput.OnChanged += OnFarClipPlaneChanged;
            farClipPlaneInput.SetRange(SceneCameraOptions.MinFarClipPlane, SceneCameraOptions.MaxFarClipPlane);

            cameraFieldOfView = new GUISliderField(1, 360, new LocEdString("Field of view"));
            cameraFieldOfView.Value = Parent.FieldOfView.Degrees;
            cameraFieldOfView.OnChanged += SetFieldOfView;

            cameraOrthographicSize = new GUIFloatField(new LocEdString("Orthographic size"));
            cameraOrthographicSize.Value = Parent.OrthographicSize;
            cameraOrthographicSize.OnChanged += SetOrthographicSize;

            GUISliderField cameraScrollSpeed = new GUISliderField(SceneCameraOptions.MinScrollSpeed, SceneCameraOptions.MaxScrollSpeed, 
                new LocEdString("Scroll speed"));
            cameraScrollSpeed.Value = Parent.ScrollSpeed;
            cameraScrollSpeed.OnChanged += SetScrollSpeed;

            GUILayoutY vertLayout = GUI.AddLayoutY();
            vertLayout.AddSpace(10);

            GUILayoutX cameraOptionsLayoutX = vertLayout.AddLayoutX();
            cameraOptionsLayoutX.AddSpace(10);

            GUILayoutY cameraOptionsLayoutY = cameraOptionsLayoutX.AddLayoutY();
            cameraOptionsLayoutY.AddElement(cameraProjectionTypeField);
            cameraOptionsLayoutY.AddElement(nearClipPlaneInput);
            cameraOptionsLayoutY.AddElement(farClipPlaneInput);
            cameraOptionsLayoutY.AddElement(cameraFieldOfView);
            cameraOptionsLayoutY.AddElement(cameraOrthographicSize);
            cameraOptionsLayoutY.AddElement(cameraScrollSpeed);
            cameraOptionsLayoutX.AddSpace(10);

            vertLayout.AddSpace(10);

            ToggleTypeSpecificFields((ProjectionType)cameraProjectionTypeField.Value);
        }

        private void SetOrthographicSize(float value)
        {
            if (Parent.ProjectionType != ProjectionType.Orthographic)
                return;
            Parent.OrthographicSize = value;
        }

        private void SetFieldOfView(float value)
        {
            if (Parent.ProjectionType != ProjectionType.Perspective)
                return;
            Parent.FieldOfView = (Degree)value;
        }

        /// <summary>
        /// Sets the value of the scene camera scroll speed.
        /// </summary>
        /// <param name="value">The scroll speed value.</param>
        private void SetScrollSpeed(float value)
        {
            Parent.ScrollSpeed = value;
        }

        private void ToggleTypeSpecificFields(ProjectionType projectionType)
        {
            cameraFieldOfView.Active = projectionType == ProjectionType.Perspective;
            cameraOrthographicSize.Active = projectionType == ProjectionType.Orthographic;
        }

        private void SetCameraProjectionType(ulong projectionType)
        {
            Parent.ProjectionType = (ProjectionType)projectionType;

            ToggleTypeSpecificFields((ProjectionType)projectionType);
        }

        private void OnNearClipPlaneChanged(float value)
        {
            Parent.NearClipPlane = value;
        }

        private void OnFarClipPlaneChanged(float value)
        {
            Parent.FarClipPlane = value;
        }
    }
}