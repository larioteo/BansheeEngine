//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "GUI/BsGUIColorGradient.h"
#include "2D/BsImageSprite.h"
#include "GUI/BsGUIDimensions.h"
#include "GUI/BsGUIMouseEvent.h"
#include "GUI/BsGUIHelper.h"
#include "Resources/BsBuiltinResources.h"
#include "Image/BsSpriteTexture.h"
#include "Image/BsTexture.h"

namespace bs
{
	template<class T, class SELF>
	const float TGUIColorGradient<T, SELF>::ALPHA_SPLIT_POSITION = 0.75f;

	template<class T, class SELF>
	TGUIColorGradient<T, SELF>::TGUIColorGradient(const String& styleName, const GUIDimensions& dimensions)
		:GUIElement(styleName, dimensions)
	{
		mColorSprite = bs_new<ImageSprite>();
		mAlphaSprite = bs_new<ImageSprite>();

		mColorImageDesc.texture = BuiltinResources::instance().getWhiteSpriteTexture();
		mAlphaImageDesc.texture = BuiltinResources::instance().getWhiteSpriteTexture();
	}

	template<class T, class SELF>
	TGUIColorGradient<T, SELF>::~TGUIColorGradient()
	{
		bs_delete(mColorSprite);
		bs_delete(mAlphaSprite);
	}

	template<class T, class SELF>
	const String& TGUIColorGradient<T, SELF>::getGUITypeName()
	{
		static String name = "ColorGradient";
		return name;
	}

	template<class T, class SELF>
	SELF* TGUIColorGradient<T, SELF>::create(const String& styleName)
	{
		return new (bs_alloc<SELF>()) SELF(getStyleName<SELF>(styleName), GUIDimensions::create());
	}

	template<class T, class SELF>
	SELF* TGUIColorGradient<T, SELF>::create(const GUIOptions& options, const String& styleName)
	{
		return new (bs_alloc<SELF>()) SELF(getStyleName<SELF>(styleName), GUIDimensions::create(options));
	}

	template<class T, class SELF>
	void TGUIColorGradient<T, SELF>::setGradient(const T& color)
	{
		if(mValue == color)
			return;

		mValue = color;
		_markContentAsDirty();
	}

	template<class T, class SELF>
	UINT32 TGUIColorGradient<T, SELF>::_getNumRenderElements() const
	{
		UINT32 numElements = mColorSprite->getNumRenderElements();
		numElements += mAlphaSprite->getNumRenderElements();

		return numElements;
	}

	template<class T, class SELF>
	const SpriteMaterialInfo& TGUIColorGradient<T, SELF>::_getMaterial(UINT32 renderElementIdx, SpriteMaterial** material) const
	{
		UINT32 alphaSpriteIdx = mColorSprite->getNumRenderElements();

		if (renderElementIdx >= alphaSpriteIdx)
		{
			*material = mAlphaSprite->getMaterial(alphaSpriteIdx - renderElementIdx);
			return mAlphaSprite->getMaterialInfo(alphaSpriteIdx - renderElementIdx);
		}
		else
		{
			*material = mColorSprite->getMaterial(renderElementIdx);
			return mColorSprite->getMaterialInfo(renderElementIdx);
		}
	}
	template<class T, class SELF>
	void TGUIColorGradient<T, SELF>::_getMeshInfo(UINT32 renderElementIdx, UINT32& numVertices, UINT32& numIndices, GUIMeshType& type) const
	{
		UINT32 alphaSpriteIdx = mColorSprite->getNumRenderElements();

		UINT32 numQuads = 0;
		if(renderElementIdx >= alphaSpriteIdx)
			numQuads = mAlphaSprite->getNumQuads(alphaSpriteIdx - renderElementIdx);
		else
			numQuads = mColorSprite->getNumQuads(renderElementIdx);

		numVertices = numQuads * 4;
		numIndices = numQuads * 6;
		type = GUIMeshType::Triangle;
	}

	template<class T, class SELF>
	void TGUIColorGradient<T, SELF>::updateRenderElementsInternal()
	{
		const Color color = getTint();

		mColorImageDesc.color = color;
		mAlphaImageDesc.color = color;

		mColorImageDesc.width = mLayoutData.area.width;
		mColorImageDesc.height = (UINT32)(mLayoutData.area.height * ALPHA_SPLIT_POSITION);

		mAlphaImageDesc.width = mLayoutData.area.width;
		mAlphaImageDesc.height = mLayoutData.area.height - mColorImageDesc.height;

		mColorImageDesc.texture = SpriteTexture::create(generateGradientTexture(mValue, mLayoutData.area.width, false)); 
		mAlphaImageDesc.texture = SpriteTexture::create(generateGradientTexture(mValue, mLayoutData.area.width, true)); 

		mColorSprite->update(mColorImageDesc, (UINT64)_getParentWidget());
		mAlphaSprite->update(mAlphaImageDesc, (UINT64)_getParentWidget());

		GUIElement::updateRenderElementsInternal();
	}

	template<class T, class SELF>
	Vector2I TGUIColorGradient<T, SELF>::_getOptimalSize() const
	{
		return GUIHelper::calcOptimalContentsSize(Vector2I(80, 10), *_getStyle(), _getDimensions()); // Arbitrary size
	}

	template<class T, class SELF>
	void TGUIColorGradient<T, SELF>::_fillBuffer(UINT8* vertices, UINT32* indices, UINT32 vertexOffset, UINT32 indexOffset,
		UINT32 maxNumVerts, UINT32 maxNumIndices, UINT32 renderElementIdx) const
	{
		UINT8* uvs = vertices + sizeof(Vector2);
		UINT32 vertexStride = sizeof(Vector2) * 2;
		UINT32 indexStride = sizeof(UINT32);
		
		UINT32 alphaSpriteIdx = mColorSprite->getNumRenderElements();
		
		Vector2I offset(mLayoutData.area.x, mLayoutData.area.y);
		if(renderElementIdx < alphaSpriteIdx)
		{
			mColorSprite->fillBuffer(vertices, uvs, indices, vertexOffset, indexOffset, maxNumVerts, maxNumIndices,
				vertexStride, indexStride, renderElementIdx, offset, mLayoutData.getLocalClipRect());
		}
		else if(renderElementIdx >= alphaSpriteIdx)
		{
			Vector2I alphaOffset = offset;
			UINT32 yOffset = (UINT32)(mLayoutData.area.height * ALPHA_SPLIT_POSITION);
			alphaOffset.y += yOffset;

			Rect2I alphaClipRect = mLayoutData.getLocalClipRect();
			alphaClipRect.y -= yOffset;

			mAlphaSprite->fillBuffer(vertices, uvs, indices, vertexOffset, indexOffset, maxNumVerts, maxNumIndices,
				vertexStride, indexStride, alphaSpriteIdx - renderElementIdx, alphaOffset, alphaClipRect);
		}
	}

	template<class T, class SELF>
	bool TGUIColorGradient<T, SELF>::_mouseEvent(const GUIMouseEvent& ev)
	{
		if(ev.getType() == GUIMouseEventType::MouseUp)
		{
			if (!_isDisabled())
				onClicked();

			return true;
		}

		return false;
	}

	template<class T, class SELF>
	HTexture TGUIColorGradient<T, SELF>::generateGradientTexture(const T& gradient, UINT32 width, bool alpha)
	{
		SPtr<PixelData> pixelData = PixelData::create(std::max(width, 1U), 1, 1, PF_RGBA8);

		const float halfPixel = 0.5f / width;
		for (UINT32 i = 0; i < width; i++)
		{
			const float t = i / (float)width + halfPixel;

			Color value = impl::TGradientHelper<typename T::ColorType>::fromInternalColor(gradient.evaluate(t));

			if (alpha)
				value = Color::lerp(value.a, Color::Black, Color::White);

			value.a = 1.0f;
			pixelData->setColorAt(value, i, 0);
		}
		
		return Texture::create(pixelData);
	}

	template class BS_ED_EXPORT TGUIColorGradient<ColorGradient, GUIColorGradient>;
	template class BS_ED_EXPORT TGUIColorGradient<ColorGradientHDR, GUIColorGradientHDR>;
}
