//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsEditorPrerequisites.h"
#include "GUI/BsGUIElement.h"
#include "2D/BsImageSprite.h"
#include "GUI/BsGUIContent.h"
#include "GUI/BsGUIElementContainer.h"
#include "Animation/BsAnimationUtility.h"

namespace bs
{
	/** @addtogroup GUI-Editor
	 *  @{
	 */

	/** Controls which elements should a GUICurves object draw. */
	enum class BS_SCRIPT_EXPORT(ed:true,m:GUIEditor,n:CurveDrawOptions) CurveDrawOption
	{
		/** Draws markers at specific time intervals. */
		DrawMarkers = 1 << 0,

		/** Draws elements representing individual keyframes. */
		DrawKeyframes = 1 << 1,

		/** Draws curves and the area between them. Only relevant if only two curves are provided for drawing. */
		DrawRange = 1 << 2
	};

	typedef Flags<CurveDrawOption> CurveDrawOptions;
	BS_FLAGS_OPERATORS(CurveDrawOption)

	/** Curve and a color to draw it in. */
	struct BS_SCRIPT_EXPORT(ed:true,pl:true,m:GUIEditor) CurveDrawInfo
	{
		CurveDrawInfo() = default;
		CurveDrawInfo(const TAnimationCurve<float>& curve, Color color)
			:curve(curve), color(color)
		{ }

		TAnimationCurve<float> curve;
		Color color;
	};

	/** Base class that can be implemented by GUI elements needing to elements along draw a horizontal timeline. */
	class BS_ED_EXPORT BS_SCRIPT_EXPORT(ed:true,m:GUIEditor) GUITimeline : public GUIElementContainer
	{
	public:
		/** Returns type name of the GUI element used for finding GUI element styles. */
		static const String& getGUITypeName();

		/**	Determines the range of values to display on the timeline, in seconds. */
		BS_SCRIPT_EXPORT(pr:setter,n:Range)
		void setRange(float range);

		/** @copydoc setRange */
		BS_SCRIPT_EXPORT(pr:getter,n:Range)
		float getRange() const;

		/**	Determines the offset at which the displayed timeline values start at, in seconds. */
		BS_SCRIPT_EXPORT(pr:setter,n:Offset)
		void setOffset(float offset);

		/** @copydoc setOffset */
		BS_SCRIPT_EXPORT(pr:getter,n:Offset)
		float getOffset() const { return mOffset; }

		/**	Number of frames per second, used for frame selection and marking. */
		BS_SCRIPT_EXPORT(pr:setter,n:FPS)
		void setFPS(UINT32 FPS);

		/** @copydoc setFPS */
		BS_SCRIPT_EXPORT(pr:getter,n:FPS)
		UINT32 getFPS() const { return mFPS; }

		/**	Frame to display the frame marker on. Set to -1 to clear the frame marker. */
		BS_SCRIPT_EXPORT(pr:setter,n:MarkedFrame)
		void setMarkedFrame(UINT32 index);

		/** @copydoc setFPS */
		BS_SCRIPT_EXPORT(pr:getter,n:MarkedFrame)
		UINT32 setMarkedFrame() const { return mFPS; }

		/**
		 * Uses the assigned FPS, range and physical size to calculate the frame that is under the provided coordinates.
		 *
		 * @param[in]	pixelCoords		Coordinates relative to this GUI element.
		 * @return						Frame that was clicked on, or -1 if the coordinates are outside of valid bounds.
		 */
		BS_SCRIPT_EXPORT()
		UINT32 getFrame(const Vector2I& pixelCoords) const;

		/**
		 * Returns the time at the specified pixel value along the timeline.
		 * 
		 * @param[in]	pixel	X coordinate to sample at, relative to this GUI element in pixels.
		 * @return				Time along the curve at the specified coordinate.
		 */
		BS_SCRIPT_EXPORT()
		float getTime(INT32 pixel) const;

		/**
		 * Finds the pixel offset relative to the GUI element's origin for the specified time.
		 *
		 * @param[in]	time	Time value to return the offset for.
		 * @return				Offset in pixels relative to GUI element's origin
		 */
		BS_SCRIPT_EXPORT()
		INT32 getOffset(float time) const;

		/**
		 * Returns time for a frame with the specified index. Depends on set range and FPS.
		 * 
		 * @param[in]	index	Index of the frame (not a key-frame) to get the time for.
		 * @return				Time of the frame with the provided index.	
		 */
		BS_SCRIPT_EXPORT()
		float getTimeForFrame(INT32 index) const;

	protected:
		GUITimeline(const String& styleName, const GUIDimensions& dimensions);
		~GUITimeline() override = default;

		/** Returns the width of the GUI element that can be drawn to (width minus padding). */
		UINT32 getDrawableWidth() const;

		/** Similar to getRange() but expands the range so it's expanded to encompas the right-most padding area. */
		float getRangeWithPadding() const;

		/** Draws a vertical frame marker at the specified time. */
		void drawFrameMarker(float t);

		/** Draws a frame marker at the currently selected frame. */
		void drawFrameMarker();

		/** @copydoc GUIElement::_updateLayoutInternal */
		void _updateLayoutInternal(const GUILayoutData& data) override;

		/** @copydoc GUIElement::_getOptimalSize */
		Vector2I _getOptimalSize() const override;

		/** @copydoc GUIElement::styleUpdated */
		void styleUpdated() override;

		GUICanvas* mCanvas = nullptr;

		float mRange = 20.0f;
		float mOffset = 0.0f;
		UINT32 mFPS = 1;
		UINT32 mMarkedFrame = (UINT32)-1;
	};

	/** Determines how should ticks reported by <see cref="GUIGraphTicks"/> be distributed. */
	enum class BS_SCRIPT_EXPORT(ed:true,m:GUIEditor) GUITickStepType
	{
		/** Ticks represent time values (Multiples of 60). */
		Time,
		/** Ticks represent generic values (Multiples of 10). */
		Generic
	};

	/**
	 * Generates a set of locations that can be used for rendering ticks on a graph. As input the class takes valid range,
	 * size of the area the ticks will be displayed on, type of ticks and minimum/maximum spacing and outputs a set of
	 * coordinates along which ticks should be positioned. Ticks are reported as multiple separate levels with different
	 * strengths, depending on how close their distribution is to the upper valid range.
	 */
	class BS_SCRIPT_EXPORT(ed:true,m:GUIEditor) GUIGraphTicks
	{
	public:
		/**
		 * Contructs a new tick generating object.
		 *
		 * @param[in]	stepType	Determines how will ticks be distributed.
		 */
		BS_SCRIPT_EXPORT()
		GUIGraphTicks(GUITickStepType stepType = GUITickStepType::Generic)
		{
			if(stepType == GUITickStepType::Generic)
				setGenericSteps();
			else
				setTimeSteps();

			rebuild();
		}

		/** Number of tick levels that will be generated. */
		BS_SCRIPT_EXPORT(pr:getter,n:NumLevels)
		UINT32 getNumLevels() const
		{
			return mNumLevels;
		}

		/**
		 * Sets the range which ticks are to be displayed for, and the range along which the ticks will be displayed.
		 *
		 * @param[in]	valueRangeStart		Start of the range the ticks are to display.
		 * @param[in]	valueRangeEnd		End of the range the ticks are to display.
		 * @param[in]	pixelRange			Width or height on which the ticks will be rendered. In pixels.
		 */
		BS_SCRIPT_EXPORT()
		void setRange(float valueRangeStart, float valueRangeEnd, UINT32 pixelRange)
		{
			this->mValueRangeStart = valueRangeStart;
			this->mValueRangeEnd = valueRangeEnd;
			this->mPixelRange = pixelRange;

			rebuild();
		}

		/**
		 * Sets valid spacing between two ticks. Tick strength will be determined by how far away are they from either
		 * end of this range.
		 *
		 * @param[in]	minPx		Minimum spacing between two ticks, in pixels.
		 * @param[in]	maxPx		Maximum spacing between two ticks, in pixels.
		 */
		BS_SCRIPT_EXPORT()
		void setTickSpacing(int minPx, int maxPx)
		{
			mMinTickSpacingPx = minPx;
			mMaxTickSpacingPx = maxPx;

			rebuild();
		}

		/**
		 * Returns the strength of a particular tick level. Levels are ordered in descending order of strength (level 0 is
		 * the strongest).
		 *
		 * @param[in]	level	Level for which to retrieve the strength. Must not be larger than getNumLevels() - 1.
		 * @return				Strength of the ticks at this level, in range [0, 1].
		 */
		BS_SCRIPT_EXPORT()
		float getLevelStrength(UINT32 level)
		{
			if (level >= mNumLevels)
				return 0.0f;

			return Math::clamp01(mLevelStrengths[mMaxLevel + level]);
		}

		/**
		 * Returns positions of all ticks of the provided level. The ticks will be within the range provided to setRange().
		 * 
		 * @param[in]	level	Level for which to retrieve the positions. Must not be larger than getNumLevels() - 1.
		 * @return				Positions of all ticks of the provided level.
		 */
		BS_SCRIPT_EXPORT()
		Vector<float> getTicks(UINT32 level)
		{
			if (level < 0 || level >= mNumLevels)
				return { };

			const float step = mValidSteps[mMaxLevel + level];

			// Round up and down so we get one extra tick on either side (outside of value range)
			// (Useful when rendering text above the ticks, so the text doesn't just pop-in when the tick appears, instead
			// it is slowly clipped-in.)
			const INT32 startTick = Math::ceilToInt(mValueRangeStart / step);
			const INT32 endTick = Math::floorToInt(mValueRangeEnd / step);

			const INT32 numTicks = endTick - startTick + 1;

			Vector<float> ticks(numTicks);
			for (INT32 i = startTick; i <= endTick; i++)
				ticks[i - startTick] = i*step;

			return ticks;
		}

	protected:
		/** Rebuilds the tick positions and strengths after some relevant parameter changes. */
		void rebuild()
		{
			mLevelStrengths = Vector<float>(mValidSteps.size());
			mMaxLevel = 0;

			const float valueRange = mValueRangeEnd - mValueRangeStart;
			const INT32 tickSpacing = (INT32)mMaxTickSpacingPx - (INT32)mMinTickSpacingPx;
			UINT32 i = 0;
			for (; i < (UINT32)mValidSteps.size(); i++)
			{
				const float tickSpacingPx = (mValidSteps[i]/valueRange) * mPixelRange;
				mLevelStrengths[i] = (tickSpacingPx - mMinTickSpacingPx)/tickSpacing;

				if (mLevelStrengths[i] > 1.0f)
					mMaxLevel = i;
				else if (mLevelStrengths[i] < 0.0f)
					break;
			}

			if (i > 0)
				mNumLevels = i - mMaxLevel;
			else
				mNumLevels = 0;
		}

		/** 
		 * Sets tick steps corresponding to time values. This will split the ticks into intervals relevant for displaying
		 * times.
		 */
		void setTimeSteps()
		{
			mValidSteps = 
			{
				3600.0f, 1800.0f, 600.0f, 300.0f,
				60.0f, 30.0f, 10.0f, 5.0f,
				1.0f, 0.5f, 0.25f, 0.1f, 0.05f, 0.01f
			};
		}

		/** Sets tick steps corresponding to generic values (as opposed to displaying time values). */
		void setGenericSteps()
		{
			constexpr UINT32 numSteps = 15;
			float minStep = 0.0000001f;

			mValidSteps = Vector<float>(numSteps * 2);
			for (int i = numSteps - 1; i >= 0; i--)
			{
				mValidSteps[i * 2 + 1] = minStep;
				mValidSteps[i * 2 + 0] = minStep * 5;

				minStep *= 10.0f;
			}
		}

		UINT32 mPixelRange = 100;
		float mValueRangeStart = 0.0f;
		float mValueRangeEnd = 1.0f;

		UINT32 mMinTickSpacingPx = 5;
		UINT32 mMaxTickSpacingPx = 30;

		Vector<float> mValidSteps = { 1.0f };
		Vector<float> mLevelStrengths = { 1.0f };
		UINT32 mNumLevels = 1;
		UINT32 mMaxLevel = 0;
	};

	/** GUI element that displays one or multiple curves. */
	class BS_ED_EXPORT BS_SCRIPT_EXPORT(ed:true,m:GUIEditor) GUICurves : public GUITimeline
	{
	public:
		/** Returns type name of the GUI element used for finding GUI element styles. */
		static const String& getGUITypeName();

		/**
		 * Creates a new GUI element.
		 *
		 * @param[in]	styleName		Optional style to use for the element. Style will be retrieved from GUISkin of the
		 *								GUIWidget the element is used on. If not specified default style is used.
		 */
		BS_SCRIPT_EXPORT(ec:GUICurves)
		static GUICurves* create(const String& styleName = StringUtil::BLANK);

		/**
		 * Creates a new GUI element.
		 *
		 * @param[in]	drawOptions		Options that control which additional elements to draw.
		 * @param[in]	styleName		Optional style to use for the element. Style will be retrieved from GUISkin of the
		 *								GUIWidget the element is used on. If not specified default style is used.
		 */
		BS_SCRIPT_EXPORT(ec:GUICurves)
		static GUICurves* create(CurveDrawOptions drawOptions, const String& styleName = StringUtil::BLANK);

		/**
		 * Creates a new GUI element.
		 *
		 * @param[in]	options			Options that allow you to control how is the element positioned and sized. This will
		 *								override any similar options set by style.
		 * @param[in]	styleName		Optional style to use for the element. Style will be retrieved from GUISkin of the
		 *								GUIWidget the element is used on. If not specified default style is used.
		 */
		static GUICurves* create(const GUIOptions& options, const String& styleName = StringUtil::BLANK);

		/**
		 * Creates a new GUI element.
		 * 
		 * @param[in]	drawOptions		Options that control which additional elements to draw.
		 * @param[in]	options			Options that allow you to control how is the element positioned and sized. This will
		 *								override any similar options set by style.
		 * @param[in]	styleName		Optional style to use for the element. Style will be retrieved from GUISkin of the
		 *								GUIWidget the element is used on. If not specified default style is used.
		 */
		static GUICurves* create(CurveDrawOptions drawOptions, const GUIOptions& options, 
			const String& styleName = StringUtil::BLANK);

		/**	Animation curves to display. */
		BS_SCRIPT_EXPORT(pr:setter,n:Curves)
		void setCurves(const Vector<CurveDrawInfo>& curves);

		/** @copydoc setCurves */
		BS_SCRIPT_EXPORT(pr:getter,n:Curves)
		const Vector<CurveDrawInfo>& getCurves() const { return mCurves; }

		/**
		 * Changes the visible range that the GUI element displays.
		 *
		 * @param[in]	xRange		Range of the horizontal area. Displayed area will range from [0, xRange].
		 * @param[in]	yRange		Range of the vertical area. Displayed area will range from [-yRange * 0.5, yRange * 0.5]
		 */
		BS_SCRIPT_EXPORT()
		void setRange(float xRange, float yRange);

		/**
		 * Returns the offset at which the displayed timeline values start at.
		 *
		 * @param[in]	offset		Value to start the timeline values at, where x = time, y = value.
		 */
		BS_SCRIPT_EXPORT()
		void setOffset(const Vector2& offset);

		/** Centers and zooms the view to fully display the provided set of curves. */
		BS_SCRIPT_EXPORT()
		void centerAndZoom();

		/**
		 * Converts pixel coordinates into coordinates in curve space.
		 *
		 * @param[in]	pixelCoords		Coordinates relative to this GUI element, in pixels.
		 * @param[out]	curveCoords		Curve coordinates within the range as specified by setRange(). Only valid when
		 *								function returns true.
		 * @param[in]	padding			Determines should coordinates over the area reserved for padding be registered.
		 * @return						True if the coordinates are within the curve area, false otherwise.
		 */
		BS_SCRIPT_EXPORT()
		bool pixelToCurveSpace(const Vector2I& pixelCoords, Vector2& curveCoords, bool padding = false) const;

		/**
		 * Converts coordinate in curve space (time, value) into pixel coordinates relative to this element's origin.
		 *
		 * @param[in]	curveCoords		Time and value of the location to convert.
		 * @return						Coordinates relative to this element's origin, in pixels.
		 */
		BS_SCRIPT_EXPORT()
		Vector2I curveToPixelSpace(const Vector2& curveCoords) const;

		/** 
		 * Attempts to find a curve under the provided coordinates.
		 *
		 * @param[in]	pixelCoords		Coordinates relative to this GUI element in pixels.
		 * @return						Index of the curve, or -1 if none found.
		 */
		BS_SCRIPT_EXPORT()
		UINT32 findCurve(const Vector2I& pixelCoords);

		/**
		 * Attempts to find a keyframe under the provided coordinates.
		 *
		 * @param[in]	pixelCoords		Coordinates relative to this GUI element in pixels.
		 * @param[out]	keyframe		Output object containing keyframe index and index of the curve it belongs to. Only 
		 *								valid if method returns true.
		 * @return						True if there is a keyframe under the coordinates, false otherwise.
		 */
		BS_SCRIPT_EXPORT()
		bool findKeyFrame(const Vector2I& pixelCoords, KeyframeRef& keyframe);

		/**
		 * Attempts to find a a tangent handle under the provided coordinates.
		 *
		 * @param[in]	pixelCoords		Coordinates relative to this GUI element in pixels.
		 * @param[in]	tangent			Output object containing keyframe information and tangent type. Only valid if method
		 *								returns true.
		 * @return						True if there is a tangent handle under the coordinates, false otherwise.
		 */
		BS_SCRIPT_EXPORT()
		bool findTangent(const Vector2I& pixelCoords, TangentRef& tangent);

		/** 
		 * Marks the specified key-frame as selected, changing the way it is displayed.
		 *
		 * @param[in]	keyframeRef		Keyframe reference containing the curve and keyframe index.
		 * @param[in]	tangentMode		Type of tangent to display on the selected keyframe.
		 * @param[in]	selected		True to select it, false to deselect it.
		 */
		BS_SCRIPT_EXPORT()
		void selectKeyframe(const KeyframeRef& keyframeRef, const TangentMode& tangentMode, bool selected);

		/** Clears any key-frames that were marked as selected. */
		BS_SCRIPT_EXPORT()
		void clearSelectedKeyframes();

		BS_SCRIPT_EXPORT(in:true)
		Event<void()> onClicked; /**< Triggered when the user clicks on the GUI element. */

	protected:
		GUICurves(CurveDrawOptions drawOptions, const String& styleName, const GUIDimensions& dimensions);
		~GUICurves() override = default;

		/**
		 * Converts a keyframe tangent (slope) value into a 2D normal vector.
		 *
		 * @param[in]	tangent		Keyframe tangent (slope).
		 * @return					Normalized 2D vector pointing in the direction of the tangent.
		 */
		Vector2 tangentToNormal(float tangent) const;

		/**
		 * Returns the position of the tangent, in element's pixel space.
		 *
		 * @param[in]	keyFrame	Keyframe that the tangent belongs to.
		 * @param[in]	type		Which tangent to retrieve the position for.
		 * @return					Position of the tangent, relative to the this GUI element's origin, in pixels.
		 */
		Vector2I getTangentPosition(const TKeyframe<float>& keyFrame, TangentType type) const;

		/** 
		 * Checks if the tangent should be displayed, depending on the active tangent mode. 
		 *
		 * @param[in]	mode	Tangent mode for the keyframe.
		 * @param[in]	type	Which tangent to check for.
		 * @return				True if the tangent should be displayed.
		 */
		bool isTangentDisplayed(TangentMode mode, TangentType type) const;

		/**
		 * Checks is the provided key-frame currently marked as selected.
		 *
		 * @param[in]	curveIdx		Index of the curve the keyframe is on.
		 * @param[in]	keyIdx			Index of the keyframe.
		 * @return						True if selected, false otherwise.
		 */
		bool isSelected(int curveIdx, int keyIdx) const;

		/**
		 * Draws a vertical frame marker on the curve area.
		 *
		 * @param[in]	t		Time at which to draw the marker.
		 * @param[in]	color	Color with which to draw the marker.
		 * @param[in]	onTop	Determines should the marker be drawn above or below the curve.
		 */
		void drawFrameMarker(float t, Color color, bool onTop);

		/** Draws a horizontal line representing the line at y = 0. */
		void drawCenterLine();

		/**
		 * Draws a diamond shape of the specified size at the coordinates.
		 *
		 * @param[in]	center		Position at which to place the diamond's center, in pixel coordinates.
		 * @param[in]	size		Determines number of pixels to extend the diamond in each direction.
		 * @param[in]	innerColor	Color of the diamond's background.
		 * @param[in]	outerColor	Color of the diamond's outline.
		 */
		void drawDiamond(Vector2I center, int size, Color innerColor, Color outerColor);

		/**
		 * Draws a keyframe a the specified time and value.
		 *
		 * @param[in]	t			Time to draw the keyframe at.
		 * @param[in]	y			Y value to draw the keyframe at.
		 * @param[in]	selected	Determines should the keyframe be drawing using the selected color scheme, or normally.
		 */
		void drawKeyframe(float t, float y, bool selected);

		/**
		 * Draws zero, one or two tangents for the specified keyframe. Whether tangents are drawn depends on the provided
		 * mode.
		 *
		 * @param[in]	keyFrame	Keyframe to draw the tangents for.
		 * @param[in]	tangentMode	Type of tangents in the keyframe.
		 */
		void drawTangents(const TKeyframe<float>& keyFrame, TangentMode tangentMode);

		/**
		 * Draws the curve using the provided color.
		 *
		 * @param[in]	curve		Curve to draw within the currently set range.
		 * @param[in]	color		Color to draw the curve with.	
		 */
		void drawCurve(const TAnimationCurve<float>& curve, const Color& color);

		/*
		 * Draws the area between two curves using the provided color.
		 *
		 * @param[in]	curves		Curves to draw within the currently set range.
		 * @param[in]	color		Color to draw the area with.
		 */
		void drawCurveRange(const Vector<TAnimationCurve<float>>& curves, Color color);

		/** @copydoc GUIElement::updateRenderElementsInternal */
		void updateRenderElementsInternal() override;

		/** @copydoc GUIElement::_mouseEvent() */
		bool _mouseEvent(const GUIMouseEvent& ev) override;

	private:
		/** Information about a currently selected keyframe. */
		struct SelectedKeyframe
		{
			SelectedKeyframe(KeyframeRef keyframeRef, TangentMode tangentMode)
				:keyframeRef(keyframeRef), tangentMode(tangentMode)
			{ }

			KeyframeRef keyframeRef;
			TangentMode tangentMode;
		};

		Vector<CurveDrawInfo> mCurves;
		Vector<SelectedKeyframe> mSelectedKeyframes;

		float mYRange = 20.0f;
		float mYOffset = 0.0f;
		CurveDrawOptions mDrawOptions;
		GUIGraphTicks mTickHandler;
	};

	/** @} */
}
