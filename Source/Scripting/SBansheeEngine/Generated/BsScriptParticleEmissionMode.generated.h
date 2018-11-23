#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfCore/Particles/BsParticleEmitter.h"

namespace bs
{
	class BS_SCR_BE_EXPORT ScriptParticleEmissionMode : public ScriptObject<ScriptParticleEmissionMode>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "ParticleEmissionMode")

		static MonoObject* box(const ParticleEmissionMode& value);
		static ParticleEmissionMode unbox(MonoObject* value);

	private:
		ScriptParticleEmissionMode(MonoObject* managedInstance);

	};
}
