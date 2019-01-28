//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//************** Copyright (c) 2016-2019 Marko Pintera (marko.pintera@gmail.com). All rights reserved. *******************//
#pragma once

#include "BsScriptEditorPrerequisites.h"
#include "Wrappers/GUI/BsScriptGUIElement.h"
#include "../../bsf/Source/Foundation/bsfCore/Particles/BsParticleDistribution.h"
#include "../../bsf/Source/Foundation/bsfCore/Localization/BsHString.h"
#include "../../bsf/Source/Foundation/bsfCore/Particles/BsParticleDistribution.h"

namespace bs
{
	class GUIVector2DistributionField;
	struct __GUIContentInterop;

	class BS_SCR_BED_EXPORT ScriptGUIVector2DistributionField : public TScriptGUIElement<ScriptGUIVector2DistributionField>
	{
	public:
		SCRIPT_OBJ(EDITOR_ASSEMBLY, EDITOR_NS, "GUIVector2DistributionField")

		ScriptGUIVector2DistributionField(MonoObject* managedInstance, GUIVector2DistributionField* value);

	private:
		void onClicked(int32_t p0);
		void onConstantModified();
		void onConstantConfirmed();

		typedef void(BS_THUNKCALL *onClickedThunkDef) (MonoObject*, int32_t p0, MonoException**);
		static onClickedThunkDef onClickedThunk;
		typedef void(BS_THUNKCALL *onConstantModifiedThunkDef) (MonoObject*, MonoException**);
		static onConstantModifiedThunkDef onConstantModifiedThunk;
		typedef void(BS_THUNKCALL *onConstantConfirmedThunkDef) (MonoObject*, MonoException**);
		static onConstantConfirmedThunkDef onConstantConfirmedThunk;

		static MonoObject* Internal_getValue(ScriptGUIVector2DistributionField* thisPtr);
		static void Internal_setValue(ScriptGUIVector2DistributionField* thisPtr, MonoObject* value);
		static PropertyDistributionType Internal_getType(ScriptGUIVector2DistributionField* thisPtr);
		static bool Internal_hasInputFocus(ScriptGUIVector2DistributionField* thisPtr);
		static void Internal_create(MonoObject* managedInstance, __GUIContentInterop* labelContent, uint32_t labelWidth, MonoString* style);
		static void Internal_create0(MonoObject* managedInstance, __GUIContentInterop* labelContent, MonoString* style);
		static void Internal_create1(MonoObject* managedInstance, MonoObject* labelText, uint32_t labelWidth, MonoString* style);
		static void Internal_create2(MonoObject* managedInstance, MonoObject* labelText, MonoString* style);
		static void Internal_create3(MonoObject* managedInstance, MonoString* style);
	};
}
