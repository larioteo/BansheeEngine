#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfCore/Physics/BsJoint.h"

namespace bs
{
	class BS_SCR_BE_EXPORT ScriptSpring : public ScriptObject<ScriptSpring>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "Spring")

		static MonoObject* box(const Spring& value);
		static Spring unbox(MonoObject* value);

	private:
		ScriptSpring(MonoObject* managedInstance);

	};
}
