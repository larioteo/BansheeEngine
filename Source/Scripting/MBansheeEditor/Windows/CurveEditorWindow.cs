//********************************** Banshee Engine (www.banshee5d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using BansheeEngine;

namespace BansheeEditor
{
    /// <summary>
    /// Opens a window that allows the user to edit a single animation curve or two curves representing a range.
    /// </summary>
    [DefaultSize(600, 400)]
    public class CurveEditorWindow : EditorWindow
    {
        private GUICurveEditor curveEditor;

        #region Overrides

        // DEBUG ONLY
        [MenuItem("Windows/Dbg", 5000)]
        public static void Open()
        {
            OpenWindow<CurveEditorWindow>();
        }

        /// <inheritdoc/>
        protected override LocString GetDisplayName()
        {
            return new LocEdString("Curve editor");
        }

        private void OnInitialize()
        {
            // TODO - Add methods to allow the window to be open with user-defined curve(s)
            // TODO - Add callbacks that trigger when user finishes editing
            // TODO - Add OK/Cancel buttons? Make the window modal?
            // TODO - Add a CurveField GUI element that can be used for curve preview, clicking on which opens this window

            curveEditor = new GUICurveEditor(this, this.GUI, 600, 400, false);
            curveEditor.Redraw();

            EdAnimationCurve[] edAnimCurve =
            {
                new EdAnimationCurve(),
                new EdAnimationCurve()
            };

            edAnimCurve[0].AddKeyframe(0.0f, 1.0f);
            edAnimCurve[0].AddKeyframe(5.0f, 3.0f);
            edAnimCurve[0].AddKeyframe(8.0f, -3.0f);
            edAnimCurve[0].AddKeyframe(15.0f, 2.0f);
            edAnimCurve[0].Apply();

            edAnimCurve[1].AddKeyframe(0.0f, -3.0f);
            edAnimCurve[1].AddKeyframe(3.0f, 0.0f);
            edAnimCurve[1].AddKeyframe(10.0f, -1.0f);
            edAnimCurve[1].AddKeyframe(13.0f, -5.0f);
            edAnimCurve[1].Apply();

            CurveDrawInfo[] drawinfo =
            {
                new CurveDrawInfo(edAnimCurve[0], Color.Green),
                new CurveDrawInfo(edAnimCurve[1], Color.Red),
            };

            curveEditor.SetCurves(drawinfo);
            curveEditor.CenterAndResize(true);
            curveEditor.SetDrawRange(true);

            EditorInput.OnPointerPressed += OnPointerPressed;
            EditorInput.OnPointerDoubleClick += OnPointerDoubleClicked;
            EditorInput.OnPointerMoved += OnPointerMoved;
            EditorInput.OnPointerReleased += OnPointerReleased;
            EditorInput.OnButtonUp += OnButtonUp;
        }

        private void OnEditorUpdate()
        {
            curveEditor.HandleDragAndZoomInput();
        }

        private void OnDestroy()
        {
            EditorInput.OnPointerPressed -= OnPointerPressed;
            EditorInput.OnPointerDoubleClick -= OnPointerDoubleClicked;
            EditorInput.OnPointerMoved -= OnPointerMoved;
            EditorInput.OnPointerReleased -= OnPointerReleased;
            EditorInput.OnButtonUp -= OnButtonUp;
        }

        /// <inheritdoc/>
        protected override void WindowResized(int width, int height)
        {
            Vector2I curveEditorSize = new Vector2I(width, height);
            curveEditor.SetSize(curveEditorSize.x, curveEditorSize.y);
            curveEditor.Redraw();
        }

        #endregion

        #region Input callbacks
        /// <summary>
        /// Triggered when the user presses a mouse button.
        /// </summary>
        /// <param name="ev">Information about the mouse press event.</param>
        private void OnPointerPressed(PointerEvent ev)
        {
            curveEditor.OnPointerPressed(ev);

        }

        /// <summary>
        /// Triggered when the user double clicks the left mouse button.
        /// </summary>
        /// <param name="ev">Information about the mouse event.</param>
        private void OnPointerDoubleClicked(PointerEvent ev)
        {
            curveEditor.OnPointerDoubleClicked(ev);
        }

        /// <summary>
        /// Triggered when the user moves the mouse.
        /// </summary>
        /// <param name="ev">Information about the mouse move event.</param>
        private void OnPointerMoved(PointerEvent ev)
        {
            curveEditor.OnPointerMoved(ev);

        }

        /// <summary>
        /// Triggered when the user releases a mouse button.
        /// </summary>
        /// <param name="ev">Information about the mouse release event.</param>
        private void OnPointerReleased(PointerEvent ev)
        {
            curveEditor.OnPointerReleased(ev);
        }

        /// <summary>
        /// Triggered when the user releases a keyboard button.
        /// </summary>
        /// <param name="ev">Information about the keyboard release event.</param>
        private void OnButtonUp(ButtonEvent ev)
        {
            curveEditor.OnButtonUp(ev);
        }
        #endregion
    }

    /** @} */
}
