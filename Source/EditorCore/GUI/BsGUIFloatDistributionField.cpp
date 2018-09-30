//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2018 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "GUI/BsGUIFloatDistributionField.h"
#include "GUI/BsGUILayout.h"
#include "GUI/BsGUILabel.h"
#include "GUI/BsGUIColor.h"
#include "GUI/BsGUIFloatField.h"
#include "GUI/BsGUICurves.h"
#include "GUI/BsGUIButton.h"
#include "GUI/BsGUIContextMenu.h"
#include "GUI/BsGUISpace.h"

using namespace std::placeholders;

namespace bs
{
	GUIFloatDistributionField::GUIFloatDistributionField(const PrivatelyConstruct& dummy, const GUIContent& labelContent, 
		UINT32 labelWidth, const String& style, const GUIDimensions& dimensions, bool withLabel)
		: TGUIField(dummy, labelContent, labelWidth, style, dimensions, withLabel)
	{
		mContextMenu = bs_shared_ptr_new<GUIContextMenu>();

		mContextMenu->addMenuItem("Constant", [this]()
		{
			mValue = FloatDistribution(mMinConstant);
			rebuild();
		}, 50);

		mContextMenu->addMenuItem("Range", [this]()
		{
			mValue = FloatDistribution(mMinConstant, mMaxConstant);
			rebuild();
		}, 40);

		mContextMenu->addMenuItem("Curve", [this]()
		{
			mValue = FloatDistribution(mCurves[0]);
			rebuild();
		}, 30);

		mContextMenu->addMenuItem("Curve range", [this]()
		{
			mValue = FloatDistribution(mCurves[0], mCurves[1]);
			rebuild();
		}, 20);

		rebuild();
	}

	void GUIFloatDistributionField::setValue(const FloatDistribution& value)
	{
		mValue = value;

		switch (mValue.getType())
		{
		default:
		case PDT_Constant:
			mMinConstant = mValue.getMinConstant();
			mMaxConstant = mMinConstant;
			mCurves[0] = TAnimationCurve<float>({
				{ mMinConstant, 0.0f, 0.0f, 0.0f}, 
				{ mMinConstant, 0.0f, 0.0f, 1.0f}});
			mCurves[1] = TAnimationCurve<float>({
				{ mMinConstant, 0.0f, 0.0f, 0.0f}, 
				{ mMinConstant, 0.0f, 0.0f, 1.0f}});
			break;
		case PDT_RandomRange: 
			mMinConstant = mValue.getMinConstant();
			mMaxConstant = mValue.getMaxConstant();
			mCurves[0] = TAnimationCurve<float>({
				{ mMinConstant, 0.0f, 0.0f, 0.0f}, 
				{ mMinConstant, 0.0f, 0.0f, 1.0f}});
			mCurves[1] = TAnimationCurve<float>({
				{ mMaxConstant, 0.0f, 0.0f, 0.0f}, 
				{ mMaxConstant, 0.0f, 0.0f, 1.0f}});
			break;
		case PDT_Curve: 
			mCurves[0] = mValue.getMinCurve();
			mCurves[1] = mValue.getMinCurve();
			mMinConstant = mCurves[0].evaluate(0.0f);
			mMaxConstant = mCurves[1].evaluate(0.0f);
			break;
		case PDT_RandomCurveRange: 
			mCurves[0] = mValue.getMinCurve();
			mCurves[1] = mValue.getMaxCurve();
			mMinConstant = mCurves[0].evaluate(0.0f);
			mMaxConstant = mCurves[1].evaluate(0.0f);
			break;
		}

		rebuild();
	}

	bool GUIFloatDistributionField::hasInputFocus() const
	{
		if(mMinInput && mMinInput->hasInputFocus())
			return true;

		if(mMaxInput && mMaxInput->hasInputFocus())
			return true;

		return false;
	}

	void GUIFloatDistributionField::setTint(const Color& color)
	{
		mDropDownButton->setTint(color);

		if (mLabel)
			mLabel->setTint(color);

		if(mMinInput)
			mMinInput->setTint(color);

		if(mMaxInput)
			mMaxInput->setTint(color);

		if(mCurveDisplay)
			mCurveDisplay->setTint(color);
	}

	Vector2I GUIFloatDistributionField::_getOptimalSize() const
	{
		Vector2I optimalsize = mDropDownButton->_getOptimalSize();

		if(mLabel)
		{
			optimalsize.x += mLabel->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mLabel->_getOptimalSize().y);
		}

		if(mMinInput)
		{
			optimalsize.x += mMinInput->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mMinInput->_getOptimalSize().y);
		}

		if(mMaxInput)
		{
			optimalsize.x += mMaxInput->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mMaxInput->_getOptimalSize().y);
		}

		if(mCurveDisplay)
		{
			optimalsize.x += mCurveDisplay->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, 50);
		}

		return optimalsize;
	}

	void GUIFloatDistributionField::styleUpdated()
	{
		mDropDownButton->setStyle(getSubStyleName(DROP_DOWN_FIELD_STYLE_TYPE));

		if (mLabel)
			mLabel->setStyle(getSubStyleName(getLabelStyleType()));

		if (mMinInput)
			mMinInput->setStyle(getSubStyleName(FLOAT_FIELD_STYLE_TYPE));

		if (mMaxInput)
			mMaxInput->setStyle(getSubStyleName(FLOAT_FIELD_STYLE_TYPE));

		if (mCurveDisplay)
			mCurveDisplay->setStyle(getSubStyleName(CURVES_FIELD_STYLE_TYPE));
	}

	void GUIFloatDistributionField::rebuild()
	{
		if(mLabel)
			mLayout->removeElement(mLabel);

		mLayout->clear();
		mLayout->addElement(mLabel);

		switch (mValue.getType())
		{
		default:
		case PDT_Constant:
			mMinInput = GUIFloatField::create(HString("Constant"), 50, GUIOptions(), getSubStyleName(FLOAT_FIELD_STYLE_TYPE));
			mMaxInput = nullptr;
			mCurveDisplay = nullptr;

			mMinInput->setValue(mMinConstant);
			mMinInput->onValueChanged.connect([this](float value)
			{
				mMinConstant = value;
				mValue = FloatDistribution(value);

				onConstantModified();
			});
			mMinInput->onConfirm.connect([this]() { onConstantConfirmed(); });

			mLayout->addElement(mMinInput);
			break;
		case PDT_RandomRange: 
			mMinInput = GUIFloatField::create(HString("Min."), 40, GUIOptions(), getSubStyleName(FLOAT_FIELD_STYLE_TYPE));
			mMaxInput = GUIFloatField::create(HString("Max."), 40, GUIOptions(), getSubStyleName(FLOAT_FIELD_STYLE_TYPE));
			mCurveDisplay = nullptr;

			mMinInput->setValue(mMinConstant);
			mMinInput->onValueChanged.connect([this](float value)
			{
				mMinConstant = value;
				mValue = FloatDistribution(value, mMaxConstant);

				onConstantModified();
			});
			mMinInput->onConfirm.connect([this]() { onConstantConfirmed(); });

			mMaxInput->setValue(mMaxConstant);
			mMaxInput->onValueChanged.connect([this](float value)
			{
				mMaxConstant = value;
				mValue = FloatDistribution(mMinConstant, value);

				onConstantModified();
			});
			mMaxInput->onConfirm.connect([this]() { onConstantConfirmed(); });

			mLayout->addElement(mMinInput);
			mLayout->addElement(mMaxInput);
			break;
		case PDT_Curve: 
			mMinInput = nullptr;
			mMaxInput = nullptr;
			mCurveDisplay = GUICurves::create(CurveDrawOption::DrawMarkers, 
				getSubStyleName(CURVES_FIELD_STYLE_TYPE));

			mCurveDisplay->setCurves(
				{
					CurveDrawInfo(mValue.getMinCurve(), Color::BansheeOrange)
				});

			mCurveDisplay->setPadding(3);
			mCurveDisplay->centerAndZoom();
			mCurveDisplay->onClicked.connect([this](){ onClicked(); });

			mLayout->addElement(mCurveDisplay);
			break;
		case PDT_RandomCurveRange: 
			mMinInput = nullptr;
			mMaxInput = nullptr;
			mCurveDisplay = GUICurves::create(CurveDrawOption::DrawMarkers | CurveDrawOption::DrawRange, 
				getSubStyleName(CURVES_FIELD_STYLE_TYPE));

			mCurveDisplay->setCurves(
				{
					CurveDrawInfo(mValue.getMinCurve(), Color::BansheeOrange),
					CurveDrawInfo(mValue.getMaxCurve(), Color::Red)
				});

			mCurveDisplay->setPadding(3);
			mCurveDisplay->centerAndZoom();
			mCurveDisplay->onClicked.connect([this](){ onClicked(); });

			mLayout->addElement(mCurveDisplay);
			break;
		}

		mDropDownButton = GUIButton::create(HString::dummy(), GUIOptions(GUIOption::fixedWidth(50)), 
			getSubStyleName(DROP_DOWN_FIELD_STYLE_TYPE));
		mDropDownButton->onClick.connect([this]()
		{
			const Rect2I bounds = getBounds();
			const Vector2I center(bounds.x + bounds.width / 2, bounds.y + bounds.height / 2);

			mContextMenu->open(center, *mParentWidget);
		});

		mLayout->addNewElement<GUIFixedSpace>(10);
		mLayout->addElement(mDropDownButton);
	}

	const String& GUIFloatDistributionField::getGUITypeName()
	{
		static String typeName = "GUIFloatDistributionField";
		return typeName;
	}
}