#include "BsScriptGUIFloatDistributionField.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../EditorCore/GUI/BsGUIFloatDistributionField.h"
#include "BsScriptTDistribution.generated.h"
#include "BsScriptHString.generated.h"
#include "BsScriptGUIContent.generated.h"
#include "../../../EditorCore/GUI/BsGUIFloatDistributionField.h"

namespace bs
{
	ScriptGUIFloatDistributionField::onClickedThunkDef ScriptGUIFloatDistributionField::onClickedThunk; 
	ScriptGUIFloatDistributionField::onConstantModifiedThunkDef ScriptGUIFloatDistributionField::onConstantModifiedThunk; 
	ScriptGUIFloatDistributionField::onConstantConfirmedThunkDef ScriptGUIFloatDistributionField::onConstantConfirmedThunk; 

	ScriptGUIFloatDistributionField::ScriptGUIFloatDistributionField(MonoObject* managedInstance, GUIFloatDistributionField* value)
		:TScriptGUIElement(managedInstance, value)
	{
		value->onClicked.connect(std::bind(&ScriptGUIFloatDistributionField::onClicked, this, std::placeholders::_1));
		value->onConstantModified.connect(std::bind(&ScriptGUIFloatDistributionField::onConstantModified, this));
		value->onConstantConfirmed.connect(std::bind(&ScriptGUIFloatDistributionField::onConstantConfirmed, this));
	}

	void ScriptGUIFloatDistributionField::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_getValue", (void*)&ScriptGUIFloatDistributionField::Internal_getValue);
		metaData.scriptClass->addInternalCall("Internal_setValue", (void*)&ScriptGUIFloatDistributionField::Internal_setValue);
		metaData.scriptClass->addInternalCall("Internal_getType", (void*)&ScriptGUIFloatDistributionField::Internal_getType);
		metaData.scriptClass->addInternalCall("Internal_hasInputFocus", (void*)&ScriptGUIFloatDistributionField::Internal_hasInputFocus);
		metaData.scriptClass->addInternalCall("Internal_create", (void*)&ScriptGUIFloatDistributionField::Internal_create);
		metaData.scriptClass->addInternalCall("Internal_create0", (void*)&ScriptGUIFloatDistributionField::Internal_create0);
		metaData.scriptClass->addInternalCall("Internal_create1", (void*)&ScriptGUIFloatDistributionField::Internal_create1);
		metaData.scriptClass->addInternalCall("Internal_create2", (void*)&ScriptGUIFloatDistributionField::Internal_create2);
		metaData.scriptClass->addInternalCall("Internal_create3", (void*)&ScriptGUIFloatDistributionField::Internal_create3);

		onClickedThunk = (onClickedThunkDef)metaData.scriptClass->getMethodExact("Internal_onClicked", "int")->getThunk();
		onConstantModifiedThunk = (onConstantModifiedThunkDef)metaData.scriptClass->getMethodExact("Internal_onConstantModified", "")->getThunk();
		onConstantConfirmedThunk = (onConstantConfirmedThunkDef)metaData.scriptClass->getMethodExact("Internal_onConstantConfirmed", "")->getThunk();
	}

	void ScriptGUIFloatDistributionField::onClicked(int32_t p0)
	{
		MonoUtil::invokeThunk(onClickedThunk, getManagedInstance(), p0);
	}

	void ScriptGUIFloatDistributionField::onConstantModified()
	{
		MonoUtil::invokeThunk(onConstantModifiedThunk, getManagedInstance());
	}

	void ScriptGUIFloatDistributionField::onConstantConfirmed()
	{
		MonoUtil::invokeThunk(onConstantConfirmedThunk, getManagedInstance());
	}
	MonoObject* ScriptGUIFloatDistributionField::Internal_getValue(ScriptGUIFloatDistributionField* thisPtr)
	{
		SPtr<TDistribution<float>> tmp__output = bs_shared_ptr_new<TDistribution<float>>();
		*tmp__output = static_cast<GUIFloatDistributionField*>(thisPtr->getGUIElement())->getValue();

		MonoObject* __output;
		__output = ScriptTDistributionfloat::create(tmp__output);

		return __output;
	}

	void ScriptGUIFloatDistributionField::Internal_setValue(ScriptGUIFloatDistributionField* thisPtr, MonoObject* value)
	{
		SPtr<TDistribution<float>> tmpvalue;
		ScriptTDistributionfloat* scriptvalue;
		scriptvalue = ScriptTDistributionfloat::toNative(value);
		tmpvalue = scriptvalue->getInternal();
		static_cast<GUIFloatDistributionField*>(thisPtr->getGUIElement())->setValue(*tmpvalue);
	}

	PropertyDistributionType ScriptGUIFloatDistributionField::Internal_getType(ScriptGUIFloatDistributionField* thisPtr)
	{
		PropertyDistributionType tmp__output;
		tmp__output = static_cast<GUIFloatDistributionField*>(thisPtr->getGUIElement())->getType();

		PropertyDistributionType __output;
		__output = tmp__output;

		return __output;
	}

	bool ScriptGUIFloatDistributionField::Internal_hasInputFocus(ScriptGUIFloatDistributionField* thisPtr)
	{
		bool tmp__output;
		tmp__output = static_cast<GUIFloatDistributionField*>(thisPtr->getGUIElement())->hasInputFocus();

		bool __output;
		__output = tmp__output;

		return __output;
	}

	void ScriptGUIFloatDistributionField::Internal_create(MonoObject* managedInstance, __GUIContentInterop* labelContent, uint32_t labelWidth, MonoString* style)
	{
		GUIContent tmplabelContent;
		tmplabelContent = ScriptGUIContent::fromInterop(*labelContent);
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIFloatDistributionField* instance = GUIFloatDistributionField::create(tmplabelContent, labelWidth, tmpstyle);
		new (bs_alloc<ScriptGUIFloatDistributionField>())ScriptGUIFloatDistributionField(managedInstance, instance);
	}

	void ScriptGUIFloatDistributionField::Internal_create0(MonoObject* managedInstance, __GUIContentInterop* labelContent, MonoString* style)
	{
		GUIContent tmplabelContent;
		tmplabelContent = ScriptGUIContent::fromInterop(*labelContent);
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIFloatDistributionField* instance = GUIFloatDistributionField::create(tmplabelContent, tmpstyle);
		new (bs_alloc<ScriptGUIFloatDistributionField>())ScriptGUIFloatDistributionField(managedInstance, instance);
	}

	void ScriptGUIFloatDistributionField::Internal_create1(MonoObject* managedInstance, MonoObject* labelText, uint32_t labelWidth, MonoString* style)
	{
		SPtr<HString> tmplabelText;
		ScriptHString* scriptlabelText;
		scriptlabelText = ScriptHString::toNative(labelText);
		tmplabelText = scriptlabelText->getInternal();
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIFloatDistributionField* instance = GUIFloatDistributionField::create(*tmplabelText, labelWidth, tmpstyle);
		new (bs_alloc<ScriptGUIFloatDistributionField>())ScriptGUIFloatDistributionField(managedInstance, instance);
	}

	void ScriptGUIFloatDistributionField::Internal_create2(MonoObject* managedInstance, MonoObject* labelText, MonoString* style)
	{
		SPtr<HString> tmplabelText;
		ScriptHString* scriptlabelText;
		scriptlabelText = ScriptHString::toNative(labelText);
		tmplabelText = scriptlabelText->getInternal();
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIFloatDistributionField* instance = GUIFloatDistributionField::create(*tmplabelText, tmpstyle);
		new (bs_alloc<ScriptGUIFloatDistributionField>())ScriptGUIFloatDistributionField(managedInstance, instance);
	}

	void ScriptGUIFloatDistributionField::Internal_create3(MonoObject* managedInstance, MonoString* style)
	{
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIFloatDistributionField* instance = GUIFloatDistributionField::create(tmpstyle);
		new (bs_alloc<ScriptGUIFloatDistributionField>())ScriptGUIFloatDistributionField(managedInstance, instance);
	}
}
