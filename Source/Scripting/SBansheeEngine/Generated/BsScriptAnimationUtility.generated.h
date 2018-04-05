#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"

namespace bs
{
	class AnimationUtility;

	class BS_SCR_BE_EXPORT ScriptAnimationUtility : public ScriptObject<ScriptAnimationUtility>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "AnimationUtility")

		ScriptAnimationUtility(MonoObject* managedInstance, const SPtr<AnimationUtility>& value);

		SPtr<AnimationUtility> getInternal() const { return mInternal; }
		static MonoObject* create(const SPtr<AnimationUtility>& value);

	private:
		SPtr<AnimationUtility> mInternal;

		static MonoObject* Internal_eulerToQuaternionCurve(MonoObject* eulerCurve);
		static MonoObject* Internal_quaternionToEulerCurve(MonoObject* quatCurve);
		static MonoArray* Internal_splitCurve(MonoObject* compoundCurve);
		static MonoObject* Internal_combineCurve(MonoArray* curveComponents);
	};
}
