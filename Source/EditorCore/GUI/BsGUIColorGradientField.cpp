//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "GUI/BsGUIColorGradientField.h"
#include "GUI/BsGUILayout.h"
#include "GUI/BsGUILabel.h"
#include "GUI/BsGUIColorGradient.h"

using namespace std::placeholders;

namespace bs
{
	GUIColorGradientField::GUIColorGradientField(const PrivatelyConstruct& dummy, const GUIContent& labelContent, 
		UINT32 labelWidth, const String& style, const GUIDimensions& dimensions, bool withLabel)
		: TGUIField(dummy, labelContent, labelWidth, style, dimensions, withLabel)
	{
		mGradient = GUIColorGradient::create(getSubStyleName(GRADIENT_FIELD_STYLE_TYPE));
		mGradient->onClicked.connect(std::bind(&GUIColorGradientField::clicked, this));

		mLayout->addElement(mGradient);
	}

	void GUIColorGradientField::setValue(const ColorGradient& gradient)
	{
		mValue = gradient;
		mGradient->setGradient(gradient);
	}

	void GUIColorGradientField::setTint(const Color& color)
	{
		if (mLabel != nullptr)
			mLabel->setTint(color);

		mGradient->setTint(color);
	}

	Vector2I GUIColorGradientField::_getOptimalSize() const
	{
		Vector2I optimalsize = mGradient->_getOptimalSize();

		if(mLabel != nullptr)
		{
			optimalsize.x += mLabel->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mLabel->_getOptimalSize().y);
		}

		return optimalsize;
	}

	void GUIColorGradientField::styleUpdated()
	{
		if (mLabel != nullptr)
			mLabel->setStyle(getSubStyleName(getLabelStyleType()));

		mGradient->setStyle(getSubStyleName(GRADIENT_FIELD_STYLE_TYPE));
	}

	void GUIColorGradientField::clicked()
	{
		onClicked();
	}

	const String& GUIColorGradientField::getGUITypeName()
	{
		static String typeName = "GUIColorGradientField";
		return typeName;
	}
}