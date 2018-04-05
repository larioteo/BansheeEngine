#include "BsScriptTNamedAnimationCurve.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "BsScriptTAnimationCurve.generated.h"
#include "BsScriptTAnimationCurve.generated.h"
#include "BsScriptTAnimationCurve.generated.h"
#include "BsScriptTAnimationCurve.generated.h"
#include "BsScriptTAnimationCurve.generated.h"
#include "BsScriptTAnimationCurve.generated.h"

namespace bs
{
	ScriptTNamedAnimationCurvefloat::ScriptTNamedAnimationCurvefloat(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptTNamedAnimationCurvefloat::initRuntimeData()
	{ }

	MonoObject*ScriptTNamedAnimationCurvefloat::box(const __TNamedAnimationCurvefloatInterop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__TNamedAnimationCurvefloatInterop ScriptTNamedAnimationCurvefloat::unbox(MonoObject* value)
	{
		return *(__TNamedAnimationCurvefloatInterop*)MonoUtil::unbox(value);
	}

	TNamedAnimationCurve<float> ScriptTNamedAnimationCurvefloat::fromInterop(const __TNamedAnimationCurvefloatInterop& value)
	{
		TNamedAnimationCurve<float> output;
		String tmpname;
		tmpname = MonoUtil::monoToString(value.name);
		output.name = tmpname;
		output.flags = value.flags;
		SPtr<TAnimationCurve<float>> tmpcurve;
		ScriptTAnimationCurvefloat* scriptcurve;
		scriptcurve = ScriptTAnimationCurvefloat::toNative(value.curve);
		if(scriptcurve != nullptr)
			tmpcurve = scriptcurve->getInternal();
		output.curve = *tmpcurve;

		return output;
	}

	__TNamedAnimationCurvefloatInterop ScriptTNamedAnimationCurvefloat::toInterop(const TNamedAnimationCurve<float>& value)
	{
		__TNamedAnimationCurvefloatInterop output;
		MonoString* tmpname;
		tmpname = MonoUtil::stringToMono(value.name);
		output.name = tmpname;
		output.flags = value.flags;
		MonoObject* tmpcurve;
		SPtr<TAnimationCurve<float>> tmpcurvecopy;
		tmpcurvecopy = bs_shared_ptr_new<TAnimationCurve<float>>(value.curve);
		tmpcurve = ScriptTAnimationCurvefloat::create(tmpcurvecopy);
		output.curve = tmpcurve;

		return output;
	}


	ScriptTNamedAnimationCurveVector3::ScriptTNamedAnimationCurveVector3(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptTNamedAnimationCurveVector3::initRuntimeData()
	{ }

	MonoObject*ScriptTNamedAnimationCurveVector3::box(const __TNamedAnimationCurveVector3Interop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__TNamedAnimationCurveVector3Interop ScriptTNamedAnimationCurveVector3::unbox(MonoObject* value)
	{
		return *(__TNamedAnimationCurveVector3Interop*)MonoUtil::unbox(value);
	}

	TNamedAnimationCurve<Vector3> ScriptTNamedAnimationCurveVector3::fromInterop(const __TNamedAnimationCurveVector3Interop& value)
	{
		TNamedAnimationCurve<Vector3> output;
		String tmpname;
		tmpname = MonoUtil::monoToString(value.name);
		output.name = tmpname;
		output.flags = value.flags;
		SPtr<TAnimationCurve<Vector3>> tmpcurve;
		ScriptTAnimationCurveVector3* scriptcurve;
		scriptcurve = ScriptTAnimationCurveVector3::toNative(value.curve);
		if(scriptcurve != nullptr)
			tmpcurve = scriptcurve->getInternal();
		output.curve = *tmpcurve;

		return output;
	}

	__TNamedAnimationCurveVector3Interop ScriptTNamedAnimationCurveVector3::toInterop(const TNamedAnimationCurve<Vector3>& value)
	{
		__TNamedAnimationCurveVector3Interop output;
		MonoString* tmpname;
		tmpname = MonoUtil::stringToMono(value.name);
		output.name = tmpname;
		output.flags = value.flags;
		MonoObject* tmpcurve;
		SPtr<TAnimationCurve<Vector3>> tmpcurvecopy;
		tmpcurvecopy = bs_shared_ptr_new<TAnimationCurve<Vector3>>(value.curve);
		tmpcurve = ScriptTAnimationCurveVector3::create(tmpcurvecopy);
		output.curve = tmpcurve;

		return output;
	}


	ScriptTNamedAnimationCurveQuaternion::ScriptTNamedAnimationCurveQuaternion(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptTNamedAnimationCurveQuaternion::initRuntimeData()
	{ }

	MonoObject*ScriptTNamedAnimationCurveQuaternion::box(const __TNamedAnimationCurveQuaternionInterop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__TNamedAnimationCurveQuaternionInterop ScriptTNamedAnimationCurveQuaternion::unbox(MonoObject* value)
	{
		return *(__TNamedAnimationCurveQuaternionInterop*)MonoUtil::unbox(value);
	}

	TNamedAnimationCurve<Quaternion> ScriptTNamedAnimationCurveQuaternion::fromInterop(const __TNamedAnimationCurveQuaternionInterop& value)
	{
		TNamedAnimationCurve<Quaternion> output;
		String tmpname;
		tmpname = MonoUtil::monoToString(value.name);
		output.name = tmpname;
		output.flags = value.flags;
		SPtr<TAnimationCurve<Quaternion>> tmpcurve;
		ScriptTAnimationCurveQuaternion* scriptcurve;
		scriptcurve = ScriptTAnimationCurveQuaternion::toNative(value.curve);
		if(scriptcurve != nullptr)
			tmpcurve = scriptcurve->getInternal();
		output.curve = *tmpcurve;

		return output;
	}

	__TNamedAnimationCurveQuaternionInterop ScriptTNamedAnimationCurveQuaternion::toInterop(const TNamedAnimationCurve<Quaternion>& value)
	{
		__TNamedAnimationCurveQuaternionInterop output;
		MonoString* tmpname;
		tmpname = MonoUtil::stringToMono(value.name);
		output.name = tmpname;
		output.flags = value.flags;
		MonoObject* tmpcurve;
		SPtr<TAnimationCurve<Quaternion>> tmpcurvecopy;
		tmpcurvecopy = bs_shared_ptr_new<TAnimationCurve<Quaternion>>(value.curve);
		tmpcurve = ScriptTAnimationCurveQuaternion::create(tmpcurvecopy);
		output.curve = tmpcurve;

		return output;
	}

}
