#include "BsScriptGUIVector3DistributionField.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../EditorCore/GUI/BsGUIFloatDistributionField.h"
#include "BsScriptGUIContent.generated.h"
#include "BsScriptTDistribution.generated.h"
#include "BsScriptHString.generated.h"
#include "../../../EditorCore/GUI/BsGUIFloatDistributionField.h"

namespace bs
{
	ScriptGUIVector3DistributionField::onClickedThunkDef ScriptGUIVector3DistributionField::onClickedThunk; 
	ScriptGUIVector3DistributionField::onConstantModifiedThunkDef ScriptGUIVector3DistributionField::onConstantModifiedThunk; 
	ScriptGUIVector3DistributionField::onConstantConfirmedThunkDef ScriptGUIVector3DistributionField::onConstantConfirmedThunk; 

	ScriptGUIVector3DistributionField::ScriptGUIVector3DistributionField(MonoObject* managedInstance, GUIVector3DistributionField* value)
		:TScriptGUIElement(managedInstance, value)
	{
		value->onClicked.connect(std::bind(&ScriptGUIVector3DistributionField::onClicked, this, std::placeholders::_1));
		value->onConstantModified.connect(std::bind(&ScriptGUIVector3DistributionField::onConstantModified, this));
		value->onConstantConfirmed.connect(std::bind(&ScriptGUIVector3DistributionField::onConstantConfirmed, this));
	}

	void ScriptGUIVector3DistributionField::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_getValue", (void*)&ScriptGUIVector3DistributionField::Internal_getValue);
		metaData.scriptClass->addInternalCall("Internal_setValue", (void*)&ScriptGUIVector3DistributionField::Internal_setValue);
		metaData.scriptClass->addInternalCall("Internal_getType", (void*)&ScriptGUIVector3DistributionField::Internal_getType);
		metaData.scriptClass->addInternalCall("Internal_hasInputFocus", (void*)&ScriptGUIVector3DistributionField::Internal_hasInputFocus);
		metaData.scriptClass->addInternalCall("Internal_create", (void*)&ScriptGUIVector3DistributionField::Internal_create);
		metaData.scriptClass->addInternalCall("Internal_create0", (void*)&ScriptGUIVector3DistributionField::Internal_create0);
		metaData.scriptClass->addInternalCall("Internal_create1", (void*)&ScriptGUIVector3DistributionField::Internal_create1);
		metaData.scriptClass->addInternalCall("Internal_create2", (void*)&ScriptGUIVector3DistributionField::Internal_create2);
		metaData.scriptClass->addInternalCall("Internal_create3", (void*)&ScriptGUIVector3DistributionField::Internal_create3);

		onClickedThunk = (onClickedThunkDef)metaData.scriptClass->getMethodExact("Internal_onClicked", "int")->getThunk();
		onConstantModifiedThunk = (onConstantModifiedThunkDef)metaData.scriptClass->getMethodExact("Internal_onConstantModified", "")->getThunk();
		onConstantConfirmedThunk = (onConstantConfirmedThunkDef)metaData.scriptClass->getMethodExact("Internal_onConstantConfirmed", "")->getThunk();
	}

	void ScriptGUIVector3DistributionField::onClicked(int32_t p0)
	{
		MonoUtil::invokeThunk(onClickedThunk, getManagedInstance(), p0);
	}

	void ScriptGUIVector3DistributionField::onConstantModified()
	{
		MonoUtil::invokeThunk(onConstantModifiedThunk, getManagedInstance());
	}

	void ScriptGUIVector3DistributionField::onConstantConfirmed()
	{
		MonoUtil::invokeThunk(onConstantConfirmedThunk, getManagedInstance());
	}
	MonoObject* ScriptGUIVector3DistributionField::Internal_getValue(ScriptGUIVector3DistributionField* thisPtr)
	{
		SPtr<TDistribution<Vector3>> tmp__output = bs_shared_ptr_new<TDistribution<Vector3>>();
		*tmp__output = static_cast<GUIVector3DistributionField*>(thisPtr->getGUIElement())->getValue();

		MonoObject* __output;
		__output = ScriptTDistributionVector3::create(tmp__output);

		return __output;
	}

	void ScriptGUIVector3DistributionField::Internal_setValue(ScriptGUIVector3DistributionField* thisPtr, MonoObject* value)
	{
		SPtr<TDistribution<Vector3>> tmpvalue;
		ScriptTDistributionVector3* scriptvalue;
		scriptvalue = ScriptTDistributionVector3::toNative(value);
		tmpvalue = scriptvalue->getInternal();
		static_cast<GUIVector3DistributionField*>(thisPtr->getGUIElement())->setValue(*tmpvalue);
	}

	PropertyDistributionType ScriptGUIVector3DistributionField::Internal_getType(ScriptGUIVector3DistributionField* thisPtr)
	{
		PropertyDistributionType tmp__output;
		tmp__output = static_cast<GUIVector3DistributionField*>(thisPtr->getGUIElement())->getType();

		PropertyDistributionType __output;
		__output = tmp__output;

		return __output;
	}

	bool ScriptGUIVector3DistributionField::Internal_hasInputFocus(ScriptGUIVector3DistributionField* thisPtr)
	{
		bool tmp__output;
		tmp__output = static_cast<GUIVector3DistributionField*>(thisPtr->getGUIElement())->hasInputFocus();

		bool __output;
		__output = tmp__output;

		return __output;
	}

	void ScriptGUIVector3DistributionField::Internal_create(MonoObject* managedInstance, __GUIContentInterop* labelContent, uint32_t labelWidth, MonoString* style)
	{
		GUIContent tmplabelContent;
		tmplabelContent = ScriptGUIContent::fromInterop(*labelContent);
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector3DistributionField* instance = GUIVector3DistributionField::create(tmplabelContent, labelWidth, tmpstyle);
		new (bs_alloc<ScriptGUIVector3DistributionField>())ScriptGUIVector3DistributionField(managedInstance, instance);
	}

	void ScriptGUIVector3DistributionField::Internal_create0(MonoObject* managedInstance, __GUIContentInterop* labelContent, MonoString* style)
	{
		GUIContent tmplabelContent;
		tmplabelContent = ScriptGUIContent::fromInterop(*labelContent);
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector3DistributionField* instance = GUIVector3DistributionField::create(tmplabelContent, tmpstyle);
		new (bs_alloc<ScriptGUIVector3DistributionField>())ScriptGUIVector3DistributionField(managedInstance, instance);
	}

	void ScriptGUIVector3DistributionField::Internal_create1(MonoObject* managedInstance, MonoObject* labelText, uint32_t labelWidth, MonoString* style)
	{
		SPtr<HString> tmplabelText;
		ScriptHString* scriptlabelText;
		scriptlabelText = ScriptHString::toNative(labelText);
		tmplabelText = scriptlabelText->getInternal();
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector3DistributionField* instance = GUIVector3DistributionField::create(*tmplabelText, labelWidth, tmpstyle);
		new (bs_alloc<ScriptGUIVector3DistributionField>())ScriptGUIVector3DistributionField(managedInstance, instance);
	}

	void ScriptGUIVector3DistributionField::Internal_create2(MonoObject* managedInstance, MonoObject* labelText, MonoString* style)
	{
		SPtr<HString> tmplabelText;
		ScriptHString* scriptlabelText;
		scriptlabelText = ScriptHString::toNative(labelText);
		tmplabelText = scriptlabelText->getInternal();
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector3DistributionField* instance = GUIVector3DistributionField::create(*tmplabelText, tmpstyle);
		new (bs_alloc<ScriptGUIVector3DistributionField>())ScriptGUIVector3DistributionField(managedInstance, instance);
	}

	void ScriptGUIVector3DistributionField::Internal_create3(MonoObject* managedInstance, MonoString* style)
	{
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector3DistributionField* instance = GUIVector3DistributionField::create(tmpstyle);
		new (bs_alloc<ScriptGUIVector3DistributionField>())ScriptGUIVector3DistributionField(managedInstance, instance);
	}
}
