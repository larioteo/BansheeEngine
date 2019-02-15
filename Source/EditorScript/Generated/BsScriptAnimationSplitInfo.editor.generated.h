//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//************** Copyright (c) 2016-2019 Marko Pintera (marko.pintera@gmail.com). All rights reserved. *******************//
#pragma once

#include "BsScriptEditorPrerequisites.h"
#include "BsScriptObject.h"

namespace bs
{
	struct AnimationSplitInfo;

	class BS_SCR_BED_EXPORT ScriptAnimationSplitInfo : public ScriptObject<ScriptAnimationSplitInfo>
	{
	public:
		SCRIPT_OBJ(EDITOR_ASSEMBLY, EDITOR_NS, "AnimationSplitInfo")

		ScriptAnimationSplitInfo(MonoObject* managedInstance, const SPtr<AnimationSplitInfo>& value);

		SPtr<AnimationSplitInfo> getInternal() const { return mInternal; }
		static MonoObject* create(const SPtr<AnimationSplitInfo>& value);

	private:
		SPtr<AnimationSplitInfo> mInternal;

		static void Internal_AnimationSplitInfo(MonoObject* managedInstance);
		static void Internal_AnimationSplitInfo0(MonoObject* managedInstance, MonoString* name, uint32_t startFrame, uint32_t endFrame, bool isAdditive);
		static MonoString* Internal_getname(ScriptAnimationSplitInfo* thisPtr);
		static void Internal_setname(ScriptAnimationSplitInfo* thisPtr, MonoString* value);
		static uint32_t Internal_getstartFrame(ScriptAnimationSplitInfo* thisPtr);
		static void Internal_setstartFrame(ScriptAnimationSplitInfo* thisPtr, uint32_t value);
		static uint32_t Internal_getendFrame(ScriptAnimationSplitInfo* thisPtr);
		static void Internal_setendFrame(ScriptAnimationSplitInfo* thisPtr, uint32_t value);
		static bool Internal_getisAdditive(ScriptAnimationSplitInfo* thisPtr);
		static void Internal_setisAdditive(ScriptAnimationSplitInfo* thisPtr, bool value);
	};
}
