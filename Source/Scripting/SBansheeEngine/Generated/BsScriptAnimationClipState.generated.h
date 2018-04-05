#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfCore/Animation/BsAnimation.h"

namespace bs
{
	class BS_SCR_BE_EXPORT ScriptAnimationClipState : public ScriptObject<ScriptAnimationClipState>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "AnimationClipState")

		static MonoObject* box(const AnimationClipState& value);
		static AnimationClipState unbox(MonoObject* value);

	private:
		ScriptAnimationClipState(MonoObject* managedInstance);

	};
}
