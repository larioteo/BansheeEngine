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
        public static float[] ScrollSpeeds
        {
            get => new float[]
            {
                0.1f,
                0.25f,
                0.5f,
                0.75f,
                1f,
                1.5f,
                2f,
                3f
            };
        }

        public const float StartSpeed = 4.0f;
        public const float TopSpeed = 12.0f;
        public readonly Degree FieldOfView = (Degree)90.0f;

        public float Acceleration { get; private set; }
        public float FastModeMultiplier { get; private set; }
        public float PanSpeed { get; private set; }
        public float ScrollSpeed { get; private set; }
        public float RotationalSpeed { get; private set; }

        public SceneCameraOptions()
        {
            Acceleration = EditorSettings.GetFloat("SceneCameraOptions_Acceleration", 1.0f);
            FastModeMultiplier = EditorSettings.GetFloat("SceneCameraOptions_FastModeMultiplier", 2.0f);
            PanSpeed = EditorSettings.GetFloat("SceneCameraOptions_PanSpeed", 3.0f);
            ScrollSpeed = EditorSettings.GetFloat("SceneCameraOptions_ScrollSpeed", 3.0f);
            RotationalSpeed = EditorSettings.GetFloat("SceneCameraOptions_RotationalSpeed", 3.0f);
        }

        /// <summary>
        /// Sets the acceleration of the scene camera
        /// </summary>
        /// <param name="acceleration">The acceleration value.</param>
        public void SetAcceleration(float acceleration)
        {
            Acceleration = acceleration;
            EditorSettings.SetFloat("SceneCameraOptions_Acceleration", acceleration);
        }

        /// <summary>
        /// Sets the fast mode multiplier of the scene camera
        /// </summary>
        /// <param name="fastModeMultiplier">The fast mode multiplier value.</param>
        public void SetFastModeMultiplier(float fastModeMultiplier)
        {
            FastModeMultiplier = fastModeMultiplier;
            EditorSettings.SetFloat("SceneCameraOptions_FastModeMultiplier", fastModeMultiplier);
        }

        /// <summary>
        /// Sets the pan speed of the scene camera
        /// </summary>
        /// <param name="panSpeed">The pan speed value.</param>
        public void SetPanSpeed(float panSpeed)
        {
            PanSpeed = panSpeed;
            EditorSettings.SetFloat("SceneCameraOptions_PanSpeed", panSpeed);
        }

        /// <summary>
        /// Sets the scroll speed of the scene camera
        /// </summary>
        /// <param name="scrollSpeed">The scroll speed value.</param>
        public void SetScrollSpeed(float scrollSpeed)
        {
            ScrollSpeed = scrollSpeed;
            EditorSettings.SetFloat("SceneCameraOptions_ScrollSpeed", scrollSpeed);
        }

        /// <summary>
        /// Sets the rotation speed of the scene camera
        /// </summary>
        /// <param name="rotationalSpeed">The rotation speed  value.</param>
        public void SetRotationalSpeed(float rotationalSpeed)
        {
            RotationalSpeed = rotationalSpeed;
            EditorSettings.SetFloat("SceneCameraOptions_RotationalSpeed", rotationalSpeed);
        }
    }
}