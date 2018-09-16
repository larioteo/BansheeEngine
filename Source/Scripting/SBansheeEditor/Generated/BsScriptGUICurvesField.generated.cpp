#include "BsScriptGUICurvesField.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../EditorCore/GUI/BsGUICurvesField.h"
#include "BsScriptHString.generated.h"
#include "BsScriptTAnimationCurve.generated.h"
#include "BsScriptGUIContent.generated.h"
#include "../../../EditorCore/GUI/BsGUICurvesField.h"

namespace bs
{
	ScriptGUICurvesField::onClickedThunkDef ScriptGUICurvesField::onClickedThunk; 

	ScriptGUICurvesField::ScriptGUICurvesField(MonoObject* managedInstance, GUICurvesField* value)
		:TScriptGUIElement(managedInstance, value)
	{
		value->onClicked.connect(std::bind(&ScriptGUICurvesField::onClicked, this));
	}

	void ScriptGUICurvesField::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_setCurve", (void*)&ScriptGUICurvesField::Internal_setCurve);
		metaData.scriptClass->addInternalCall("Internal_setCurveRange", (void*)&ScriptGUICurvesField::Internal_setCurveRange);
		metaData.scriptClass->addInternalCall("Internal_create", (void*)&ScriptGUICurvesField::Internal_create);
		metaData.scriptClass->addInternalCall("Internal_create0", (void*)&ScriptGUICurvesField::Internal_create0);
		metaData.scriptClass->addInternalCall("Internal_create1", (void*)&ScriptGUICurvesField::Internal_create1);
		metaData.scriptClass->addInternalCall("Internal_create2", (void*)&ScriptGUICurvesField::Internal_create2);
		metaData.scriptClass->addInternalCall("Internal_create3", (void*)&ScriptGUICurvesField::Internal_create3);

		onClickedThunk = (onClickedThunkDef)metaData.scriptClass->getMethodExact("Internal_onClicked", "")->getThunk();
	}

	void ScriptGUICurvesField::onClicked()
	{
		MonoUtil::invokeThunk(onClickedThunk, getManagedInstance());
	}
	void ScriptGUICurvesField::Internal_setCurve(ScriptGUICurvesField* thisPtr, MonoObject* curve)
	{
		SPtr<TAnimationCurve<float>> tmpcurve;
		ScriptTAnimationCurvefloat* scriptcurve;
		scriptcurve = ScriptTAnimationCurvefloat::toNative(curve);
		tmpcurve = scriptcurve->getInternal();
		static_cast<GUICurvesField*>(thisPtr->getGUIElement())->setCurve(*tmpcurve);
	}

	void ScriptGUICurvesField::Internal_setCurveRange(ScriptGUICurvesField* thisPtr, MonoObject* curveA, MonoObject* curveB)
	{
		SPtr<TAnimationCurve<float>> tmpcurveA;
		ScriptTAnimationCurvefloat* scriptcurveA;
		scriptcurveA = ScriptTAnimationCurvefloat::toNative(curveA);
		tmpcurveA = scriptcurveA->getInternal();
		SPtr<TAnimationCurve<float>> tmpcurveB;
		ScriptTAnimationCurvefloat* scriptcurveB;
		scriptcurveB = ScriptTAnimationCurvefloat::toNative(curveB);
		tmpcurveB = scriptcurveB->getInternal();
		static_cast<GUICurvesField*>(thisPtr->getGUIElement())->setCurveRange(*tmpcurveA, *tmpcurveB);
	}

	void ScriptGUICurvesField::Internal_create(MonoObject* managedInstance, __GUIContentInterop* labelContent, uint32_t labelWidth, MonoString* style)
	{
		GUIContent tmplabelContent;
		tmplabelContent = ScriptGUIContent::fromInterop(*labelContent);
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUICurvesField* instance = GUICurvesField::create(tmplabelContent, labelWidth, tmpstyle);
		new (bs_alloc<ScriptGUICurvesField>())ScriptGUICurvesField(managedInstance, instance);
	}

	void ScriptGUICurvesField::Internal_create0(MonoObject* managedInstance, __GUIContentInterop* labelContent, MonoString* style)
	{
		GUIContent tmplabelContent;
		tmplabelContent = ScriptGUIContent::fromInterop(*labelContent);
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUICurvesField* instance = GUICurvesField::create(tmplabelContent, tmpstyle);
		new (bs_alloc<ScriptGUICurvesField>())ScriptGUICurvesField(managedInstance, instance);
	}

	void ScriptGUICurvesField::Internal_create1(MonoObject* managedInstance, MonoObject* labelText, uint32_t labelWidth, MonoString* style)
	{
		SPtr<HString> tmplabelText;
		ScriptHString* scriptlabelText;
		scriptlabelText = ScriptHString::toNative(labelText);
		tmplabelText = scriptlabelText->getInternal();
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUICurvesField* instance = GUICurvesField::create(*tmplabelText, labelWidth, tmpstyle);
		new (bs_alloc<ScriptGUICurvesField>())ScriptGUICurvesField(managedInstance, instance);
	}

	void ScriptGUICurvesField::Internal_create2(MonoObject* managedInstance, MonoObject* labelText, MonoString* style)
	{
		SPtr<HString> tmplabelText;
		ScriptHString* scriptlabelText;
		scriptlabelText = ScriptHString::toNative(labelText);
		tmplabelText = scriptlabelText->getInternal();
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUICurvesField* instance = GUICurvesField::create(*tmplabelText, tmpstyle);
		new (bs_alloc<ScriptGUICurvesField>())ScriptGUICurvesField(managedInstance, instance);
	}

	void ScriptGUICurvesField::Internal_create3(MonoObject* managedInstance, MonoString* style)
	{
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUICurvesField* instance = GUICurvesField::create(tmpstyle);
		new (bs_alloc<ScriptGUICurvesField>())ScriptGUICurvesField(managedInstance, instance);
	}
}
