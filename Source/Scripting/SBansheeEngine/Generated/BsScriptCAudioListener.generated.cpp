#include "BsScriptCAudioListener.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Components/BsCAudioListener.h"

namespace bs
{
	ScriptCAudioListener::ScriptCAudioListener(MonoObject* managedInstance, const GameObjectHandle<CAudioListener>& value)
		:TScriptComponent(managedInstance, value)
	{
	}

	void ScriptCAudioListener::initRuntimeData()
	{

	}

}
