//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2018 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsEditorPrerequisites.h"
#include "GUI/BsGUIFieldBase.h"
#include "Particles/BsParticleDistribution.h"

namespace bs
{
	class GUICurves;

	/** @addtogroup GUI-Editor
	 *  @{
	 */

	/**
	 * A composite GUI object representing an editor field. Editor fields are a combination of a label and an input field.
	 * Label is optional. This specific implementation displays an input field for a floating point distribution.
	 */
	class BS_ED_EXPORT BS_SCRIPT_EXPORT(ed:true,m:GUIEditor) 
	GUIFloatDistributionField final : public TGUIField<GUIFloatDistributionField>
	{
	public:
		/** Style type name for the internal float fields. */
		static constexpr const char* FLOAT_FIELD_STYLE_TYPE = "FloatField";

		/** Style type name for the internal curve display field. */
		static constexpr const char* CURVES_FIELD_STYLE_TYPE = "CurvesField";

		/** Style type name for the internal drop down button. */
		static constexpr const char* DROP_DOWN_FIELD_STYLE_TYPE = "DropDownButton";

		/** Returns type name of the GUI element used for finding GUI element styles. */
		static const String& getGUITypeName();

		GUIFloatDistributionField(const PrivatelyConstruct& dummy, const GUIContent& labelContent, UINT32 labelWidth,
			const String& style, const GUIDimensions& dimensions, bool withLabel);

		/**	Returns the value of the field. */
		BS_SCRIPT_EXPORT(pr:getter,n:Value)
		FloatDistribution getValue() const { return mValue; }

		/**	Changes the value of the field. */
		BS_SCRIPT_EXPORT(pr:setter,n:Value)
		void setValue(const FloatDistribution& value);

		/** @copydoc GUIElement::setTint */
		void setTint(const Color& color) override;

		/** 
		 * Triggered when the user clicks on the curve display. Only relevant if the distribution is a curve distribution. 
		 */
		BS_SCRIPT_EXPORT(in:true)
		Event<void()> onClicked; /**< Triggered when the user clicks on the GUI element. */

		/** 
		 * Triggered when the user modifies either of the non-curve (constant) values of the distribution. Only relevant
		 * if the distribution is not a curve distribution.
		 */
		BS_SCRIPT_EXPORT(in:true)
		Event<void()> onConstantModified; /**< Triggered when the user clicks on the GUI element. */

		/** @name Internal 
		 *  @{
		 */

		/** @copydoc GUIElement::_getOptimalSize */
		Vector2I _getOptimalSize() const override;

		/** @} */

	protected:
		/** @copydoc GUIElement::styleUpdated */
		void styleUpdated() override;

		/** Rebuilds the internal GUI components for the current property type. */
		void rebuild();

		UINT32 mLabelWidth = 100;
		FloatDistribution mValue = 0.0f;
		GUIButton* mDropDownButton = nullptr;
		GUIFloatField* mMinInput = nullptr;
		GUIFloatField* mMaxInput = nullptr;
		GUICurves* mCurveDisplay = nullptr;

		float mMinConstant = 0.0f;
		float mMaxConstant = 0.0f;
		TAnimationCurve<float> mCurves[2];
		SPtr<GUIContextMenu> mContextMenu;
	};

	/** @} */
}
