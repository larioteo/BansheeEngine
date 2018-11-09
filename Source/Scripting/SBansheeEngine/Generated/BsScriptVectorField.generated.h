#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "Wrappers/BsScriptResource.h"

namespace bs
{
	class VectorField;

	class BS_SCR_BE_EXPORT ScriptVectorField : public TScriptResource<ScriptVectorField, VectorField>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "VectorField")

		ScriptVectorField(MonoObject* managedInstance, const ResourceHandle<VectorField>& value);

		static MonoObject* createInstance();

	private:
		static MonoObject* Internal_getRef(ScriptVectorField* thisPtr);

	};
}
