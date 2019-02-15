//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//************** Copyright (c) 2016-2019 Marko Pintera (marko.pintera@gmail.com). All rights reserved. *******************//
#pragma once

#include "BsScriptEditorPrerequisites.h"
#include "BsScriptObject.h"
#include "BsScriptImportOptions.editor.generated.h"
#include "../../bsf/Source/Foundation/bsfCore/Importer/BsShaderImportOptions.h"

namespace bs
{
	class ShaderImportOptions;

	class BS_SCR_BED_EXPORT ScriptShaderImportOptions : public ScriptObject<ScriptShaderImportOptions, ScriptImportOptionsBase>
	{
	public:
		SCRIPT_OBJ(EDITOR_ASSEMBLY, EDITOR_NS, "ShaderImportOptions")

		ScriptShaderImportOptions(MonoObject* managedInstance, const SPtr<ShaderImportOptions>& value);

		SPtr<ShaderImportOptions> getInternal() const;
		static MonoObject* create(const SPtr<ShaderImportOptions>& value);

	private:
		static void Internal_setDefine(ScriptShaderImportOptions* thisPtr, MonoString* define, MonoString* value);
		static bool Internal_getDefine(ScriptShaderImportOptions* thisPtr, MonoString* define, MonoString** value);
		static bool Internal_hasDefine(ScriptShaderImportOptions* thisPtr, MonoString* define);
		static void Internal_removeDefine(ScriptShaderImportOptions* thisPtr, MonoString* define);
		static ShadingLanguageFlag Internal_getlanguages(ScriptShaderImportOptions* thisPtr);
		static void Internal_setlanguages(ScriptShaderImportOptions* thisPtr, ShadingLanguageFlag value);
	};
}
