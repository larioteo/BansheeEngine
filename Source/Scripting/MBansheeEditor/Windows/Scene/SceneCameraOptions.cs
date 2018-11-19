//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using BansheeEngine;

namespace BansheeEditor
{
    /** @addtogroup Scene-Editor
     *  @{
     */

    /// <summary>
    /// Options used by the scene camera.
    /// </summary>
    internal class SceneCameraOptions
    {
        public const float MinScrollSpeed = 0.1f;
        public const float MaxScrollSpeed = 3.0f;
        public const float MinNearClipPlane = 0.0001f;
        public const float MaxNearClipPlane = float.MaxValue;
        public const float MinFarClipPlane = 0.01f;
        public const float MaxFarClipPlane = float.MaxValue;

        public const float StartSpeed = 4.0f;
        public const float TopSpeed = 12.0f;

        public Degree FieldOfView { get; private set; }
        public float OrthographicSize { get; private set; }
        public float Acceleration { get; private set; }
        public float FastModeMultiplier { get; private set; }
        public float PanSpeed { get; private set; }
        public float ScrollSpeed { get; private set; }
        public float RotationalSpeed { get; private set; }
        public float NearClipPlane { get; private set; }
        public float FarClipPlane { get; private set; }

        public SceneCameraOptions()
        {
            FieldOfView = (Degree)ProjectSettings.GetFloat("SceneCameraOptions_FieldOfView", 90.0f);
            OrthographicSize = ProjectSettings.GetFloat("SceneCameraOptions_OrthographicSize", 10.0f);
            Acceleration = ProjectSettings.GetFloat("SceneCameraOptions_Acceleration", 1.0f);
            FastModeMultiplier = ProjectSettings.GetFloat("SceneCameraOptions_FastModeMultiplier", 2.0f);
            PanSpeed = ProjectSettings.GetFloat("SceneCameraOptions_PanSpeed", 3.0f);
            ScrollSpeed = ProjectSettings.GetFloat("SceneCameraOptions_ScrollSpeed", 3.0f);
            RotationalSpeed = ProjectSettings.GetFloat("SceneCameraOptions_RotationalSpeed", 3.0f);

            NearClipPlane = ProjectSettings.GetFloat("SceneCameraOptions_NearClipPlane", 0.05f);
            FarClipPlane = ProjectSettings.GetFloat("SceneCameraOptions_FarClipPlane", 2500f);
        }

        /// <summary>
        /// Sets the orthographic size of the scene camera.
        /// </summary>
        /// <param name="orthographicSize">The orthographic size value.</param>
        public void SetOrthographicSize(float orthographicSize)
        {
            OrthographicSize = orthographicSize;
            ProjectSettings.SetFloat("SceneCameraOptions_OrthographicSize", orthographicSize);
        }

        /// <summary>
        /// Sets the field of view of the scene camera
        /// </summary>
        /// <param name="fieldOfView">The field of view value.</param>
        public void SetFieldOfView(float fieldOfView)
        {
            FieldOfView = (Degree)fieldOfView;
            ProjectSettings.SetFloat("SceneCameraOptions_FieldOfView", fieldOfView);
        }
        
        /// <summary>
        /// Sets the acceleration of the scene camera
        /// </summary>
        /// <param name="acceleration">The acceleration value.</param>
        public void SetAcceleration(float acceleration)
        {
            Acceleration = acceleration;
            ProjectSettings.SetFloat("SceneCameraOptions_Acceleration", acceleration);
        }

        /// <summary>
        /// Sets the fast mode multiplier of the scene camera
        /// </summary>
        /// <param name="fastModeMultiplier">The fast mode multiplier value.</param>
        public void SetFastModeMultiplier(float fastModeMultiplier)
        {
            FastModeMultiplier = fastModeMultiplier;
            ProjectSettings.SetFloat("SceneCameraOptions_FastModeMultiplier", fastModeMultiplier);
        }

        /// <summary>
        /// Sets the pan speed of the scene camera
        /// </summary>
        /// <param name="panSpeed">The pan speed value.</param>
        public void SetPanSpeed(float panSpeed)
        {
            PanSpeed = panSpeed;
            ProjectSettings.SetFloat("SceneCameraOptions_PanSpeed", panSpeed);
        }

        /// <summary>
        /// Sets the scroll speed of the scene camera
        /// </summary>
        /// <param name="scrollSpeed">The scroll speed value.</param>
        public void SetScrollSpeed(float scrollSpeed)
        {
            ScrollSpeed = scrollSpeed;
            ProjectSettings.SetFloat("SceneCameraOptions_ScrollSpeed", scrollSpeed);
        }

        /// <summary>
        /// Sets the rotation speed of the scene camera
        /// </summary>
        /// <param name="rotationalSpeed">The rotation speed  value.</param>
        public void SetRotationalSpeed(float rotationalSpeed)
        {
            RotationalSpeed = rotationalSpeed;
            ProjectSettings.SetFloat("SceneCameraOptions_RotationalSpeed", rotationalSpeed);
        }

        /// <summary>
        /// Sets the near clip plane of the camera
        /// </summary>
        /// <param name="value">The near clip plane value.</param>
        public void SetNearClipPlane(float value)
        {
            value = MathEx.Clamp(value, MinNearClipPlane, MaxNearClipPlane);

            NearClipPlane = value;

            ProjectSettings.SetFloat("SceneCameraOptions_NearClipPlane", value);
        }

        /// <summary>
        /// Sets the far clip plane of the camera
        /// </summary>
        /// <param name="value">The far clip plane value.</param>
        public void SetFarClipPlane(float value)
        {
            value = MathEx.Clamp(value, MinFarClipPlane, MaxFarClipPlane);

            FarClipPlane = value;

            ProjectSettings.SetFloat("SceneCameraOptions_FarClipPlane", value);
        }
    }

    /** @} */
}