#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfCore/RenderAPI/BsSubMesh.h"

namespace bs
{
	class BS_SCR_BE_EXPORT ScriptSubMesh : public ScriptObject<ScriptSubMesh>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "SubMesh")

		static MonoObject* box(const SubMesh& value);
		static SubMesh unbox(MonoObject* value);

	private:
		ScriptSubMesh(MonoObject* managedInstance);

	};
}
