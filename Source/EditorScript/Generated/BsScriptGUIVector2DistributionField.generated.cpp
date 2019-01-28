//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//************** Copyright (c) 2016-2019 Marko Pintera (marko.pintera@gmail.com). All rights reserved. *******************//
#include "BsScriptGUIVector2DistributionField.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../EditorCore/GUI/BsGUIFloatDistributionField.h"
#include "BsScriptTDistribution.generated.h"
#include "BsScriptHString.generated.h"
#include "BsScriptGUIContent.generated.h"
#include "../../EditorCore/GUI/BsGUIFloatDistributionField.h"

namespace bs
{
	ScriptGUIVector2DistributionField::onClickedThunkDef ScriptGUIVector2DistributionField::onClickedThunk; 
	ScriptGUIVector2DistributionField::onConstantModifiedThunkDef ScriptGUIVector2DistributionField::onConstantModifiedThunk; 
	ScriptGUIVector2DistributionField::onConstantConfirmedThunkDef ScriptGUIVector2DistributionField::onConstantConfirmedThunk; 

	ScriptGUIVector2DistributionField::ScriptGUIVector2DistributionField(MonoObject* managedInstance, GUIVector2DistributionField* value)
		:TScriptGUIElement(managedInstance, value)
	{
		value->onClicked.connect(std::bind(&ScriptGUIVector2DistributionField::onClicked, this, std::placeholders::_1));
		value->onConstantModified.connect(std::bind(&ScriptGUIVector2DistributionField::onConstantModified, this));
		value->onConstantConfirmed.connect(std::bind(&ScriptGUIVector2DistributionField::onConstantConfirmed, this));
	}

	void ScriptGUIVector2DistributionField::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_getValue", (void*)&ScriptGUIVector2DistributionField::Internal_getValue);
		metaData.scriptClass->addInternalCall("Internal_setValue", (void*)&ScriptGUIVector2DistributionField::Internal_setValue);
		metaData.scriptClass->addInternalCall("Internal_getType", (void*)&ScriptGUIVector2DistributionField::Internal_getType);
		metaData.scriptClass->addInternalCall("Internal_hasInputFocus", (void*)&ScriptGUIVector2DistributionField::Internal_hasInputFocus);
		metaData.scriptClass->addInternalCall("Internal_create", (void*)&ScriptGUIVector2DistributionField::Internal_create);
		metaData.scriptClass->addInternalCall("Internal_create0", (void*)&ScriptGUIVector2DistributionField::Internal_create0);
		metaData.scriptClass->addInternalCall("Internal_create1", (void*)&ScriptGUIVector2DistributionField::Internal_create1);
		metaData.scriptClass->addInternalCall("Internal_create2", (void*)&ScriptGUIVector2DistributionField::Internal_create2);
		metaData.scriptClass->addInternalCall("Internal_create3", (void*)&ScriptGUIVector2DistributionField::Internal_create3);

		onClickedThunk = (onClickedThunkDef)metaData.scriptClass->getMethodExact("Internal_onClicked", "int")->getThunk();
		onConstantModifiedThunk = (onConstantModifiedThunkDef)metaData.scriptClass->getMethodExact("Internal_onConstantModified", "")->getThunk();
		onConstantConfirmedThunk = (onConstantConfirmedThunkDef)metaData.scriptClass->getMethodExact("Internal_onConstantConfirmed", "")->getThunk();
	}

	void ScriptGUIVector2DistributionField::onClicked(int32_t p0)
	{
		MonoUtil::invokeThunk(onClickedThunk, getManagedInstance(), p0);
	}

	void ScriptGUIVector2DistributionField::onConstantModified()
	{
		MonoUtil::invokeThunk(onConstantModifiedThunk, getManagedInstance());
	}

	void ScriptGUIVector2DistributionField::onConstantConfirmed()
	{
		MonoUtil::invokeThunk(onConstantConfirmedThunk, getManagedInstance());
	}
	MonoObject* ScriptGUIVector2DistributionField::Internal_getValue(ScriptGUIVector2DistributionField* thisPtr)
	{
		SPtr<TDistribution<Vector2>> tmp__output = bs_shared_ptr_new<TDistribution<Vector2>>();
		*tmp__output = static_cast<GUIVector2DistributionField*>(thisPtr->getGUIElement())->getValue();

		MonoObject* __output;
		__output = ScriptTDistributionVector2::create(tmp__output);

		return __output;
	}

	void ScriptGUIVector2DistributionField::Internal_setValue(ScriptGUIVector2DistributionField* thisPtr, MonoObject* value)
	{
		SPtr<TDistribution<Vector2>> tmpvalue;
		ScriptTDistributionVector2* scriptvalue;
		scriptvalue = ScriptTDistributionVector2::toNative(value);
		if(scriptvalue != nullptr)
			tmpvalue = scriptvalue->getInternal();
		static_cast<GUIVector2DistributionField*>(thisPtr->getGUIElement())->setValue(*tmpvalue);
	}

	PropertyDistributionType ScriptGUIVector2DistributionField::Internal_getType(ScriptGUIVector2DistributionField* thisPtr)
	{
		PropertyDistributionType tmp__output;
		tmp__output = static_cast<GUIVector2DistributionField*>(thisPtr->getGUIElement())->getType();

		PropertyDistributionType __output;
		__output = tmp__output;

		return __output;
	}

	bool ScriptGUIVector2DistributionField::Internal_hasInputFocus(ScriptGUIVector2DistributionField* thisPtr)
	{
		bool tmp__output;
		tmp__output = static_cast<GUIVector2DistributionField*>(thisPtr->getGUIElement())->hasInputFocus();

		bool __output;
		__output = tmp__output;

		return __output;
	}

	void ScriptGUIVector2DistributionField::Internal_create(MonoObject* managedInstance, __GUIContentInterop* labelContent, uint32_t labelWidth, MonoString* style)
	{
		GUIContent tmplabelContent;
		tmplabelContent = ScriptGUIContent::fromInterop(*labelContent);
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector2DistributionField* instance = GUIVector2DistributionField::create(tmplabelContent, labelWidth, tmpstyle);
		new (bs_alloc<ScriptGUIVector2DistributionField>())ScriptGUIVector2DistributionField(managedInstance, instance);
	}

	void ScriptGUIVector2DistributionField::Internal_create0(MonoObject* managedInstance, __GUIContentInterop* labelContent, MonoString* style)
	{
		GUIContent tmplabelContent;
		tmplabelContent = ScriptGUIContent::fromInterop(*labelContent);
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector2DistributionField* instance = GUIVector2DistributionField::create(tmplabelContent, tmpstyle);
		new (bs_alloc<ScriptGUIVector2DistributionField>())ScriptGUIVector2DistributionField(managedInstance, instance);
	}

	void ScriptGUIVector2DistributionField::Internal_create1(MonoObject* managedInstance, MonoObject* labelText, uint32_t labelWidth, MonoString* style)
	{
		SPtr<HString> tmplabelText;
		ScriptHString* scriptlabelText;
		scriptlabelText = ScriptHString::toNative(labelText);
		if(scriptlabelText != nullptr)
			tmplabelText = scriptlabelText->getInternal();
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector2DistributionField* instance = GUIVector2DistributionField::create(*tmplabelText, labelWidth, tmpstyle);
		new (bs_alloc<ScriptGUIVector2DistributionField>())ScriptGUIVector2DistributionField(managedInstance, instance);
	}

	void ScriptGUIVector2DistributionField::Internal_create2(MonoObject* managedInstance, MonoObject* labelText, MonoString* style)
	{
		SPtr<HString> tmplabelText;
		ScriptHString* scriptlabelText;
		scriptlabelText = ScriptHString::toNative(labelText);
		if(scriptlabelText != nullptr)
			tmplabelText = scriptlabelText->getInternal();
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector2DistributionField* instance = GUIVector2DistributionField::create(*tmplabelText, tmpstyle);
		new (bs_alloc<ScriptGUIVector2DistributionField>())ScriptGUIVector2DistributionField(managedInstance, instance);
	}

	void ScriptGUIVector2DistributionField::Internal_create3(MonoObject* managedInstance, MonoString* style)
	{
		String tmpstyle;
		tmpstyle = MonoUtil::monoToString(style);
		GUIVector2DistributionField* instance = GUIVector2DistributionField::create(tmpstyle);
		new (bs_alloc<ScriptGUIVector2DistributionField>())ScriptGUIVector2DistributionField(managedInstance, instance);
	}
}
