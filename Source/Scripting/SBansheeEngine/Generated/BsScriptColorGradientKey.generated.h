#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfUtility/Image/BsColorGradient.h"
#include "Image/BsColor.h"

namespace bs
{
	struct __ColorGradientKeyInterop
	{
		Color color;
		float time;
	};

	class BS_SCR_BE_EXPORT ScriptColorGradientKey : public ScriptObject<ScriptColorGradientKey>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "ColorGradientKey")

		static MonoObject* box(const __ColorGradientKeyInterop& value);
		static __ColorGradientKeyInterop unbox(MonoObject* value);
		static ColorGradientKey fromInterop(const __ColorGradientKeyInterop& value);
		static __ColorGradientKeyInterop toInterop(const ColorGradientKey& value);

	private:
		ScriptColorGradientKey(MonoObject* managedInstance);

	};
}
