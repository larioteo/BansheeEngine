//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System;
using System.Collections.Generic;
using BansheeEngine;

namespace BansheeEditor
{
    /** @addtogroup AnimationEditor
     *  @{
     */

    /// <summary>
    /// Draws one or multiple curves over the specified physical area. User can specify horizontal and vertical range to
    /// display, as well as physical size of the GUI area.
    /// </summary>
    internal class GUICurveDrawing : GUITimelineBase
    {
        private const int LINE_SPLIT_WIDTH = 2;
        private const int TANGENT_LINE_DISTANCE = 30;
        private static readonly Color COLOR_MID_GRAY = new Color(90.0f / 255.0f, 90.0f / 255.0f, 90.0f / 255.0f, 1.0f);
        private static readonly Color COLOR_DARK_GRAY = new Color(40.0f / 255.0f, 40.0f / 255.0f, 40.0f / 255.0f, 1.0f);

        private CurveDrawInfo[] curveInfos;
        private bool[][] selectedKeyframes;

        private float yRange = 20.0f;
        private float yOffset;

        private GUIGraphTicks tickHandler;
        private CurveDrawOptions drawOptions;

        /// <summary>
        /// Creates a new curve drawing GUI element.
        /// </summary>
        /// <param name="layout">Layout into which to add the GUI element.</param>
        /// <param name="width">Width of the element in pixels.</param>
        /// <param name="height">Height of the element in pixels.</param>
        /// <param name="curveInfos">Initial set of curves to display. </param>
        /// <param name="options">Options that control which additional elements to draw.</param>
        public GUICurveDrawing(GUILayout layout, int width, int height, CurveDrawInfo[] curveInfos, 
            CurveDrawOptions options = CurveDrawOptions.DrawKeyframes | CurveDrawOptions.DrawMarkers)
            :base(layout, width, height)
        {
            drawOptions = options;

            if(drawOptions.HasFlag(CurveDrawOptions.DrawMarkers))
                tickHandler = new GUIGraphTicks(GUITickStepType.Time);

            this.curveInfos = curveInfos;
            
            ClearSelectedKeyframes(); // Makes sure the array is initialized
        }

        /// <summary>
        /// Change the set of curves to display.
        /// </summary>
        /// <param name="curveInfos">New set of curves to draw on the GUI element.</param>
        public void SetCurves(CurveDrawInfo[] curveInfos)
        {
            this.curveInfos = curveInfos;
        }
        
        /// <summary>
        /// Changes the visible range that the GUI element displays.
        /// </summary>
        /// <param name="xRange">Range of the horizontal area. Displayed area will range from [0, xRange].</param>
        /// <param name="yRange">Range of the vertical area. Displayed area will range from 
        ///                      [-yRange * 0.5, yRange * 0.5]</param>
        public void SetRange(float xRange, float yRange)
        {
            SetRange(xRange);
            this.yRange = yRange;
        }

        /// <summary>
        /// Returns the offset at which the displayed timeline values start at.
        /// </summary>
        /// <param name="offset">Value to start the timeline values at.</param>
        public void SetOffset(Vector2 offset)
        {
            SetOffset(offset.x);
            yOffset = offset.y;
        }

        /// <summary>
        /// Marks the specified key-frame as selected, changing the way it is displayed.
        /// </summary>
        /// <param name="keyframeRef">Keyframe reference containing the curve and keyframe index.</param>
        /// <param name="selected">True to select it, false to deselect it.</param>
        public void SelectKeyframe(KeyframeRef keyframeRef, bool selected)
        {
            if (selectedKeyframes == null)
                return;

            if (keyframeRef.curveIdx < 0 || keyframeRef.curveIdx >= selectedKeyframes.Length)
                return;

            if (keyframeRef.keyIdx < 0 || keyframeRef.keyIdx >= selectedKeyframes[keyframeRef.curveIdx].Length)
                return;

            selectedKeyframes[keyframeRef.curveIdx][keyframeRef.keyIdx] = selected;
        }

        /// <summary>
        /// Clears any key-frames that were marked as selected.
        /// </summary>
        public void ClearSelectedKeyframes()
        {
            selectedKeyframes = new bool[curveInfos.Length][];

            for (int i = 0; i < curveInfos.Length; i++)
            {
                KeyFrame[] keyframes = curveInfos[i].curve.KeyFrames;
                selectedKeyframes[i] = new bool[keyframes.Length];
            }
        }

        /// <summary>
        /// Attempts to find a curve under the provided coordinates.
        /// </summary>
        /// <param name="pixelCoords">Coordinates relative to this GUI element in pixels.</param>
        /// <returns>Index of the curve, or -1 if none found.</returns>
        public int FindCurve(Vector2I pixelCoords)
        {
            PixelToCurveSpace(pixelCoords, out var curveCoords, true);

            float time = curveCoords.x;

            float nearestDistance = float.MaxValue;
            int curveIdx = -1;
            for (int i = 0; i < curveInfos.Length; i++)
            {
                EdAnimationCurve curve = curveInfos[i].curve;

                float value = curve.Evaluate(time, false);
                Vector2I curPixelPos = CurveToPixelSpace(new Vector2(time, value));

                float distanceToKey = Vector2I.Distance(pixelCoords, curPixelPos);
                if (distanceToKey < nearestDistance)
                {
                    nearestDistance = distanceToKey;
                    curveIdx = i;
                }
            }

            // We're not near any curve
            if (nearestDistance > 5.0f)
                return -1;

            return curveIdx;
        }

        /// <summary>
        /// Attempts to find a keyframe under the provided coordinates.
        /// </summary>
        /// <param name="pixelCoords">Coordinates relative to this GUI element in pixels.</param>
        /// <param name="keyframe">Output object containing keyframe index and index of the curve it belongs to. Only valid
        ///                        if method returns true.</param>
        /// <returns>True if there is a keyframe under the coordinates, false otherwise.</returns>
        public bool FindKeyFrame(Vector2I pixelCoords, out KeyframeRef keyframe)
        {
            keyframe = new KeyframeRef();

            float nearestDistance = float.MaxValue;
            for (int i = 0; i < curveInfos.Length; i++)
            {
                EdAnimationCurve curve = curveInfos[i].curve;
                KeyFrame[] keyframes = curve.KeyFrames;

                for (int j = 0; j < keyframes.Length; j++)
                {
                    Vector2 keyframeCurveCoords = new Vector2(keyframes[j].time, keyframes[j].value);
                    Vector2I keyframeCoords = CurveToPixelSpace(keyframeCurveCoords);

                    float distanceToKey = Vector2I.Distance(pixelCoords, keyframeCoords);
                    if (distanceToKey < nearestDistance)
                    {
                        nearestDistance = distanceToKey;
                        keyframe.keyIdx = j;
                        keyframe.curveIdx = i;
                    }
                }
            }

            // We're not near any keyframe
            if (nearestDistance > 5.0f)
                return false;

            return true;
        }

        /// <summary>
        /// Attempts to find a a tangent handle under the provided coordinates.
        /// </summary>
        /// <param name="pixelCoords">Coordinates relative to this GUI element in pixels.</param>
        /// <param name="tangent">Output object containing keyframe information and tangent type. Only valid if method
        ///                       returns true.</param>
        /// <returns>True if there is a tangent handle under the coordinates, false otherwise.</returns>
        public bool FindTangent(Vector2I pixelCoords, out TangentRef tangent)
        {
            tangent = new TangentRef();

            float nearestDistance = float.MaxValue;
            for (int i = 0; i < curveInfos.Length; i++)
            {
                EdAnimationCurve curve = curveInfos[i].curve;
                KeyFrame[] keyframes = curve.KeyFrames;

                for (int j = 0; j < keyframes.Length; j++)
                {
                    if (!IsSelected(i, j))
                        continue;

                    TangentMode tangentMode = curve.TangentModes[j];

                    if (IsTangentDisplayed(tangentMode, TangentType.In))
                    {
                        Vector2I tangentCoords = GetTangentPosition(keyframes[j], TangentType.In);

                        float distanceToHandle = Vector2I.Distance(pixelCoords, tangentCoords);
                        if (distanceToHandle < nearestDistance)
                        {
                            nearestDistance = distanceToHandle;
                            tangent.keyframeRef.keyIdx = j;
                            tangent.keyframeRef.curveIdx = i;
                            tangent.type = TangentType.In;
                        }
;                    }

                    if (IsTangentDisplayed(tangentMode, TangentType.Out))
                    {
                        Vector2I tangentCoords = GetTangentPosition(keyframes[j], TangentType.Out);

                        float distanceToHandle = Vector2I.Distance(pixelCoords, tangentCoords);
                        if (distanceToHandle < nearestDistance)
                        {
                            nearestDistance = distanceToHandle;
                            tangent.keyframeRef.keyIdx = j;
                            tangent.keyframeRef.curveIdx = i;
                            tangent.type = TangentType.Out;
                        }
                    }
                }
            }

            // We're not near any keyframe
            if (nearestDistance > 5.0f)
                return false;

            return true;
        }
        
        /// <summary>
        /// Converts pixel coordinates into coordinates in curve space.
        /// </summary>
        /// <param name="pixelCoords">Coordinates relative to this GUI element, in pixels.</param>
        /// <param name="curveCoords">Curve coordinates within the range as specified by <see cref="SetRange"/>. Only
        ///                           valid when function returns true.</param>
        /// <param name="padding">Determines should coordinates over padding be registered.</param>
        /// <returns>True if the coordinates are within the curve area, false otherwise.</returns>
        public bool PixelToCurveSpace(Vector2I pixelCoords, out Vector2 curveCoords, bool padding = false)
        {
            Rect2I bounds = canvas.Bounds;

            bool outsideHorizontal;
            if (padding)
                outsideHorizontal = pixelCoords.x < bounds.x || pixelCoords.x >= (bounds.x + bounds.width);
            else
                outsideHorizontal = pixelCoords.x < (bounds.x + PADDING) || pixelCoords.x >= (bounds.x + bounds.width - PADDING);

            // Check if outside of curve drawing bounds
            if (outsideHorizontal || pixelCoords.y < bounds.y || pixelCoords.y >= (bounds.y + bounds.height))
            {
                curveCoords = new Vector2();
                return false;
            }

            // Find time and value of the place under the coordinates
            Vector2I relativeCoords = pixelCoords - new Vector2I(bounds.x + PADDING, bounds.y);

            float lengthPerPixel = GetRange() / drawableWidth;
            float heightPerPixel = yRange / height;

            float centerOffset = yRange / 2.0f;

            float t = rangeOffset + relativeCoords.x * lengthPerPixel;
            float value = yOffset + centerOffset - relativeCoords.y * heightPerPixel;

            curveCoords = new Vector2();
            curveCoords.x = t;
            curveCoords.y = value;

            return true;
        }

        /// <summary>
        /// Converts coordinate in curve space (time, value) into pixel coordinates relative to this element's origin.
        /// </summary>
        /// <param name="curveCoords">Time and value of the location to convert.</param>
        /// <returns>Coordinates relative to this element's origin, in pixels.</returns>
        public Vector2I CurveToPixelSpace(Vector2 curveCoords)
        {
            int heightOffset = height / 2; // So that y = 0 is at center of canvas

            Vector2 relativeCurveCoords = curveCoords - new Vector2(rangeOffset, yOffset);

            Vector2I pixelCoords = new Vector2I();
            pixelCoords.x = (int)((relativeCurveCoords.x / GetRange()) * drawableWidth) + PADDING;
            pixelCoords.y = heightOffset - (int)((relativeCurveCoords.y / yRange) * height);

            return pixelCoords;
        }

        /// <summary>
        /// Returns the offset and range required for fully displaying the provided set of curves. 
        /// </summary>
        /// <param name="offset">Offset used for centering the curves.</param>
        /// <param name="range">Range representing the width/height in curve space (time, value). </param>
        public static void GetOptimalRangeAndOffset(CurveDrawInfo[] curveInfos, out Vector2 offset, out Vector2 range)
        {
            float xMin, xMax;
            float yMin, yMax;
            CalculateRange(curveInfos, out xMin, out xMax, out yMin, out yMax);

            float xRange = xMax - xMin;

            float yRange = (yMax - yMin) * 0.5f;
            float yOffset = yMin + yRange;

            // Add padding to y range
            yRange *= 1.05f;

            // Don't allow zero range
            if (xRange == 0.0f)
                xRange = 60.0f;

            if (yRange == 0.0f)
                yRange = 10.0f;

            offset = new Vector2(xMin, yOffset);
            range = new Vector2(xRange, yRange);
        }

        /// <summary>
        /// Calculates the total range covered by a set of curves.
        /// </summary>
        /// <param name="curveInfos">Curves to calculate range for.</param>
        /// <param name="xMin">Minimum time value present in the curves.</param>
        /// <param name="xMax">Maximum time value present in the curves.</param>
        /// <param name="yMin">Minimum curve value present in the curves.</param>
        /// <param name="yMax">Maximum curve value present in the curves.</param>
        public static void CalculateRange(CurveDrawInfo[] curveInfos, out float xMin, out float xMax, out float yMin, 
            out float yMax)
        {
            // Note: This only evaluates at keyframes, we should also evaluate in-between in order to account for steep
            // tangents
            xMin = float.PositiveInfinity;
            xMax = float.NegativeInfinity;
            yMin = float.PositiveInfinity;
            yMax = float.NegativeInfinity;

            foreach (var curveInfo in curveInfos)
            {
                KeyFrame[] keyframes = curveInfo.curve.KeyFrames;

                foreach (var key in keyframes)
                {
                    xMin = Math.Min(xMin, key.time);
                    xMax = Math.Max(xMax, key.time);
                    yMin = Math.Min(yMin, key.value);
                    yMax = Math.Max(yMax, key.value);
                }
            }

            if (xMin == float.PositiveInfinity)
                xMin = 0.0f;

            if (xMax == float.NegativeInfinity)
                xMax = 0.0f;

            if (yMin == float.PositiveInfinity)
                yMin = 0.0f;

            if (yMax == float.NegativeInfinity)
                yMax = 0.0f;
        }

        /// <summary>
        /// Generates a unique color based on the provided index.
        /// </summary>
        /// <param name="idx">Index to use for generating a color. Should be less than 30 in order to guarantee reasonably
        /// different colors.</param>
        /// <returns>Unique color.</returns>
        public static Color GetUniqueColor(int idx)
        {
            const int COLOR_SPACING = 359 / 15;

            float hue = ((idx * COLOR_SPACING) % 359) / 359.0f;
            return Color.HSV2RGB(new Color(hue, 175.0f / 255.0f, 175.0f / 255.0f));
        }

        /// <summary>
        /// Draws a vertical frame marker on the curve area.
        /// </summary>
        /// <param name="t">Time at which to draw the marker.</param>
        /// <param name="color">Color with which to draw the marker.</param>
        /// <param name="onTop">Determines should the marker be drawn above or below the curve.</param>
        private void DrawFrameMarker(float t, Color color, bool onTop)
        {
            int xPos = (int)(((t - rangeOffset) / GetRange()) * drawableWidth) + PADDING;

            Vector2I start = new Vector2I(xPos, 0);
            Vector2I end = new Vector2I(xPos, height);

            byte depth;
            if (onTop)
                depth = 110;
            else
                depth = 130;

            canvas.DrawLine(start, end, color, depth);
        }

        /// <summary>
        /// Draws a horizontal line representing the line at y = 0.
        /// </summary>
        private void DrawCenterLine()
        {
            Vector2I center = CurveToPixelSpace(new Vector2(0.0f, 0.0f));

            Vector2I start = new Vector2I(0, center.y);
            Vector2I end = new Vector2I(width, center.y);

            canvas.DrawLine(start, end, COLOR_DARK_GRAY, 130);
        }

        /// <summary>
        /// Draws a diamond shape of the specified size at the coordinates.
        /// </summary>
        /// <param name="center">Position at which to place the diamond's center, in pixel coordinates.</param>
        /// <param name="size">Determines number of pixels to extend the diamond in each direction.</param>
        /// <param name="innerColor">Color of the diamond's background.</param>
        /// <param name="outerColor">Color of the diamond's outline.</param>
        private void DrawDiamond(Vector2I center, int size, Color innerColor, Color outerColor)
        {
            Vector2I a = new Vector2I(center.x - size, center.y);
            Vector2I b = new Vector2I(center.x, center.y - size);
            Vector2I c = new Vector2I(center.x + size, center.y);
            Vector2I d = new Vector2I(center.x, center.y + size);

            // Draw diamond shape
            Vector2I[] linePoints = new Vector2I[] { a, b, c, d, a };
            Vector2I[] trianglePoints = new Vector2I[] { b, c, a, d };

            canvas.DrawTriangleStrip(trianglePoints, innerColor, 101);
            canvas.DrawPolyLine(linePoints, outerColor, 100);
    }

        /// <summary>
        /// Draws a keyframe a the specified time and value.
        /// </summary>
        /// <param name="t">Time to draw the keyframe at.</param>
        /// <param name="y">Y value to draw the keyframe at.</param>
        /// <param name="selected">Determines should the keyframe be drawing using the selected color scheme, or normally.
        ///                        </param>
        private void DrawKeyframe(float t, float y, bool selected)
        {
            Vector2I pixelCoords = CurveToPixelSpace(new Vector2(t, y));

            if (selected)
                DrawDiamond(pixelCoords, 3, Color.White, Color.BansheeOrange);
            else
                DrawDiamond(pixelCoords, 3, Color.White, Color.Black);
        }

        /// <summary>
        /// Draws zero, one or two tangents for the specified keyframe. Whether tangents are drawn depends on the provided
        /// mode.
        /// </summary>
        /// <param name="keyFrame">Keyframe to draw the tangents for.</param>
        /// <param name="tangentMode">Type of tangents in the keyframe.</param>
        private void DrawTangents(KeyFrame keyFrame, TangentMode tangentMode)
        {
            Vector2I keyframeCoords = CurveToPixelSpace(new Vector2(keyFrame.time, keyFrame.value));

            if (IsTangentDisplayed(tangentMode, TangentType.In))
            {
                Vector2I tangentCoords = GetTangentPosition(keyFrame, TangentType.In);

                canvas.DrawLine(keyframeCoords, tangentCoords, Color.LightGray);
                DrawDiamond(tangentCoords, 2, Color.Green, Color.Black);
            }

            if (IsTangentDisplayed(tangentMode, TangentType.Out))
            {
                Vector2I tangentCoords = GetTangentPosition(keyFrame, TangentType.Out);

                canvas.DrawLine(keyframeCoords, tangentCoords, Color.LightGray);
                DrawDiamond(tangentCoords, 2, Color.Green, Color.Black);
            }
        }

        /// <summary>
        /// Returns the position of the tangent, in element's pixel space.
        /// </summary>
        /// <param name="keyFrame">Keyframe that the tangent belongs to.</param>
        /// <param name="type">Which tangent to retrieve the position for.</param>
        /// <returns>Position of the tangent, relative to the this GUI element's origin, in pixels.</returns>
        private Vector2I GetTangentPosition(KeyFrame keyFrame, TangentType type)
        {
            Vector2I position = CurveToPixelSpace(new Vector2(keyFrame.time, keyFrame.value));

            Vector2 normal;
            if (type == TangentType.In)
                normal = -EdAnimationCurve.TangentToNormal(keyFrame.inTangent);
            else
                normal = EdAnimationCurve.TangentToNormal(keyFrame.outTangent);

            // X/Y ranges aren't scaled 1:1, adjust normal accordingly
            normal.x /= GetRange();
            normal.y /= yRange;
            normal = Vector2.Normalize(normal);

            // Convert normal (in percentage) to pixel values
            Vector2I offset = new Vector2I((int)(normal.x * TANGENT_LINE_DISTANCE),
                    (int)(-normal.y * TANGENT_LINE_DISTANCE));

            return position + offset;
        }

        /// <summary>
        /// Checks if the tangent should be displayed, depending on the active tangent mode.
        /// </summary>
        /// <param name="mode">Tangent mode for the keyframe.</param>
        /// <param name="type">Which tangent to check for.</param>
        /// <returns>True if the tangent should be displayed.</returns>
        private bool IsTangentDisplayed(TangentMode mode, TangentType type)
        {
            if (mode == TangentMode.Auto)
                return false;
            else if (mode == TangentMode.Free)
                return true;

            if (type == TangentType.In)
                return mode.HasFlag(TangentMode.InFree);
            else
                return mode.HasFlag(TangentMode.OutFree);
        }

        /// <summary>
        /// Rebuilds the internal GUI elements. Should be called whenever timeline properties change.
        /// </summary>
        public override void Rebuild()
        {
            canvas.Clear();

            if (curveInfos == null)
                return;

            bool drawMarkers = drawOptions.HasFlag(CurveDrawOptions.DrawMarkers);
            if(drawMarkers)
            {
                tickHandler.SetRange(rangeOffset, rangeOffset + GetRange(true), drawableWidth + PADDING);

                // Draw vertical frame markers
                int numTickLevels = tickHandler.NumLevels;
                for (int i = numTickLevels - 1; i >= 0; i--)
                {
                    float[] ticks = tickHandler.GetTicks(i);
                    float strength = tickHandler.GetLevelStrength(i);

                    for (int j = 0; j < ticks.Length; j++)
                    {
                        Color color = COLOR_DARK_GRAY;
                        color.a *= strength;

                        DrawFrameMarker(ticks[j], color, false);
                    }
                }

                // Draw center line
                DrawCenterLine();
            }

            // Draw range
            bool drawRange = drawOptions.HasFlag(CurveDrawOptions.DrawRange);
            int curvesToDraw = curveInfos.Length;
            if (drawRange && curveInfos.Length >= 2)
            {
                EdAnimationCurve[] curves = {curveInfos[0].curve, curveInfos[1].curve};

                DrawCurveRange(curves, new Color(1.0f, 0.0f, 0.0f, 0.3f));
                curvesToDraw = 2;
            }

            // Draw curves
            bool drawKeyframes = drawOptions.HasFlag(CurveDrawOptions.DrawKeyframes);
            for (int i = 0; i < curvesToDraw; i++)
            {
                DrawCurve(curveInfos[i].curve, curveInfos[i].color);

                // Draw keyframes
                if (drawKeyframes)
                {
                    KeyFrame[] keyframes = curveInfos[i].curve.KeyFrames;

                    for (int j = 0; j < keyframes.Length; j++)
                    {
                        bool isSelected = IsSelected(i, j);

                        DrawKeyframe(keyframes[j].time, keyframes[j].value, isSelected);

                        if (isSelected)
                            DrawTangents(keyframes[j], curveInfos[i].curve.TangentModes[j]);
                    }
                }
            }

            // Draw selected frame marker
            if (drawMarkers && markedFrameIdx != -1)
                DrawFrameMarker(GetTimeForFrame(markedFrameIdx), Color.BansheeOrange, true);
        }

        /// <summary>
        /// Checks is the provided key-frame currently marked as selected.
        /// </summary>
        /// <param name="curveIdx">Index of the curve the keyframe is on.</param>
        /// <param name="keyIdx">Index of the keyframe.</param>
        /// <returns>True if selected, false otherwise.</returns>
        private bool IsSelected(int curveIdx, int keyIdx)
        {
            if (selectedKeyframes == null)
                return false;

            if (curveIdx < 0 || curveIdx >= selectedKeyframes.Length)
                return false;

            if (keyIdx < 0 || keyIdx >= selectedKeyframes[curveIdx].Length)
                return false;

            return selectedKeyframes[curveIdx][keyIdx];
        }

        /// <summary>
        /// Draws the curve using the provided color.
        /// </summary>
        /// <param name="curve">Curve to draw within the currently set range. </param>
        /// <param name="color">Color to draw the curve with.</param>
        private void DrawCurve(EdAnimationCurve curve, Color color)
        {
            float range = GetRange(true);
            float lengthPerPixel = range / drawableWidth;

            KeyFrame[] keyframes = curve.KeyFrames;
            if (keyframes.Length <= 0)
                return;

            // Draw start line
            {
                float curveStart = keyframes[0].time;
                float curveValue = curve.Evaluate(curveStart, false);

                Vector2I end = CurveToPixelSpace(new Vector2(curveStart, curveValue));
                Vector2I start = new Vector2I(-GUIGraphTime.PADDING, end.y);

                if(start.x < end.x)
                    canvas.DrawLine(start, end, COLOR_MID_GRAY);
            }

            List<Vector2I> linePoints = new List<Vector2I>();

            // Draw in between keyframes
            float startVisibleTime = rangeOffset;
            float endVisibleTime = startVisibleTime + range;
            for (int i = 0; i < keyframes.Length - 1; i++)
            {
                float start = keyframes[i].time;
                float end = keyframes[i + 1].time;

                if (end < startVisibleTime || start > endVisibleTime)
                    continue;

                bool isStep = keyframes[i].outTangent == float.PositiveInfinity ||
                              keyframes[i + 1].inTangent == float.PositiveInfinity;

                // If step tangent, draw the required lines without sampling, as the sampling will miss the step
                if (isStep)
                {
                    float startValue = curve.Evaluate(start, false);
                    float endValue = curve.Evaluate(end, false);

                    linePoints.Add(CurveToPixelSpace(new Vector2(start, startValue)));
                    linePoints.Add(CurveToPixelSpace(new Vector2(end, startValue)));
                    linePoints.Add(CurveToPixelSpace(new Vector2(end, endValue)));
                }
                else // Draw normally
                {
                    float splitIncrement = LINE_SPLIT_WIDTH*lengthPerPixel;

                    float startValue = keyframes[i].value;
                    float endValue = keyframes[i + 1].value;

                    Vector2I startPixel = new Vector2I();
                    startPixel.x = (int) (start / lengthPerPixel);
                    startPixel.y = (int) (startValue / lengthPerPixel);

                    Vector2I endPixel = new Vector2I();
                    endPixel.x = (int) (end / lengthPerPixel);
                    endPixel.y = (int) (endValue / lengthPerPixel);

                    int distance = Vector2I.Distance(startPixel, endPixel);

                    int numSplits;
                    if (distance > 0)
                    {
                        float fNumSplits = distance / splitIncrement;

                        numSplits = MathEx.CeilToInt(fNumSplits);
                        splitIncrement = distance/(float)numSplits;
                    }
                    else
                    {
                        numSplits = 1;
                        splitIncrement = 0.0f;
                    }

                    for (int j = 0; j < numSplits; j++)
                    {
                        float t = Math.Min(start + j * splitIncrement, end);
                        float value = curve.Evaluate(t, false);

                        linePoints.Add(CurveToPixelSpace(new Vector2(t, value)));
                    }
                }
            }
            
            canvas.DrawPolyLine(linePoints.ToArray(), color);

            // Draw end line
            {
                float curveEnd = keyframes[keyframes.Length - 1].time;
                float curveValue = curve.Evaluate(curveEnd, false);

                Vector2I start = CurveToPixelSpace(new Vector2(curveEnd, curveValue));
                Vector2I end = new Vector2I(width, start.y);

                if(start.x < end.x)
                    canvas.DrawLine(start, end, COLOR_MID_GRAY);
            }
        }

        /// <summary>
        /// Draws the area between two curves using the provided color.
        /// </summary>
        /// <param name="curves">Curves to draw within the currently set range.</param>
        /// <param name="color">Color to draw the area with.</param>
        private void DrawCurveRange(EdAnimationCurve[] curves, Color color)
        {
            float range = GetRange(true);

            if(curves.Length != 2 || curves[0] == null || curves[1] == null)
                return;

            KeyFrame[][] keyframes = { curves[0].KeyFrames, curves[1].KeyFrames };
            if (keyframes[0].Length <= 0 || keyframes[1].Length <= 0)
                return;

            int numSamples = (drawableWidth + LINE_SPLIT_WIDTH - 1) / LINE_SPLIT_WIDTH;
            float timePerSample = range / numSamples;

            float time = rangeOffset;
            float lengthPerPixel = rangeLength / drawableWidth;
            time -= lengthPerPixel * PADDING;

            int[] keyframeIndices = {0, 0};

            // Find first valid keyframe indices
            for (int curveIdx = 0; curveIdx < 2; curveIdx++)
            {
                keyframeIndices[curveIdx] = keyframes[curveIdx].Length;

                for (int i = 0; i < keyframes[curveIdx].Length; i++)
                {
                    if (keyframes[curveIdx][i].time > time)
                        keyframeIndices[curveIdx] = i;
                }
            }

            List<float> times = new List<float>();
            List<float>[] points = { new List<float>(), new List<float>() };

            // Determine start points
            for (int curveIdx = 0; curveIdx < 2; curveIdx++)
            {
                float value = curves[curveIdx].Evaluate(time, false);
                points[curveIdx].Add(value);
            }

            times.Add(time);

            float rangeEnd = rangeOffset + range;
            while (time < rangeEnd)
            {
                float nextTime = time + timePerSample;
                bool hasStep = false;

                // Determine time to sample at. Use fixed increments unless there's a step keyframe within our increment in
                // which case we use its time so we can evaluate it directly
                for (int curveIdx = 0; curveIdx < 2; curveIdx++)
                {
                    int keyframeIdx = keyframeIndices[curveIdx];
                    if (keyframeIdx < keyframes[curveIdx].Length)
                    {
                        KeyFrame keyframe = keyframes[curveIdx][keyframeIdx];

                        bool isStep = keyframe.inTangent == float.PositiveInfinity ||
                                      keyframe.outTangent == float.PositiveInfinity;

                        if (isStep && keyframe.time <= nextTime)
                        {
                            nextTime = Math.Min(nextTime, keyframe.time);
                            hasStep = true;
                        }
                    }
                }

                // Evaluate
                if (hasStep)
                {
                    for (int curveIdx = 0; curveIdx < 2; curveIdx++)
                    {
                        int keyframeIdx = keyframeIndices[curveIdx];
                        if (keyframeIdx < keyframes[curveIdx].Length)
                        {
                            KeyFrame keyframe = keyframes[curveIdx][keyframeIdx];

                            if (MathEx.ApproxEquals(keyframe.time, nextTime))
                            {
                                if (keyframeIdx > 0)
                                {
                                    KeyFrame prevKeyframe = keyframes[curveIdx][keyframeIdx - 1];
                                    points[curveIdx].Add(prevKeyframe.value);
                                }
                                else
                                    points[curveIdx].Add(keyframe.value);

                                points[curveIdx].Add(keyframe.value);

                            }
                            else
                            {
                                // The other curve has step but this one doesn't, we just insert the same value twice
                                float value = curves[curveIdx].Evaluate(nextTime, false);
                                points[curveIdx].Add(value);
                                points[curveIdx].Add(value);
                            }

                            times.Add(nextTime);
                            times.Add(nextTime);
                        }
                    }
                }
                else
                {
                    for (int curveIdx = 0; curveIdx < 2; curveIdx++)
                        points[curveIdx].Add(curves[curveIdx].Evaluate(nextTime, false));

                    times.Add(nextTime);
                }

                // Advance keyframe indices
                for (int curveIdx = 0; curveIdx < 2; curveIdx++)
                {
                    int keyframeIdx = keyframeIndices[curveIdx];
                    while (keyframeIdx < keyframes[curveIdx].Length)
                    {
                        KeyFrame keyframe = keyframes[curveIdx][keyframeIdx];
                        if (keyframe.time > nextTime)
                            break;

                        keyframeIdx = ++keyframeIndices[curveIdx];
                    }
                }

                time = nextTime;
            }

            // End points
            for (int curveIdx = 0; curveIdx < 2; curveIdx++)
            {
                float value = curves[curveIdx].Evaluate(rangeEnd, false);
                points[curveIdx].Add(value);
            }

            times.Add(rangeEnd);

            int numQuads = times.Count - 1;
            List<Vector2I> vertices = new List<Vector2I>();

            for (int i = 0; i < numQuads; i++)
            {
                int idxLeft = points[0][i] < points[1][i] ? 0 : 1;
                int idxRight = points[0][i + 1] < points[1][i + 1] ? 0 : 1;

                Vector2[] left =
                {
                    new Vector2(times[i], points[0][i]),
                    new Vector2(times[i], points[1][i])
                };

                Vector2[] right =
                {
                    new Vector2(times[i + 1], points[0][i + 1]),
                    new Vector2(times[i + 1], points[1][i + 1])
                };

                if (idxLeft == idxRight)
                {
                    int idxA = idxLeft;
                    int idxB = (idxLeft + 1) % 2;

                    vertices.Add(CurveToPixelSpace(left[idxB]));
                    vertices.Add(CurveToPixelSpace(right[idxB]));
                    vertices.Add(CurveToPixelSpace(left[idxA]));

                    vertices.Add(CurveToPixelSpace(right[idxB]));
                    vertices.Add(CurveToPixelSpace(right[idxA]));
                    vertices.Add(CurveToPixelSpace(left[idxA]));
                }
                // Lines intersects, can't represent them with a single quad
                else if (idxLeft != idxRight)
                {
                    int idxA = idxLeft;
                    int idxB = (idxLeft + 1) % 2;

                    Line2 lineA = new Line2(left[idxB], right[idxA] - left[idxB]);
                    Line2 lineB = new Line2(left[idxA], right[idxB] - left[idxA]);

                    if (lineA.Intersects(lineB, out var t))
                    {
                        Vector2 intersection = left[idxB] + t * (right[idxA] - left[idxB]);

                        vertices.Add(CurveToPixelSpace(left[idxB]));
                        vertices.Add(CurveToPixelSpace(intersection));
                        vertices.Add(CurveToPixelSpace(left[idxA]));

                        vertices.Add(CurveToPixelSpace(intersection));
                        vertices.Add(CurveToPixelSpace(right[idxB]));
                        vertices.Add(CurveToPixelSpace(right[idxA]));
                    }
                }
            }

            canvas.DrawTriangleList(vertices.ToArray(), color, 129);
        }
    }

    /// <summary>
    /// Information necessary to draw a curve.
    /// </summary>
    public struct CurveDrawInfo
    {
        public CurveDrawInfo(EdAnimationCurve curve, Color color)
        {
            this.curve = curve;
            this.color = color;
        }

        public EdAnimationCurve curve;
        public Color color;
    }

    /// <summary>
    /// Controls which elements should a <see cref="GUICurveDrawing"/> object draw.
    /// </summary>
    [Flags]
    internal enum CurveDrawOptions
    {
        /// <summary>
        /// Draws markers at specific time intervals.
        /// </summary>
        DrawMarkers = 1 << 0,

        /// <summary>
        /// Draws elements representing individual keyframes.
        /// </summary>
        DrawKeyframes = 1 << 1,

        /// <summary>
        /// Draws curves and the area between them. Only relevant if only two curves are provided for drawing.
        /// </summary>
        DrawRange = 1 << 2
    }

    /** }@ */
}
