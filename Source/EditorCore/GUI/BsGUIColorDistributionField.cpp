//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2018 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "GUI/BsGUIColorDistributionField.h"
#include "GUI/BsGUILayout.h"
#include "GUI/BsGUILabel.h"
#include "GUI/BsGUIColorField.h"
#include "GUI/BsGUIColorGradientField.h"
#include "GUI/BsGUICurves.h"
#include "GUI/BsGUIButton.h"
#include "GUI/BsGUIContextMenu.h"
#include "GUI/BsGUISpace.h"

using namespace std::placeholders;

namespace bs
{
	GUIColorDistributionField::GUIColorDistributionField(const PrivatelyConstruct& dummy, const GUIContent& labelContent, 
		UINT32 labelWidth, const String& style, const GUIDimensions& dimensions, bool withLabel)
		: TGUIField(dummy, labelContent, labelWidth, style, dimensions, withLabel)
	{
		mContextMenu = bs_shared_ptr_new<GUIContextMenu>();

		mContextMenu->addMenuItem("Constant", [this]()
		{
			mValue = ColorDistribution(mMinConstant);
			mPropertyType = PDT_Constant;
			rebuild();
		}, 50);

		mContextMenu->addMenuItem("Range", [this]()
		{
			mValue = ColorDistribution(mMinConstant, mMaxConstant);
			mPropertyType = PDT_RandomRange;
			rebuild();
		}, 40);

		mContextMenu->addMenuItem("Gradient", [this]()
		{
			mValue = ColorDistribution(mMinGradient);
			mPropertyType = PDT_Curve;
			rebuild();
		}, 30);

		mContextMenu->addMenuItem("Gradient range", [this]()
		{
			mValue = ColorDistribution(mMinGradient, mMaxGradient);
			mPropertyType = PDT_RandomCurveRange;
			rebuild();
		}, 20);

		rebuild();
	}

	void GUIColorDistributionField::setValue(const ColorDistribution& value)
	{
		mValue = value;

		switch (mPropertyType)
		{
		default:
		case PDT_Constant:
			mMinConstant = mValue.getMinConstant();
			mMaxConstant = mMinConstant;
			mMinGradient = mMinConstant;
			mMaxGradient = mMinConstant;

			mMinColorField->setValue(mMinConstant);
			break;
		case PDT_RandomRange: 
			mMinConstant = mValue.getMinConstant();
			mMaxConstant = mValue.getMaxConstant();
			mMinGradient = mMinConstant;
			mMaxGradient = mMaxConstant;

			mMinColorField->setValue(mMinConstant);
			mMaxColorField->setValue(mMaxConstant);
			break;
		case PDT_Curve: 
			mMinGradient = mValue.getMinGradient();
			mMaxGradient = mMinGradient;
			mMinConstant = Color::fromRGBA(mMinGradient.evaluate(0.0f));
			mMaxConstant = Color::fromRGBA(mMaxGradient.evaluate(0.0f));

			mMinGradientField->setValue(mMinGradient);
			break;
		case PDT_RandomCurveRange: 
			mMinGradient = mValue.getMinGradient();
			mMaxGradient = mValue.getMaxGradient();
			mMinConstant = Color::fromRGBA(mMinGradient.evaluate(0.0f));
			mMaxConstant = Color::fromRGBA(mMaxGradient.evaluate(0.0f));

			mMinGradientField->setValue(mMinGradient);
			mMaxGradientField->setValue(mMaxGradient);
			break;
		}
	}

	void GUIColorDistributionField::setTint(const Color& color)
	{
		mDropDownButton->setTint(color);

		if (mLabel)
			mLabel->setTint(color);

		if(mMinColorField)
			mMinColorField->setTint(color);

		if(mMaxColorField)
			mMaxColorField->setTint(color);

		if(mMinGradientField)
			mMinGradientField->setTint(color);

		if(mMaxGradientField)
			mMaxGradientField->setTint(color);
	}

	Vector2I GUIColorDistributionField::_getOptimalSize() const
	{
		Vector2I optimalsize = mDropDownButton->_getOptimalSize();

		if(mLabel)
		{
			optimalsize.x += mLabel->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mLabel->_getOptimalSize().y);
		}

		if(mMinColorField)
		{
			optimalsize.x += mMinColorField->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mMinColorField->_getOptimalSize().y);
		}

		if(mMaxColorField)
		{
			optimalsize.x += mMaxColorField->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mMaxColorField->_getOptimalSize().y);
		}

		if(mMinGradientField)
		{
			optimalsize.x += mMinGradientField->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mMinGradientField->_getOptimalSize().y);
		}

		if(mMaxGradientField)
		{
			optimalsize.x += mMaxGradientField->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mMaxGradientField->_getOptimalSize().y);
		}

		return optimalsize;
	}

	void GUIColorDistributionField::styleUpdated()
	{
		mDropDownButton->setStyle(getSubStyleName(DROP_DOWN_FIELD_STYLE_TYPE));

		if (mLabel)
			mLabel->setStyle(getSubStyleName(getLabelStyleType()));

		if (mMinColorField)
			mMinColorField->setStyle(getSubStyleName(COLOR_FIELD_STYLE_TYPE));

		if (mMaxColorField)
			mMaxColorField->setStyle(getSubStyleName(COLOR_FIELD_STYLE_TYPE));

		if (mMinGradientField)
			mMinGradientField->setStyle(getSubStyleName(COLOR_GRADIENT_FIELD_STYLE_TYPE));

		if (mMaxGradientField)
			mMaxGradientField->setStyle(getSubStyleName(COLOR_GRADIENT_FIELD_STYLE_TYPE));
	}

	void GUIColorDistributionField::rebuild()
	{
		if(mLabel)
			mLayout->removeElement(mLabel);

		mLayout->clear();
		mLayout->addElement(mLabel);

		switch (mPropertyType)
		{
		default:
		case PDT_Constant:
			mMinColorField = GUIColorField::create(GUIOptions(), getSubStyleName(COLOR_FIELD_STYLE_TYPE));
			mMaxColorField = nullptr;
			mMinGradientField = nullptr;
			mMaxGradientField = nullptr;

			mMinColorField->setValue(mMinConstant);
			mMinColorField->onClicked.connect([this]() { onMinClicked(); });

			mLayout->addElement(mMinColorField);
			break;
		case PDT_RandomRange: 
			mMinColorField = GUIColorField::create(HString("Min."), 40, GUIOptions(), getSubStyleName(COLOR_FIELD_STYLE_TYPE));
			mMaxColorField = GUIColorField::create(HString("Max."), 40, GUIOptions(), getSubStyleName(COLOR_FIELD_STYLE_TYPE));
			mMinGradientField = nullptr;
			mMaxGradientField = nullptr;

			mMinColorField->setValue(mMinConstant);
			mMinColorField->onClicked.connect([this]() { onMinClicked(); });

			mMaxColorField->setValue(mMaxConstant);
			mMaxColorField->onClicked.connect([this]() { onMaxClicked(); });

			mLayout->addElement(mMinColorField);
			mLayout->addElement(mMaxColorField);
			break;
		case PDT_Curve: 
			mMinColorField = nullptr;
			mMaxColorField = nullptr;
			mMinGradientField = GUIColorGradientField::create(HString("Gradient"), 
				getSubStyleName(COLOR_GRADIENT_FIELD_STYLE_TYPE));
			mMaxGradientField = nullptr;

			mMinGradientField->setValue(mMinGradient);
			mMinGradientField->onClicked.connect([this](){ onMinClicked(); });

			mLayout->addElement(mMinGradientField);
			break;
		case PDT_RandomCurveRange: 
			mMinColorField = nullptr;
			mMaxColorField = nullptr;
			mMinGradientField = GUIColorGradientField::create(HString("Min. "),
				getSubStyleName(COLOR_GRADIENT_FIELD_STYLE_TYPE));

			mMinGradientField->setValue(mMinGradient);
			mMinGradientField->onClicked.connect([this](){ onMinClicked(); });

			mMaxGradientField = GUIColorGradientField::create(HString("Max. "),
				getSubStyleName(COLOR_GRADIENT_FIELD_STYLE_TYPE));

			mMaxGradientField->setValue(mMaxGradient);
			mMaxGradientField->onClicked.connect([this](){ onMaxClicked(); });

			mLayout->addElement(mMinGradientField);
			mLayout->addElement(mMaxGradientField);
			break;
		}

		mDropDownButton = GUIButton::create(HString::dummy(), getSubStyleName(DROP_DOWN_FIELD_STYLE_TYPE));
		mDropDownButton->onClick.connect([this]()
		{
			const Rect2I bounds = mDropDownButton->getBounds(mParentWidget->getPanel());
			const Vector2I center(bounds.x + bounds.width / 2, bounds.y + bounds.height / 2);

			mContextMenu->open(center, *mParentWidget);
		});

		mLayout->addNewElement<GUIFixedSpace>(10);
		mLayout->addElement(mDropDownButton);
	}

	const String& GUIColorDistributionField::getGUITypeName()
	{
		static String typeName = "GUIColorDistributionField";
		return typeName;
	}
}