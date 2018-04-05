#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfCore/Animation/BsAnimationCurve.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfCore/Animation/BsAnimationCurve.h"
#include "BsScriptObject.h"
#include "../../../bsf/Source/Foundation/bsfCore/Animation/BsAnimationCurve.h"
#include "Math/BsVector3.h"
#include "Math/BsQuaternion.h"

namespace bs
{
	class BS_SCR_BE_EXPORT ScriptTKeyframefloat : public ScriptObject<ScriptTKeyframefloat>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "KeyFrame")

		static MonoObject* box(const TKeyframe<float>& value);
		static TKeyframe<float> unbox(MonoObject* value);

	private:
		ScriptTKeyframefloat(MonoObject* managedInstance);

	};

	struct __TKeyframeVector3Interop
	{
		Vector3 value;
		Vector3 inTangent;
		Vector3 outTangent;
		float time;
	};

	class BS_SCR_BE_EXPORT ScriptTKeyframeVector3 : public ScriptObject<ScriptTKeyframeVector3>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "KeyFrameVec3")

		static MonoObject* box(const __TKeyframeVector3Interop& value);
		static __TKeyframeVector3Interop unbox(MonoObject* value);
		static TKeyframe<Vector3> fromInterop(const __TKeyframeVector3Interop& value);
		static __TKeyframeVector3Interop toInterop(const TKeyframe<Vector3>& value);

	private:
		ScriptTKeyframeVector3(MonoObject* managedInstance);

	};

	struct __TKeyframeQuaternionInterop
	{
		Quaternion value;
		Quaternion inTangent;
		Quaternion outTangent;
		float time;
	};

	class BS_SCR_BE_EXPORT ScriptTKeyframeQuaternion : public ScriptObject<ScriptTKeyframeQuaternion>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "KeyFrameQuat")

		static MonoObject* box(const __TKeyframeQuaternionInterop& value);
		static __TKeyframeQuaternionInterop unbox(MonoObject* value);
		static TKeyframe<Quaternion> fromInterop(const __TKeyframeQuaternionInterop& value);
		static __TKeyframeQuaternionInterop toInterop(const TKeyframe<Quaternion>& value);

	private:
		ScriptTKeyframeQuaternion(MonoObject* managedInstance);

	};
}
