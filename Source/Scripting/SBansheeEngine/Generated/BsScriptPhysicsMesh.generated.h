#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "Wrappers/BsScriptResource.h"
#include "../../../bsf/Source/Foundation/bsfCore/Utility/BsCommonTypes.h"

namespace bs
{
	class PhysicsMesh;
	class PhysicsMeshEx;

	class BS_SCR_BE_EXPORT ScriptPhysicsMesh : public TScriptResource<ScriptPhysicsMesh, PhysicsMesh>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "PhysicsMesh")

		ScriptPhysicsMesh(MonoObject* managedInstance, const ResourceHandle<PhysicsMesh>& value);

		static MonoObject* createInstance();

	private:
		static PhysicsMeshType Internal_getType(ScriptPhysicsMesh* thisPtr);
		static void Internal_create(MonoObject* managedInstance, MonoObject* meshData, PhysicsMeshType type);
		static MonoObject* Internal_getMeshData(ScriptPhysicsMesh* thisPtr);
	};
}
