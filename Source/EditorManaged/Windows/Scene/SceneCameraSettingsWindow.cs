//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2019 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//

using System;
using bs;

namespace bs.Editor
{
    /** @addtogroup Windows
     *  @{
     */

    /// <summary>
    /// Displays settings for the scene camera.
    /// </summary>
    internal class SceneCameraSettingsWindow : EditorWindow
    {
        private const string ExpandStatesKey = "SceneCamera0_ExpandStates";

        private InspectorFieldDrawer guiViewSettings;
        private InspectorFieldDrawer guiMovementSettings;
        private InspectorFieldDrawer guiRenderSettings;

        private SceneCameraViewSettings viewSettings;
        private SceneCameraMoveSettings moveSettings;
        private RenderSettings renderSettings;

        private SerializableProperties expandStates;

        /// <summary>
        /// Opens the options window.
        /// </summary>
        public static void Open()
        {
            OpenWindow<SceneCameraSettingsWindow>();
        }

        /// <inheritdoc/>
        protected override LocString GetDisplayName()
        {
            return new LocEdString("Scene Camera Settings");
        }

        private void OnInitialize()
        {
            EditorApplication.OnProjectSave += SaveSettings;

            SceneWindow sceneWindow = SceneWindow.GetWindow<SceneWindow>();
            if (sceneWindow != null)
            {
                viewSettings = sceneWindow.Camera.ViewSettings;
                moveSettings = sceneWindow.Camera.MoveSettings;
                renderSettings = sceneWindow.Camera.RenderSettings;
            }
            else
            {
                viewSettings = ProjectSettings.GetObject<SceneCameraViewSettings>(SceneCamera.ViewSettingsKey);
                moveSettings = ProjectSettings.GetObject<SceneCameraMoveSettings>(SceneCamera.MoveSettingsKey);
                renderSettings = ProjectSettings.GetObject<RenderSettings>(SceneCamera.RenderSettingsKey);
            }

            expandStates = ProjectSettings.GetObject<SerializableProperties>(ExpandStatesKey);
            InspectableContext inspectableContext = new InspectableContext(expandStates);

            GUILayout mainLayout = GUI.AddLayoutY();

            GUIScrollArea scrollArea = new GUIScrollArea(ScrollBarType.ShowIfDoesntFit, ScrollBarType.NeverShow);
            mainLayout.AddElement(scrollArea);

            GUILayoutX horzPadLayout = scrollArea.Layout.AddLayoutX(GUIOption.FlexibleWidth(100, 400));
            horzPadLayout.AddSpace(5);

            GUILayout vertLayout = horzPadLayout.AddLayoutY();
            horzPadLayout.AddSpace(5);

            vertLayout.AddSpace(5);

            vertLayout.AddElement(new GUILabel(new LocEdString("View Settings"), EditorStyles.LabelBold));
            GUILayoutY viewSettingsLayout = vertLayout.AddLayoutY();
            vertLayout.AddSpace(10);

            vertLayout.AddElement(new GUILabel(new LocEdString("Move Settings"), EditorStyles.LabelBold));
            GUILayoutY moveSettingsLayout = vertLayout.AddLayoutY();
            vertLayout.AddSpace(10);

            vertLayout.AddElement(new GUILabel(new LocEdString("Render Settings"), EditorStyles.LabelBold));
            GUILayoutY renderSettingsLayout = vertLayout.AddLayoutY();

            guiViewSettings = new InspectorFieldDrawer(inspectableContext, viewSettingsLayout);
            guiMovementSettings = new InspectorFieldDrawer(inspectableContext, moveSettingsLayout);
            guiRenderSettings = new InspectorFieldDrawer(inspectableContext, renderSettingsLayout);

            guiViewSettings.AddDefault(viewSettings);
            guiMovementSettings.AddDefault(moveSettings);
            guiRenderSettings.AddDefault(renderSettings);

            mainLayout.AddSpace(5);
            GUILayout buttonCenterLayout = mainLayout.AddLayoutX();
            mainLayout.AddSpace(5);

            GUIButton resetToDefaultBtn = new GUIButton(new LocEdString("Reset to defaults"));
            resetToDefaultBtn.OnClick += () => ConfirmResetToDefault(ResetToDefault, null);

            buttonCenterLayout.AddFlexibleSpace();
            buttonCenterLayout.AddElement(resetToDefaultBtn);
            buttonCenterLayout.AddFlexibleSpace();
        }

        private void OnEditorUpdate()
        {
            InspectableState viewOptionsState = guiViewSettings.Refresh();
            if (viewOptionsState != InspectableState.NotModified)
            {
                SceneWindow sceneWindow = SceneWindow.GetWindow<SceneWindow>();
                if (sceneWindow != null)
                    sceneWindow.Camera.ViewSettings = viewSettings;

                ProjectSettings.SetObject(SceneCamera.ViewSettingsKey, viewSettings);
            }

            InspectableState moveOptionsState = guiMovementSettings.Refresh();
            if (moveOptionsState != InspectableState.NotModified)
            {
                SceneWindow sceneWindow = SceneWindow.GetWindow<SceneWindow>();
                if (sceneWindow != null)
                    sceneWindow.Camera.MoveSettings = moveSettings;

                ProjectSettings.SetObject(SceneCamera.MoveSettingsKey, moveSettings);
            }

            InspectableState renderOptionsState = guiRenderSettings.Refresh();
            if (renderOptionsState != InspectableState.NotModified)
            {
                SceneWindow sceneWindow = SceneWindow.GetWindow<SceneWindow>();
                if (sceneWindow != null)
                    sceneWindow.Camera.RenderSettings = renderSettings;

                ProjectSettings.SetObject(SceneCamera.RenderSettingsKey, renderSettings);
            }
        }

        private void OnDestroy()
        {
            EditorApplication.OnProjectSave -= SaveSettings;
        }

        private void SaveSettings()
        {
            ProjectSettings.SetObject(ExpandStatesKey, expandStates);
        }

        /// <summary>
        /// Resets all scene camera settings to default values.
        /// </summary>
        private void ResetToDefault()
        {
            viewSettings = new SceneCameraViewSettings();
            moveSettings = new SceneCameraMoveSettings();
            renderSettings = new RenderSettings();

            SceneWindow sceneWindow = SceneWindow.GetWindow<SceneWindow>();
            if (sceneWindow != null)
            {
                sceneWindow.Camera.ViewSettings = viewSettings;
                sceneWindow.Camera.MoveSettings = moveSettings;
                sceneWindow.Camera.RenderSettings = renderSettings;
            }

            ProjectSettings.SetObject(SceneCamera.ViewSettingsKey, viewSettings);
            ProjectSettings.SetObject(SceneCamera.MoveSettingsKey, moveSettings);
            ProjectSettings.SetObject(SceneCamera.RenderSettingsKey, renderSettings);
        }

        /// <summary>
        /// Opens a dialog asking the user whether he wants to reset camera settings to defaults.
        /// </summary>
        private void ConfirmResetToDefault(Action confirm, Action cancel)
        {
            DialogBox.Open("Confirm", "Are you sure you want to reset all scene camera settings to default?",
                DialogBox.Type.OKCancel, x =>
                {
                    if (x == DialogBox.ResultType.OK)
                        confirm?.Invoke();
                    else
                        cancel?.Invoke();
                });
        }
    }

    /** @} */
}
