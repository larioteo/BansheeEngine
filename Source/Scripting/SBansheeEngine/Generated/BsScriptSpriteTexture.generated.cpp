#include "BsScriptSpriteTexture.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfEngine/2D/BsSpriteTexture.h"
#include "BsScriptResourceManager.h"
#include "BsScriptTexture.generated.h"
#include "Wrappers/BsScriptVector.h"
#include "BsScriptSpriteTexture.generated.h"

namespace bs
{
	ScriptSpriteTexture::ScriptSpriteTexture(MonoObject* managedInstance, const ResourceHandle<SpriteTexture>& value)
		:TScriptResource(managedInstance, value)
	{
	}

	void ScriptSpriteTexture::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_setTexture", (void*)&ScriptSpriteTexture::Internal_setTexture);
		metaData.scriptClass->addInternalCall("Internal_getTexture", (void*)&ScriptSpriteTexture::Internal_getTexture);
		metaData.scriptClass->addInternalCall("Internal_setOffset", (void*)&ScriptSpriteTexture::Internal_setOffset);
		metaData.scriptClass->addInternalCall("Internal_getOffset", (void*)&ScriptSpriteTexture::Internal_getOffset);
		metaData.scriptClass->addInternalCall("Internal_setScale", (void*)&ScriptSpriteTexture::Internal_setScale);
		metaData.scriptClass->addInternalCall("Internal_getScale", (void*)&ScriptSpriteTexture::Internal_getScale);
		metaData.scriptClass->addInternalCall("Internal_getWidth", (void*)&ScriptSpriteTexture::Internal_getWidth);
		metaData.scriptClass->addInternalCall("Internal_getHeight", (void*)&ScriptSpriteTexture::Internal_getHeight);
		metaData.scriptClass->addInternalCall("Internal_create", (void*)&ScriptSpriteTexture::Internal_create);
		metaData.scriptClass->addInternalCall("Internal_create0", (void*)&ScriptSpriteTexture::Internal_create0);

	}

	 MonoObject*ScriptSpriteTexture::createInstance()
	{
		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		return metaData.scriptClass->createInstance("bool", ctorParams);
	}
	void ScriptSpriteTexture::Internal_setTexture(ScriptSpriteTexture* thisPtr, MonoObject* texture)
	{
		ResourceHandle<Texture> tmptexture;
		ScriptTexture* scripttexture;
		scripttexture = ScriptTexture::toNative(texture);
		if(scripttexture != nullptr)
			tmptexture = scripttexture->getHandle();
		thisPtr->getHandle()->setTexture(tmptexture);
	}

	MonoObject* ScriptSpriteTexture::Internal_getTexture(ScriptSpriteTexture* thisPtr)
	{
		ResourceHandle<Texture> tmp__output;
		tmp__output = thisPtr->getHandle()->getTexture();

		MonoObject* __output;
		ScriptResourceBase* script__output;
		script__output = ScriptResourceManager::instance().getScriptResource(tmp__output, true);
		if(script__output != nullptr)
			__output = script__output->getManagedInstance();
		else
			__output = nullptr;

		return __output;
	}

	void ScriptSpriteTexture::Internal_setOffset(ScriptSpriteTexture* thisPtr, Vector2* offset)
	{
		thisPtr->getHandle()->setOffset(*offset);
	}

	void ScriptSpriteTexture::Internal_getOffset(ScriptSpriteTexture* thisPtr, Vector2* __output)
	{
		Vector2 tmp__output;
		tmp__output = thisPtr->getHandle()->getOffset();

		*__output = tmp__output;
	}

	void ScriptSpriteTexture::Internal_setScale(ScriptSpriteTexture* thisPtr, Vector2* scale)
	{
		thisPtr->getHandle()->setScale(*scale);
	}

	void ScriptSpriteTexture::Internal_getScale(ScriptSpriteTexture* thisPtr, Vector2* __output)
	{
		Vector2 tmp__output;
		tmp__output = thisPtr->getHandle()->getScale();

		*__output = tmp__output;
	}

	uint32_t ScriptSpriteTexture::Internal_getWidth(ScriptSpriteTexture* thisPtr)
	{
		uint32_t tmp__output;
		tmp__output = thisPtr->getHandle()->getWidth();

		uint32_t __output;
		__output = tmp__output;

		return __output;
	}

	uint32_t ScriptSpriteTexture::Internal_getHeight(ScriptSpriteTexture* thisPtr)
	{
		uint32_t tmp__output;
		tmp__output = thisPtr->getHandle()->getHeight();

		uint32_t __output;
		__output = tmp__output;

		return __output;
	}

	void ScriptSpriteTexture::Internal_create(MonoObject* managedInstance, MonoObject* texture)
	{
		ResourceHandle<Texture> tmptexture;
		ScriptTexture* scripttexture;
		scripttexture = ScriptTexture::toNative(texture);
		if(scripttexture != nullptr)
			tmptexture = scripttexture->getHandle();
		ResourceHandle<SpriteTexture> instance = SpriteTexture::create(tmptexture);
		ScriptResourceManager::instance().createBuiltinScriptResource(instance, managedInstance);
	}

	void ScriptSpriteTexture::Internal_create0(MonoObject* managedInstance, Vector2* uvOffset, Vector2* uvScale, MonoObject* texture)
	{
		ResourceHandle<Texture> tmptexture;
		ScriptTexture* scripttexture;
		scripttexture = ScriptTexture::toNative(texture);
		if(scripttexture != nullptr)
			tmptexture = scripttexture->getHandle();
		ResourceHandle<SpriteTexture> instance = SpriteTexture::create(*uvOffset, *uvScale, tmptexture);
		ScriptResourceManager::instance().createBuiltinScriptResource(instance, managedInstance);
	}
}
