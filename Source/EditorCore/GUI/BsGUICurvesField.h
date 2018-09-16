//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2018 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsEditorPrerequisites.h"
#include "GUI/BsGUIFieldBase.h"
#include "Animation/BsAnimationCurve.h"

namespace bs
{
	class GUICurves;

	/** @addtogroup GUI-Editor
	 *  @{
	 */

	/**
	 * A composite GUI object representing an editor field. Editor fields are a combination of a label and an input field.
	 * Label is optional. This specific implementation displays an animation curve or a range between two animation curves.
	 */
	class BS_ED_EXPORT BS_SCRIPT_EXPORT(ed:true,m:GUIEditor) GUICurvesField final : public TGUIField<GUICurvesField>
	{
	public:
		/** Returns type name of the GUI element used for finding GUI element styles. */
		static const String& getGUITypeName();

		/** Style type name for the internal curve field. */
		static const String& getCurveStyleType();

		GUICurvesField(const PrivatelyConstruct& dummy, const GUIContent& labelContent, UINT32 labelWidth,
			const String& style, const GUIDimensions& dimensions, bool withLabel);

		/** Sets an animation curve to display on the field. */
		BS_SCRIPT_EXPORT() 
		void setCurve(const TAnimationCurve<float>& curve);

		/** Sets a set of animation curves and displays the difference (range) between them. */
		BS_SCRIPT_EXPORT()
		void setCurveRange(const TAnimationCurve<float>& curveA, const TAnimationCurve<float>& curveB);

		/** @copydoc GUIElement::setTint */
		void setTint(const Color& color) override;

		BS_SCRIPT_EXPORT() 
		Event<void()> onClicked; /**< Triggered when the user clicks on the GUI element. */

		/** @name Internal 
		 *  @{
		 */

		/** @copydoc GUIElement::_getOptimalSize */
		Vector2I _getOptimalSize() const override;

		/** @} */

	protected:
		/** @copydoc GUIElement::styleUpdated */
		void styleUpdated() override;

		/**	Triggered when the child color input field is clicked on. */
		void clicked();

		UINT32 mLabelWidth = 100;
		GUILabel* mLabel = nullptr;
		GUICurves* mCurves = nullptr;
	};

	/** @} */
}