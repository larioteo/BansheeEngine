#include "BsScriptCSkybox.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Components/BsCSkybox.h"
#include "BsScriptResourceManager.h"
#include "BsScriptTexture.generated.h"

namespace bs
{
	ScriptCSkybox::ScriptCSkybox(MonoObject* managedInstance, const GameObjectHandle<CSkybox>& value)
		:TScriptComponent(managedInstance, value)
	{
	}

	void ScriptCSkybox::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_getTexture", (void*)&ScriptCSkybox::Internal_getTexture);
		metaData.scriptClass->addInternalCall("Internal_setTexture", (void*)&ScriptCSkybox::Internal_setTexture);
		metaData.scriptClass->addInternalCall("Internal_setBrightness", (void*)&ScriptCSkybox::Internal_setBrightness);
		metaData.scriptClass->addInternalCall("Internal_getBrightness", (void*)&ScriptCSkybox::Internal_getBrightness);

	}

	MonoObject* ScriptCSkybox::Internal_getTexture(ScriptCSkybox* thisPtr)
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

	void ScriptCSkybox::Internal_setTexture(ScriptCSkybox* thisPtr, MonoObject* texture)
	{
		ResourceHandle<Texture> tmptexture;
		ScriptTexture* scripttexture;
		scripttexture = ScriptTexture::toNative(texture);
		if(scripttexture != nullptr)
			tmptexture = scripttexture->getHandle();
		thisPtr->getHandle()->setTexture(tmptexture);
	}

	void ScriptCSkybox::Internal_setBrightness(ScriptCSkybox* thisPtr, float brightness)
	{
		thisPtr->getHandle()->setBrightness(brightness);
	}

	float ScriptCSkybox::Internal_getBrightness(ScriptCSkybox* thisPtr)
	{
		float tmp__output;
		tmp__output = thisPtr->getHandle()->getBrightness();

		float __output;
		__output = tmp__output;

		return __output;
	}
}
