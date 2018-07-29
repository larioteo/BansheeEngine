#pragma once

#include "BsScriptEditorPrerequisites.h"
#include "Wrappers/GUI/BsScriptGUIElement.h"
#include "../../../bsf/Source/Foundation/bsfUtility/Image/BsColorGradient.h"

namespace bs
{
	class GUIColorGradient;

	class BS_SCR_BED_EXPORT ScriptGUIColorGradient : public TScriptGUIElement<ScriptGUIColorGradient>
	{
	public:
		SCRIPT_OBJ(EDITOR_ASSEMBLY, "BansheeEditor", "GUIColorGradient")

		ScriptGUIColorGradient(MonoObject* managedInstance, GUIColorGradient* value);

	private:
		void onClicked();

		typedef void(BS_THUNKCALL *onClickedThunkDef) (MonoObject*, MonoException**);
		static onClickedThunkDef onClickedThunk;

		static void Internal_setGradient(ScriptGUIColorGradient* thisPtr, MonoObject* colorGradient);
		static MonoObject* Internal_getGradient(ScriptGUIColorGradient* thisPtr);
		static void Internal_create(MonoObject* managedInstance, MonoString* styleName);
	};
}
