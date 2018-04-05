#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../SBansheeEngine/Extensions/BsShaderEx.h"
#include "../../SBansheeEngine/Extensions/BsShaderEx.h"

namespace bs
{
	struct __ShaderParameterInterop
	{
		MonoString* name;
		ShaderParameterType type;
		bool isInternal;
	};

	class BS_SCR_BE_EXPORT ScriptShaderParameter : public ScriptObject<ScriptShaderParameter>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "ShaderParameter")

		static MonoObject* box(const __ShaderParameterInterop& value);
		static __ShaderParameterInterop unbox(MonoObject* value);
		static ShaderParameter fromInterop(const __ShaderParameterInterop& value);
		static __ShaderParameterInterop toInterop(const ShaderParameter& value);

	private:
		ScriptShaderParameter(MonoObject* managedInstance);

	};
}
