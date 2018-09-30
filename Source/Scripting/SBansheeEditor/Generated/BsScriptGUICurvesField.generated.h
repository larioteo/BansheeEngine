#pragma once

#include "BsScriptEditorPrerequisites.h"
#include "Wrappers/GUI/BsScriptGUIElement.h"
#include "../../../bsf/Source/Foundation/bsfCore/Localization/BsHString.h"
#include "../../../bsf/Source/Foundation/bsfCore/Animation/BsAnimationCurve.h"

namespace bs
{
	class GUICurvesField;
	struct __GUIContentInterop;

	class BS_SCR_BED_EXPORT ScriptGUICurvesField : public TScriptGUIElement<ScriptGUICurvesField>
	{
	public:
		SCRIPT_OBJ(EDITOR_ASSEMBLY, "BansheeEditor", "GUICurvesField")

		ScriptGUICurvesField(MonoObject* managedInstance, GUICurvesField* value);

	private:
		void onClicked();

		typedef void(BS_THUNKCALL *onClickedThunkDef) (MonoObject*, MonoException**);
		static onClickedThunkDef onClickedThunk;

		static void Internal_setCurve(ScriptGUICurvesField* thisPtr, MonoObject* curve);
		static void Internal_setCurveRange(ScriptGUICurvesField* thisPtr, MonoObject* curveA, MonoObject* curveB);
		static MonoObject* Internal_getCurve(ScriptGUICurvesField* thisPtr);
		static MonoObject* Internal_getMinCurve(ScriptGUICurvesField* thisPtr);
		static MonoObject* Internal_getMaxCurve(ScriptGUICurvesField* thisPtr);
		static void Internal_create(MonoObject* managedInstance, __GUIContentInterop* labelContent, uint32_t labelWidth, MonoString* style);
		static void Internal_create0(MonoObject* managedInstance, __GUIContentInterop* labelContent, MonoString* style);
		static void Internal_create1(MonoObject* managedInstance, MonoObject* labelText, uint32_t labelWidth, MonoString* style);
		static void Internal_create2(MonoObject* managedInstance, MonoObject* labelText, MonoString* style);
		static void Internal_create3(MonoObject* managedInstance, MonoString* style);
	};
}
