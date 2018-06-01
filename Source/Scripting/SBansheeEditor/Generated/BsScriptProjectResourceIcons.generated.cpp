#include "BsScriptProjectResourceIcons.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "BsScriptResourceManager.h"
#include "BsScriptTexture.generated.h"

namespace bs
{
	ScriptProjectResourceIcons::ScriptProjectResourceIcons(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptProjectResourceIcons::initRuntimeData()
	{ }

	MonoObject*ScriptProjectResourceIcons::box(const __ProjectResourceIconsInterop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__ProjectResourceIconsInterop ScriptProjectResourceIcons::unbox(MonoObject* value)
	{
		return *(__ProjectResourceIconsInterop*)MonoUtil::unbox(value);
	}

	ProjectResourceIcons ScriptProjectResourceIcons::fromInterop(const __ProjectResourceIconsInterop& value)
	{
		ProjectResourceIcons output;
		ResourceHandle<Texture> tmpicon16;
		ScriptTexture* scripticon16;
		scripticon16 = ScriptTexture::toNative(value.icon16);
		if(scripticon16 != nullptr)
			tmpicon16 = scripticon16->getHandle();
		output.icon16 = tmpicon16;
		ResourceHandle<Texture> tmpicon32;
		ScriptTexture* scripticon32;
		scripticon32 = ScriptTexture::toNative(value.icon32);
		if(scripticon32 != nullptr)
			tmpicon32 = scripticon32->getHandle();
		output.icon32 = tmpicon32;
		ResourceHandle<Texture> tmpicon48;
		ScriptTexture* scripticon48;
		scripticon48 = ScriptTexture::toNative(value.icon48);
		if(scripticon48 != nullptr)
			tmpicon48 = scripticon48->getHandle();
		output.icon48 = tmpicon48;
		ResourceHandle<Texture> tmpicon64;
		ScriptTexture* scripticon64;
		scripticon64 = ScriptTexture::toNative(value.icon64);
		if(scripticon64 != nullptr)
			tmpicon64 = scripticon64->getHandle();
		output.icon64 = tmpicon64;
		ResourceHandle<Texture> tmpicon96;
		ScriptTexture* scripticon96;
		scripticon96 = ScriptTexture::toNative(value.icon96);
		if(scripticon96 != nullptr)
			tmpicon96 = scripticon96->getHandle();
		output.icon96 = tmpicon96;
		ResourceHandle<Texture> tmpicon128;
		ScriptTexture* scripticon128;
		scripticon128 = ScriptTexture::toNative(value.icon128);
		if(scripticon128 != nullptr)
			tmpicon128 = scripticon128->getHandle();
		output.icon128 = tmpicon128;
		ResourceHandle<Texture> tmpicon192;
		ScriptTexture* scripticon192;
		scripticon192 = ScriptTexture::toNative(value.icon192);
		if(scripticon192 != nullptr)
			tmpicon192 = scripticon192->getHandle();
		output.icon192 = tmpicon192;
		ResourceHandle<Texture> tmpicon256;
		ScriptTexture* scripticon256;
		scripticon256 = ScriptTexture::toNative(value.icon256);
		if(scripticon256 != nullptr)
			tmpicon256 = scripticon256->getHandle();
		output.icon256 = tmpicon256;

		return output;
	}

	__ProjectResourceIconsInterop ScriptProjectResourceIcons::toInterop(const ProjectResourceIcons& value)
	{
		__ProjectResourceIconsInterop output;
		ScriptResourceBase* scripticon16;
		scripticon16 = ScriptResourceManager::instance().getScriptResource(value.icon16, true);
		MonoObject* tmpicon16;
		if(scripticon16 != nullptr)
			tmpicon16 = scripticon16->getManagedInstance();
		else
			tmpicon16 = nullptr;
		output.icon16 = tmpicon16;
		ScriptResourceBase* scripticon32;
		scripticon32 = ScriptResourceManager::instance().getScriptResource(value.icon32, true);
		MonoObject* tmpicon32;
		if(scripticon32 != nullptr)
			tmpicon32 = scripticon32->getManagedInstance();
		else
			tmpicon32 = nullptr;
		output.icon32 = tmpicon32;
		ScriptResourceBase* scripticon48;
		scripticon48 = ScriptResourceManager::instance().getScriptResource(value.icon48, true);
		MonoObject* tmpicon48;
		if(scripticon48 != nullptr)
			tmpicon48 = scripticon48->getManagedInstance();
		else
			tmpicon48 = nullptr;
		output.icon48 = tmpicon48;
		ScriptResourceBase* scripticon64;
		scripticon64 = ScriptResourceManager::instance().getScriptResource(value.icon64, true);
		MonoObject* tmpicon64;
		if(scripticon64 != nullptr)
			tmpicon64 = scripticon64->getManagedInstance();
		else
			tmpicon64 = nullptr;
		output.icon64 = tmpicon64;
		ScriptResourceBase* scripticon96;
		scripticon96 = ScriptResourceManager::instance().getScriptResource(value.icon96, true);
		MonoObject* tmpicon96;
		if(scripticon96 != nullptr)
			tmpicon96 = scripticon96->getManagedInstance();
		else
			tmpicon96 = nullptr;
		output.icon96 = tmpicon96;
		ScriptResourceBase* scripticon128;
		scripticon128 = ScriptResourceManager::instance().getScriptResource(value.icon128, true);
		MonoObject* tmpicon128;
		if(scripticon128 != nullptr)
			tmpicon128 = scripticon128->getManagedInstance();
		else
			tmpicon128 = nullptr;
		output.icon128 = tmpicon128;
		ScriptResourceBase* scripticon192;
		scripticon192 = ScriptResourceManager::instance().getScriptResource(value.icon192, true);
		MonoObject* tmpicon192;
		if(scripticon192 != nullptr)
			tmpicon192 = scripticon192->getManagedInstance();
		else
			tmpicon192 = nullptr;
		output.icon192 = tmpicon192;
		ScriptResourceBase* scripticon256;
		scripticon256 = ScriptResourceManager::instance().getScriptResource(value.icon256, true);
		MonoObject* tmpicon256;
		if(scripticon256 != nullptr)
			tmpicon256 = scripticon256->getManagedInstance();
		else
			tmpicon256 = nullptr;
		output.icon256 = tmpicon256;

		return output;
	}

}
