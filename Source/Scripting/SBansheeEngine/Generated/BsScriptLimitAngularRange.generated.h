#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfCore/Physics/BsJoint.h"
#include "Math/BsRadian.h"
#include "../../../bsf/Source/Foundation/bsfCore/Physics/BsJoint.h"

namespace bs
{
	struct __LimitAngularRangeInterop
	{
		Radian lower;
		Radian upper;
		float contactDist;
		float restitution;
		Spring spring;
	};

	class BS_SCR_BE_EXPORT ScriptLimitAngularRange : public ScriptObject<ScriptLimitAngularRange>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "LimitAngularRange")

		static MonoObject* box(const __LimitAngularRangeInterop& value);
		static __LimitAngularRangeInterop unbox(MonoObject* value);
		static LimitAngularRange fromInterop(const __LimitAngularRangeInterop& value);
		static __LimitAngularRangeInterop toInterop(const LimitAngularRange& value);

	private:
		ScriptLimitAngularRange(MonoObject* managedInstance);

	};
}
