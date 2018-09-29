#pragma once

#include "BsScriptEditorPrerequisites.h"
#include "BsScriptObject.h"
#include "../../../EditorCore/GUI/BsGUIGraphTicks.h"

namespace bs
{
	class GUIGraphTicks;

	class BS_SCR_BED_EXPORT ScriptGUIGraphTicks : public ScriptObject<ScriptGUIGraphTicks>
	{
	public:
		SCRIPT_OBJ(EDITOR_ASSEMBLY, "BansheeEditor", "GUIGraphTicks")

		ScriptGUIGraphTicks(MonoObject* managedInstance, const SPtr<GUIGraphTicks>& value);

		SPtr<GUIGraphTicks> getInternal() const { return mInternal; }
		static MonoObject* create(const SPtr<GUIGraphTicks>& value);

	private:
		SPtr<GUIGraphTicks> mInternal;

		static void Internal_GUIGraphTicks(MonoObject* managedInstance, GUITickStepType stepType);
		static uint32_t Internal_getNumLevels(ScriptGUIGraphTicks* thisPtr);
		static void Internal_setRange(ScriptGUIGraphTicks* thisPtr, float valueRangeStart, float valueRangeEnd, uint32_t pixelRange);
		static void Internal_setTickSpacing(ScriptGUIGraphTicks* thisPtr, int32_t minPx, int32_t maxPx);
		static float Internal_getLevelStrength(ScriptGUIGraphTicks* thisPtr, uint32_t level);
		static MonoArray* Internal_getTicks(ScriptGUIGraphTicks* thisPtr, uint32_t level);
	};
}
