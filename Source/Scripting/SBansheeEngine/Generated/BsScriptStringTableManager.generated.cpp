#include "BsScriptStringTableManager.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Localization/BsStringTableManager.h"
#include "BsScriptResourceManager.h"
#include "BsScriptStringTable.generated.h"

namespace bs
{
	ScriptStringTableManager::ScriptStringTableManager(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{
	}

	void ScriptStringTableManager::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_setActiveLanguage", (void*)&ScriptStringTableManager::Internal_setActiveLanguage);
		metaData.scriptClass->addInternalCall("Internal_getActiveLanguage", (void*)&ScriptStringTableManager::Internal_getActiveLanguage);
		metaData.scriptClass->addInternalCall("Internal_getTable", (void*)&ScriptStringTableManager::Internal_getTable);
		metaData.scriptClass->addInternalCall("Internal_removeTable", (void*)&ScriptStringTableManager::Internal_removeTable);
		metaData.scriptClass->addInternalCall("Internal_setTable", (void*)&ScriptStringTableManager::Internal_setTable);

	}

	void ScriptStringTableManager::Internal_setActiveLanguage(Language language)
	{
		StringTableManager::instance().setActiveLanguage(language);
	}

	Language ScriptStringTableManager::Internal_getActiveLanguage()
	{
		Language tmp__output;
		tmp__output = StringTableManager::instance().getActiveLanguage();

		Language __output;
		__output = tmp__output;

		return __output;
	}

	MonoObject* ScriptStringTableManager::Internal_getTable(uint32_t id)
	{
		ResourceHandle<StringTable> tmp__output;
		tmp__output = StringTableManager::instance().getTable(id);

		MonoObject* __output;
		ScriptResourceBase* script__output;
		script__output = ScriptResourceManager::instance().getScriptResource(tmp__output, true);
		if(script__output != nullptr)
			__output = script__output->getManagedInstance();
		else
			__output = nullptr;

		return __output;
	}

	void ScriptStringTableManager::Internal_removeTable(uint32_t id)
	{
		StringTableManager::instance().removeTable(id);
	}

	void ScriptStringTableManager::Internal_setTable(uint32_t id, MonoObject* table)
	{
		ResourceHandle<StringTable> tmptable;
		ScriptStringTable* scripttable;
		scripttable = ScriptStringTable::toNative(table);
		if(scripttable != nullptr)
			tmptable = scripttable->getHandle();
		StringTableManager::instance().setTable(id, tmptable);
	}
}
