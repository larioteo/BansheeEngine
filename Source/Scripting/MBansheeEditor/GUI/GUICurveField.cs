//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2018 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System;
using BansheeEngine;

namespace BansheeEditor
{
    /// <summary>
    /// Displays a preview of a single animation curve or a range represented by two curves. Clicking on the field
    /// open an editor window that allows the user to edit the curve(s).
    /// </summary>
    public class GUICurveField
    {
        private GUIPanel mainPanel;
        private GUICurveDrawing curveDrawing;
        private CurveDrawInfo[] drawInfos;
        private bool drawRange;

        /// <summary>
        /// Constructs the element displaying a single animation curve.
        /// </summary>
        /// <param name="layout">GUI layout to which to add the element to.</param>
        /// <param name="curve">Curve to display.</param>
        /// <param name="width">Width of the GUI element in pixels.</param>
        /// <param name="height">Height of the GUI element in pixels.</param>
        public GUICurveField(GUILayout layout, AnimationCurve curve, int width = 200, int height = 60)
        { 
            drawInfos = new [] { new CurveDrawInfo(new EdAnimationCurve(curve, null), Color.BansheeOrange ) };
            drawRange = false;

            Initialize(layout, width, height);
        }

        /// <summary>
        /// Constructs the element displaying a curve between two animation curves.
        /// </summary>
        /// <param name="layout">GUI layout to which to add the element to.</param>
        /// <param name="curveA">First curve to display.</param>
        /// <param name="curveB">Second curve to display.</param>
        /// <param name="width">Width of the GUI element in pixels.</param>
        /// <param name="height">Height of the GUI element in pixels.</param>
        public GUICurveField(GUILayout layout, AnimationCurve curveA, AnimationCurve curveB, int width = 200, int height = 60)
        { 
            drawInfos = new []
            {
                new CurveDrawInfo(new EdAnimationCurve(curveA, null), Color.BansheeOrange ),
                new CurveDrawInfo(new EdAnimationCurve(curveB, null), Color.Green )
            };
            drawRange = true;

            Initialize(layout, width, height);
        }

        /// <summary>
        /// Contains common initialization code for all constructors.
        /// </summary>
        /// <param name="layout">GUI layout to which to add the element to.</param>
        /// <param name="width">Width of the GUI element in pixels.</param>
        /// <param name="height">Height of the GUI element in pixels.</param>
        private void Initialize(GUILayout layout, int width, int height)
        {
            Rect2I padding = new Rect2I(2, 2, 4, 6);

            mainPanel = layout.AddPanel();

            GUIPanel curveDrawingPanel = mainPanel.AddPanel();
            GUIPanel underlayPanel = mainPanel.AddPanel(1);
            GUIPanel overlayPanel = mainPanel.AddPanel(-1);
            curveDrawingPanel.SetPosition(padding.x, padding.y);

            CurveDrawOptions drawOptions = CurveDrawOptions.DrawMarkers;
            if (drawRange)
                drawOptions |= CurveDrawOptions.DrawRange;

            curveDrawing = new GUICurveDrawing(curveDrawingPanel, width - padding.width, height - padding.height,
                drawInfos, drawOptions);

            Refresh();

            GUITexture containerBg = new GUITexture(null, EditorStylesInternal.ContainerBg);
            containerBg.SetWidth(width);
            containerBg.SetHeight(height);

            underlayPanel.AddElement(containerBg);

            GUIButton button = new GUIButton(new LocEdString(""), EditorStyles.Blank, GUIOption.FixedWidth(width),
                GUIOption.FixedHeight(height));
            overlayPanel.AddElement(button);

            button.OnClick += DoOnClick;
        }

        /// <summary>
        /// Triggers when the user clicks on the GUI element.
        /// </summary>
        private void DoOnClick()
        {
            if (drawRange)
            {
                CurveEditorWindow.Show(drawInfos[0].curve.Normal, drawInfos[1].curve.Normal,
                    (success, curveA, curveB) =>
                {
                    if (!success)
                        return;

                    drawInfos[0].curve = new EdAnimationCurve(curveA, null);
                    drawInfos[1].curve = new EdAnimationCurve(curveB, null);
                    curveDrawing.SetCurves(drawInfos);
                    Refresh();
                });
            }
            else
            {
                CurveEditorWindow.Show(drawInfos[0].curve.Normal, (success, curve) =>
                {
                    if (!success)
                        return;

                    drawInfos[0].curve = new EdAnimationCurve(curve, null);
                    curveDrawing.SetCurves(drawInfos);
                    Refresh();
                });
            }
        }

        /// <summary>
        /// Removes the GUI element from the parent layout.
        /// </summary>
        public void Destroy()
        {
            mainPanel.Destroy();
        }

        /// <summary>
        /// Refreshes the curve drawing control. Should be called after curves change.
        /// </summary>
        private void Refresh()
        {
            Vector2 offset, range;
            GUICurveDrawing.GetOptimalRangeAndOffset(drawInfos, out offset, out range);
            curveDrawing.SetRange(range.x, range.y * 2.0f);
            curveDrawing.SetOffset(offset);
            curveDrawing.Rebuild();
        }
    }
}
