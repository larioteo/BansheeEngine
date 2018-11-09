#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "Wrappers/BsScriptComponent.h"

namespace bs
{
	class CDecal;
	class Material;

	class BS_SCR_BE_EXPORT ScriptCDecal : public TScriptComponent<ScriptCDecal, CDecal>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "Decal")

		ScriptCDecal(MonoObject* managedInstance, const GameObjectHandle<CDecal>& value);

	private:
		static void Internal_setMaterial(ScriptCDecal* thisPtr, MonoObject* material);
		static MonoObject* Internal_getMaterial(ScriptCDecal* thisPtr);
		static void Internal_setSize(ScriptCDecal* thisPtr, Vector2* size);
		static void Internal_getSize(ScriptCDecal* thisPtr, Vector2* __output);
		static void Internal_setMaxDistance(ScriptCDecal* thisPtr, float distance);
		static float Internal_getMaxDistance(ScriptCDecal* thisPtr);
		static void Internal_setLayer(ScriptCDecal* thisPtr, uint64_t layer);
		static uint64_t Internal_getLayer(ScriptCDecal* thisPtr);
	};
}
