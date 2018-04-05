#include "BsScriptBlend2DInfo.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "BsScriptResourceManager.h"
#include "BsScriptAnimationClip.generated.h"

namespace bs
{
	ScriptBlend2DInfo::ScriptBlend2DInfo(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptBlend2DInfo::initRuntimeData()
	{ }

	MonoObject*ScriptBlend2DInfo::box(const __Blend2DInfoInterop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__Blend2DInfoInterop ScriptBlend2DInfo::unbox(MonoObject* value)
	{
		return *(__Blend2DInfoInterop*)MonoUtil::unbox(value);
	}

	Blend2DInfo ScriptBlend2DInfo::fromInterop(const __Blend2DInfoInterop& value)
	{
		Blend2DInfo output;
		ResourceHandle<AnimationClip> tmptopLeftClip;
		ScriptAnimationClip* scripttopLeftClip;
		scripttopLeftClip = ScriptAnimationClip::toNative(value.topLeftClip);
		if(scripttopLeftClip != nullptr)
			tmptopLeftClip = scripttopLeftClip->getHandle();
		output.topLeftClip = tmptopLeftClip;
		ResourceHandle<AnimationClip> tmptopRightClip;
		ScriptAnimationClip* scripttopRightClip;
		scripttopRightClip = ScriptAnimationClip::toNative(value.topRightClip);
		if(scripttopRightClip != nullptr)
			tmptopRightClip = scripttopRightClip->getHandle();
		output.topRightClip = tmptopRightClip;
		ResourceHandle<AnimationClip> tmpbotLeftClip;
		ScriptAnimationClip* scriptbotLeftClip;
		scriptbotLeftClip = ScriptAnimationClip::toNative(value.botLeftClip);
		if(scriptbotLeftClip != nullptr)
			tmpbotLeftClip = scriptbotLeftClip->getHandle();
		output.botLeftClip = tmpbotLeftClip;
		ResourceHandle<AnimationClip> tmpbotRightClip;
		ScriptAnimationClip* scriptbotRightClip;
		scriptbotRightClip = ScriptAnimationClip::toNative(value.botRightClip);
		if(scriptbotRightClip != nullptr)
			tmpbotRightClip = scriptbotRightClip->getHandle();
		output.botRightClip = tmpbotRightClip;

		return output;
	}

	__Blend2DInfoInterop ScriptBlend2DInfo::toInterop(const Blend2DInfo& value)
	{
		__Blend2DInfoInterop output;
		ScriptResourceBase* scripttopLeftClip;
		scripttopLeftClip = ScriptResourceManager::instance().getScriptResource(value.topLeftClip, true);
		MonoObject* tmptopLeftClip;
		if(scripttopLeftClip != nullptr)
			tmptopLeftClip = scripttopLeftClip->getManagedInstance();
		else
			tmptopLeftClip = nullptr;
		output.topLeftClip = tmptopLeftClip;
		ScriptResourceBase* scripttopRightClip;
		scripttopRightClip = ScriptResourceManager::instance().getScriptResource(value.topRightClip, true);
		MonoObject* tmptopRightClip;
		if(scripttopRightClip != nullptr)
			tmptopRightClip = scripttopRightClip->getManagedInstance();
		else
			tmptopRightClip = nullptr;
		output.topRightClip = tmptopRightClip;
		ScriptResourceBase* scriptbotLeftClip;
		scriptbotLeftClip = ScriptResourceManager::instance().getScriptResource(value.botLeftClip, true);
		MonoObject* tmpbotLeftClip;
		if(scriptbotLeftClip != nullptr)
			tmpbotLeftClip = scriptbotLeftClip->getManagedInstance();
		else
			tmpbotLeftClip = nullptr;
		output.botLeftClip = tmpbotLeftClip;
		ScriptResourceBase* scriptbotRightClip;
		scriptbotRightClip = ScriptResourceManager::instance().getScriptResource(value.botRightClip, true);
		MonoObject* tmpbotRightClip;
		if(scriptbotRightClip != nullptr)
			tmpbotRightClip = scriptbotRightClip->getManagedInstance();
		else
			tmpbotRightClip = nullptr;
		output.botRightClip = tmpbotRightClip;

		return output;
	}

}
