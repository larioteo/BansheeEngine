//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//************** Copyright (c) 2016-2019 Marko Pintera (marko.pintera@gmail.com). All rights reserved. *******************//
#pragma once

#include "BsScriptEditorPrerequisites.h"
#include "BsScriptObject.h"

namespace bs
{
	class ImportOptions;

	class BS_SCR_BED_EXPORT ScriptImportOptionsBase : public ScriptObjectBase
	{
	public:
		ScriptImportOptionsBase(MonoObject* instance);
		virtual ~ScriptImportOptionsBase() {}

		SPtr<ImportOptions> getInternal() const { return mInternal; }
	protected:
		SPtr<ImportOptions> mInternal;
	};

	class BS_SCR_BED_EXPORT ScriptImportOptions : public ScriptObject<ScriptImportOptions, ScriptImportOptionsBase>
	{
	public:
		SCRIPT_OBJ(EDITOR_ASSEMBLY, EDITOR_NS, "ImportOptions")

		ScriptImportOptions(MonoObject* managedInstance, const SPtr<ImportOptions>& value);

		SPtr<ImportOptions> getInternal() const;
		static MonoObject* create(const SPtr<ImportOptions>& value);

	private:
	};
}
