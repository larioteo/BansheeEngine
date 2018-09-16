//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2018 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "GUI/BsGUICurvesField.h"
#include "GUI/BsGUILayout.h"
#include "GUI/BsGUILabel.h"
#include "GUI/BsGUICurves.h"

using namespace std::placeholders;

namespace bs
{
	GUICurvesField::GUICurvesField(const PrivatelyConstruct& dummy, const GUIContent& labelContent, UINT32 labelWidth,
		const String& style, const GUIDimensions& dimensions, bool withLabel)
		: TGUIField(dummy, labelContent, labelWidth, style, dimensions, withLabel)
	{
		mCurves = GUICurves::create(getSubStyleName(getCurveStyleType()));
		mCurves->onClicked.connect(std::bind(&GUICurvesField::clicked, this));

		mLayout->addElement(mCurves);
	}

	void GUICurvesField::setCurve(const TAnimationCurve<float>& curve)
	{
		const Vector<CurveDrawInfo> drawInfos =
		{
			CurveDrawInfo(curve, Color::BansheeOrange)
		};

		mCurves->setCurves(drawInfos);
	}


	void GUICurvesField::setCurveRange(const TAnimationCurve<float>& curveA, const TAnimationCurve<float>& curveB)
	{
		const Vector<CurveDrawInfo> drawInfos =
		{
			CurveDrawInfo(curveA, Color::BansheeOrange),
			CurveDrawInfo(curveB, Color::Green)
		};

		mCurves->setCurves(drawInfos);
	}

	void GUICurvesField::setTint(const Color& color)
	{
		if (mLabel != nullptr)
			mLabel->setTint(color);

		mCurves->setTint(color);
	}

	Vector2I GUICurvesField::_getOptimalSize() const
	{
		Vector2I optimalsize = mCurves->_getOptimalSize();

		if(mLabel != nullptr)
		{
			optimalsize.x += mLabel->_getOptimalSize().x;
			optimalsize.y = std::max(optimalsize.y, mLabel->_getOptimalSize().y);
		}

		return optimalsize;
	}

	void GUICurvesField::styleUpdated()
	{
		if (mLabel != nullptr)
			mLabel->setStyle(getSubStyleName(getLabelStyleType()));

		mCurves->setStyle(getSubStyleName(getCurveStyleType()));
	}

	void GUICurvesField::clicked()
	{
		onClicked();
	}

	const String& GUICurvesField::getGUITypeName()
	{
		static String typeName = "GUICurvesField";
		return typeName;
	}

	const String& GUICurvesField::getCurveStyleType()
	{
		static String STYLE_TYPE = "EditorFieldCurves";
		return STYLE_TYPE;
	}
}