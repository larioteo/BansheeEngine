#include "BsScriptTAnimationCurve.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "BsScriptTKeyframe.generated.h"
#include "BsScriptTKeyframe.generated.h"
#include "BsScriptTKeyframe.generated.h"
#include "Wrappers/BsScriptVector.h"
#include "Wrappers/BsScriptQuaternion.h"

namespace bs
{
	ScriptTAnimationCurvefloat::ScriptTAnimationCurvefloat(MonoObject* managedInstance, const SPtr<TAnimationCurve<float>>& value)
		:ScriptObject(managedInstance), mInternal(value)
	{
	}

	void ScriptTAnimationCurvefloat::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_TAnimationCurve", (void*)&ScriptTAnimationCurvefloat::Internal_TAnimationCurve);
		metaData.scriptClass->addInternalCall("Internal_evaluate", (void*)&ScriptTAnimationCurvefloat::Internal_evaluate);
		metaData.scriptClass->addInternalCall("Internal_getKeyFrames", (void*)&ScriptTAnimationCurvefloat::Internal_getKeyFrames);

	}

	MonoObject* ScriptTAnimationCurvefloat::create(const SPtr<TAnimationCurve<float>>& value)
	{
		if(value == nullptr) return nullptr; 

		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		MonoObject* managedInstance = metaData.scriptClass->createInstance("bool", ctorParams);
		new (bs_alloc<ScriptTAnimationCurvefloat>()) ScriptTAnimationCurvefloat(managedInstance, value);
		return managedInstance;
	}
	void ScriptTAnimationCurvefloat::Internal_TAnimationCurve(MonoObject* managedInstance, MonoArray* keyframes)
	{
		Vector<TKeyframe<float>> veckeyframes;
		if(keyframes != nullptr)
		{
			ScriptArray arraykeyframes(keyframes);
			veckeyframes.resize(arraykeyframes.size());
			for(int i = 0; i < (int)arraykeyframes.size(); i++)
			{
				veckeyframes[i] = arraykeyframes.get<TKeyframe<float>>(i);
			}
		}
		SPtr<TAnimationCurve<float>> instance = bs_shared_ptr_new<TAnimationCurve<float>>(veckeyframes);
		new (bs_alloc<ScriptTAnimationCurvefloat>())ScriptTAnimationCurvefloat(managedInstance, instance);
	}

	float ScriptTAnimationCurvefloat::Internal_evaluate(ScriptTAnimationCurvefloat* thisPtr, float time, bool loop)
	{
		float tmp__output;
		tmp__output = thisPtr->getInternal()->evaluate(time, loop);

		float __output;
		__output = tmp__output;

		return __output;
	}

	MonoArray* ScriptTAnimationCurvefloat::Internal_getKeyFrames(ScriptTAnimationCurvefloat* thisPtr)
	{
		Vector<TKeyframe<float>> vec__output;
		vec__output = thisPtr->getInternal()->getKeyFrames();

		MonoArray* __output;
		int arraySize__output = (int)vec__output.size();
		ScriptArray array__output = ScriptArray::create<ScriptTKeyframefloat>(arraySize__output);
		for(int i = 0; i < arraySize__output; i++)
		{
			array__output.set(i, vec__output[i]);
		}
		__output = array__output.getInternal();

		return __output;
	}

	ScriptTAnimationCurveVector3::ScriptTAnimationCurveVector3(MonoObject* managedInstance, const SPtr<TAnimationCurve<Vector3>>& value)
		:ScriptObject(managedInstance), mInternal(value)
	{
	}

	void ScriptTAnimationCurveVector3::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_TAnimationCurve", (void*)&ScriptTAnimationCurveVector3::Internal_TAnimationCurve);
		metaData.scriptClass->addInternalCall("Internal_evaluate", (void*)&ScriptTAnimationCurveVector3::Internal_evaluate);
		metaData.scriptClass->addInternalCall("Internal_getKeyFrames", (void*)&ScriptTAnimationCurveVector3::Internal_getKeyFrames);

	}

	MonoObject* ScriptTAnimationCurveVector3::create(const SPtr<TAnimationCurve<Vector3>>& value)
	{
		if(value == nullptr) return nullptr; 

		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		MonoObject* managedInstance = metaData.scriptClass->createInstance("bool", ctorParams);
		new (bs_alloc<ScriptTAnimationCurveVector3>()) ScriptTAnimationCurveVector3(managedInstance, value);
		return managedInstance;
	}
	void ScriptTAnimationCurveVector3::Internal_TAnimationCurve(MonoObject* managedInstance, MonoArray* keyframes)
	{
		Vector<TKeyframe<Vector3>> veckeyframes;
		if(keyframes != nullptr)
		{
			ScriptArray arraykeyframes(keyframes);
			veckeyframes.resize(arraykeyframes.size());
			for(int i = 0; i < (int)arraykeyframes.size(); i++)
			{
				veckeyframes[i] = ScriptTKeyframeVector3::fromInterop(arraykeyframes.get<__TKeyframeVector3Interop>(i));
			}
		}
		SPtr<TAnimationCurve<Vector3>> instance = bs_shared_ptr_new<TAnimationCurve<Vector3>>(veckeyframes);
		new (bs_alloc<ScriptTAnimationCurveVector3>())ScriptTAnimationCurveVector3(managedInstance, instance);
	}

	void ScriptTAnimationCurveVector3::Internal_evaluate(ScriptTAnimationCurveVector3* thisPtr, float time, bool loop, Vector3* __output)
	{
		Vector3 tmp__output;
		tmp__output = thisPtr->getInternal()->evaluate(time, loop);

		*__output = tmp__output;
	}

	MonoArray* ScriptTAnimationCurveVector3::Internal_getKeyFrames(ScriptTAnimationCurveVector3* thisPtr)
	{
		Vector<TKeyframe<Vector3>> vec__output;
		vec__output = thisPtr->getInternal()->getKeyFrames();

		MonoArray* __output;
		int arraySize__output = (int)vec__output.size();
		ScriptArray array__output = ScriptArray::create<ScriptTKeyframeVector3>(arraySize__output);
		for(int i = 0; i < arraySize__output; i++)
		{
			array__output.set(i, ScriptTKeyframeVector3::toInterop(vec__output[i]));
		}
		__output = array__output.getInternal();

		return __output;
	}

	ScriptTAnimationCurveQuaternion::ScriptTAnimationCurveQuaternion(MonoObject* managedInstance, const SPtr<TAnimationCurve<Quaternion>>& value)
		:ScriptObject(managedInstance), mInternal(value)
	{
	}

	void ScriptTAnimationCurveQuaternion::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_TAnimationCurve", (void*)&ScriptTAnimationCurveQuaternion::Internal_TAnimationCurve);
		metaData.scriptClass->addInternalCall("Internal_evaluate", (void*)&ScriptTAnimationCurveQuaternion::Internal_evaluate);
		metaData.scriptClass->addInternalCall("Internal_getKeyFrames", (void*)&ScriptTAnimationCurveQuaternion::Internal_getKeyFrames);

	}

	MonoObject* ScriptTAnimationCurveQuaternion::create(const SPtr<TAnimationCurve<Quaternion>>& value)
	{
		if(value == nullptr) return nullptr; 

		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		MonoObject* managedInstance = metaData.scriptClass->createInstance("bool", ctorParams);
		new (bs_alloc<ScriptTAnimationCurveQuaternion>()) ScriptTAnimationCurveQuaternion(managedInstance, value);
		return managedInstance;
	}
	void ScriptTAnimationCurveQuaternion::Internal_TAnimationCurve(MonoObject* managedInstance, MonoArray* keyframes)
	{
		Vector<TKeyframe<Quaternion>> veckeyframes;
		if(keyframes != nullptr)
		{
			ScriptArray arraykeyframes(keyframes);
			veckeyframes.resize(arraykeyframes.size());
			for(int i = 0; i < (int)arraykeyframes.size(); i++)
			{
				veckeyframes[i] = ScriptTKeyframeQuaternion::fromInterop(arraykeyframes.get<__TKeyframeQuaternionInterop>(i));
			}
		}
		SPtr<TAnimationCurve<Quaternion>> instance = bs_shared_ptr_new<TAnimationCurve<Quaternion>>(veckeyframes);
		new (bs_alloc<ScriptTAnimationCurveQuaternion>())ScriptTAnimationCurveQuaternion(managedInstance, instance);
	}

	void ScriptTAnimationCurveQuaternion::Internal_evaluate(ScriptTAnimationCurveQuaternion* thisPtr, float time, bool loop, Quaternion* __output)
	{
		Quaternion tmp__output;
		tmp__output = thisPtr->getInternal()->evaluate(time, loop);

		*__output = tmp__output;
	}

	MonoArray* ScriptTAnimationCurveQuaternion::Internal_getKeyFrames(ScriptTAnimationCurveQuaternion* thisPtr)
	{
		Vector<TKeyframe<Quaternion>> vec__output;
		vec__output = thisPtr->getInternal()->getKeyFrames();

		MonoArray* __output;
		int arraySize__output = (int)vec__output.size();
		ScriptArray array__output = ScriptArray::create<ScriptTKeyframeQuaternion>(arraySize__output);
		for(int i = 0; i < arraySize__output; i++)
		{
			array__output.set(i, ScriptTKeyframeQuaternion::toInterop(vec__output[i]));
		}
		__output = array__output.getInternal();

		return __output;
	}
}
