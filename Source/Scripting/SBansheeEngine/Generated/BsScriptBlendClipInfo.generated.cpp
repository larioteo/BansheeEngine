#include "BsScriptBlendClipInfo.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "BsScriptResourceManager.h"
#include "BsScriptAnimationClip.generated.h"

namespace bs
{
	ScriptBlendClipInfo::ScriptBlendClipInfo(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptBlendClipInfo::initRuntimeData()
	{ }

	MonoObject*ScriptBlendClipInfo::box(const __BlendClipInfoInterop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__BlendClipInfoInterop ScriptBlendClipInfo::unbox(MonoObject* value)
	{
		return *(__BlendClipInfoInterop*)MonoUtil::unbox(value);
	}

	BlendClipInfo ScriptBlendClipInfo::fromInterop(const __BlendClipInfoInterop& value)
	{
		BlendClipInfo output;
		ResourceHandle<AnimationClip> tmpclip;
		ScriptAnimationClip* scriptclip;
		scriptclip = ScriptAnimationClip::toNative(value.clip);
		if(scriptclip != nullptr)
			tmpclip = scriptclip->getHandle();
		output.clip = tmpclip;
		output.position = value.position;

		return output;
	}

	__BlendClipInfoInterop ScriptBlendClipInfo::toInterop(const BlendClipInfo& value)
	{
		__BlendClipInfoInterop output;
		ScriptResourceBase* scriptclip;
		scriptclip = ScriptResourceManager::instance().getScriptResource(value.clip, true);
		MonoObject* tmpclip;
		if(scriptclip != nullptr)
			tmpclip = scriptclip->getManagedInstance();
		else
			tmpclip = nullptr;
		output.clip = tmpclip;
		output.position = value.position;

		return output;
	}

}
