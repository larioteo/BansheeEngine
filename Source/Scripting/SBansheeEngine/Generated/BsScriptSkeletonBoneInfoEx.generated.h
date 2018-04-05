#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../SBansheeEngine/Extensions/BsSkeletonEx.h"
#include "Math/BsMatrix4.h"

namespace bs
{
	struct __SkeletonBoneInfoExInterop
	{
		MonoString* name;
		int32_t parent;
		Matrix4 invBindPose;
	};

	class BS_SCR_BE_EXPORT ScriptSkeletonBoneInfoEx : public ScriptObject<ScriptSkeletonBoneInfoEx>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "BoneInfo")

		static MonoObject* box(const __SkeletonBoneInfoExInterop& value);
		static __SkeletonBoneInfoExInterop unbox(MonoObject* value);
		static SkeletonBoneInfoEx fromInterop(const __SkeletonBoneInfoExInterop& value);
		static __SkeletonBoneInfoExInterop toInterop(const SkeletonBoneInfoEx& value);

	private:
		ScriptSkeletonBoneInfoEx(MonoObject* managedInstance);

	};
}
