#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfCore/Utility/BsCommonTypes.h"

namespace bs
{
	class BS_SCR_BE_EXPORT ScriptTextureSurface : public ScriptObject<ScriptTextureSurface>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "TextureSurface")

		static MonoObject* box(const TextureSurface& value);
		static TextureSurface unbox(MonoObject* value);

	private:
		ScriptTextureSurface(MonoObject* managedInstance);

	};
}
