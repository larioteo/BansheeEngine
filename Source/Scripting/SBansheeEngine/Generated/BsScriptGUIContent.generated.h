#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfEngine/GUI/BsGUIContent.h"
#include "../../../bsf/Source/Foundation/bsfCore/Localization/BsHString.h"
#include "../../../bsf/Source/Foundation/bsfEngine/GUI/BsGUIContent.h"
#include "BsScriptGUIContentImages.generated.h"

namespace bs
{
	struct __GUIContentInterop
	{
		MonoObject* text;
		__GUIContentImagesInterop images;
		MonoObject* tooltip;
	};

	class BS_SCR_BE_EXPORT ScriptGUIContent : public ScriptObject<ScriptGUIContent>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "GUIContent")

		static MonoObject* box(const __GUIContentInterop& value);
		static __GUIContentInterop unbox(MonoObject* value);
		static GUIContent fromInterop(const __GUIContentInterop& value);
		static __GUIContentInterop toInterop(const GUIContent& value);

	private:
		ScriptGUIContent(MonoObject* managedInstance);

	};
}
