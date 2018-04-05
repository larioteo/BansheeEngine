#include "BsScriptTKeyframe.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "Wrappers/BsScriptQuaternion.h"
#include "Wrappers/BsScriptVector.h"
#include "Wrappers/BsScriptVector.h"
#include "Wrappers/BsScriptQuaternion.h"

namespace bs
{
	ScriptTKeyframefloat::ScriptTKeyframefloat(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptTKeyframefloat::initRuntimeData()
	{ }

	MonoObject*ScriptTKeyframefloat::box(const TKeyframe<float>& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	TKeyframe<float> ScriptTKeyframefloat::unbox(MonoObject* value)
	{
		return *(TKeyframe<float>*)MonoUtil::unbox(value);
	}


	ScriptTKeyframeVector3::ScriptTKeyframeVector3(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptTKeyframeVector3::initRuntimeData()
	{ }

	MonoObject*ScriptTKeyframeVector3::box(const __TKeyframeVector3Interop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__TKeyframeVector3Interop ScriptTKeyframeVector3::unbox(MonoObject* value)
	{
		return *(__TKeyframeVector3Interop*)MonoUtil::unbox(value);
	}

	TKeyframe<Vector3> ScriptTKeyframeVector3::fromInterop(const __TKeyframeVector3Interop& value)
	{
		TKeyframe<Vector3> output;
		output.value = value.value;
		output.inTangent = value.inTangent;
		output.outTangent = value.outTangent;
		output.time = value.time;

		return output;
	}

	__TKeyframeVector3Interop ScriptTKeyframeVector3::toInterop(const TKeyframe<Vector3>& value)
	{
		__TKeyframeVector3Interop output;
		output.value = value.value;
		output.inTangent = value.inTangent;
		output.outTangent = value.outTangent;
		output.time = value.time;

		return output;
	}


	ScriptTKeyframeQuaternion::ScriptTKeyframeQuaternion(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptTKeyframeQuaternion::initRuntimeData()
	{ }

	MonoObject*ScriptTKeyframeQuaternion::box(const __TKeyframeQuaternionInterop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__TKeyframeQuaternionInterop ScriptTKeyframeQuaternion::unbox(MonoObject* value)
	{
		return *(__TKeyframeQuaternionInterop*)MonoUtil::unbox(value);
	}

	TKeyframe<Quaternion> ScriptTKeyframeQuaternion::fromInterop(const __TKeyframeQuaternionInterop& value)
	{
		TKeyframe<Quaternion> output;
		output.value = value.value;
		output.inTangent = value.inTangent;
		output.outTangent = value.outTangent;
		output.time = value.time;

		return output;
	}

	__TKeyframeQuaternionInterop ScriptTKeyframeQuaternion::toInterop(const TKeyframe<Quaternion>& value)
	{
		__TKeyframeQuaternionInterop output;
		output.value = value.value;
		output.inTangent = value.inTangent;
		output.outTangent = value.outTangent;
		output.time = value.time;

		return output;
	}

}
