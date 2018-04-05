#include "BsScriptAnimationUtility.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Animation/BsAnimationUtility.h"
#include "BsScriptTAnimationCurve.generated.h"
#include "BsScriptTAnimationCurve.generated.h"
#include "BsScriptTAnimationCurve.generated.h"

namespace bs
{
	ScriptAnimationUtility::ScriptAnimationUtility(MonoObject* managedInstance, const SPtr<AnimationUtility>& value)
		:ScriptObject(managedInstance), mInternal(value)
	{
	}

	void ScriptAnimationUtility::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_eulerToQuaternionCurve", (void*)&ScriptAnimationUtility::Internal_eulerToQuaternionCurve);
		metaData.scriptClass->addInternalCall("Internal_quaternionToEulerCurve", (void*)&ScriptAnimationUtility::Internal_quaternionToEulerCurve);
		metaData.scriptClass->addInternalCall("Internal_splitCurve", (void*)&ScriptAnimationUtility::Internal_splitCurve);
		metaData.scriptClass->addInternalCall("Internal_combineCurve", (void*)&ScriptAnimationUtility::Internal_combineCurve);

	}

	MonoObject* ScriptAnimationUtility::create(const SPtr<AnimationUtility>& value)
	{
		if(value == nullptr) return nullptr; 

		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		MonoObject* managedInstance = metaData.scriptClass->createInstance("bool", ctorParams);
		new (bs_alloc<ScriptAnimationUtility>()) ScriptAnimationUtility(managedInstance, value);
		return managedInstance;
	}
	MonoObject* ScriptAnimationUtility::Internal_eulerToQuaternionCurve(MonoObject* eulerCurve)
	{
		SPtr<TAnimationCurve<Quaternion>> tmp__output;
		SPtr<TAnimationCurve<Vector3>> tmpeulerCurve;
		ScriptTAnimationCurveVector3* scripteulerCurve;
		scripteulerCurve = ScriptTAnimationCurveVector3::toNative(eulerCurve);
		tmpeulerCurve = scripteulerCurve->getInternal();
		tmp__output = AnimationUtility::eulerToQuaternionCurve(tmpeulerCurve);

		MonoObject* __output;
		__output = ScriptTAnimationCurveQuaternion::create(tmp__output);

		return __output;
	}

	MonoObject* ScriptAnimationUtility::Internal_quaternionToEulerCurve(MonoObject* quatCurve)
	{
		SPtr<TAnimationCurve<Vector3>> tmp__output;
		SPtr<TAnimationCurve<Quaternion>> tmpquatCurve;
		ScriptTAnimationCurveQuaternion* scriptquatCurve;
		scriptquatCurve = ScriptTAnimationCurveQuaternion::toNative(quatCurve);
		tmpquatCurve = scriptquatCurve->getInternal();
		tmp__output = AnimationUtility::quaternionToEulerCurve(tmpquatCurve);

		MonoObject* __output;
		__output = ScriptTAnimationCurveVector3::create(tmp__output);

		return __output;
	}

	MonoArray* ScriptAnimationUtility::Internal_splitCurve(MonoObject* compoundCurve)
	{
		Vector<SPtr<TAnimationCurve<float>>> vec__output;
		SPtr<TAnimationCurve<Vector3>> tmpcompoundCurve;
		ScriptTAnimationCurveVector3* scriptcompoundCurve;
		scriptcompoundCurve = ScriptTAnimationCurveVector3::toNative(compoundCurve);
		tmpcompoundCurve = scriptcompoundCurve->getInternal();
		vec__output = AnimationUtility::splitCurve(tmpcompoundCurve);

		MonoArray* __output;
		int arraySize__output = (int)vec__output.size();
		ScriptArray array__output = ScriptArray::create<ScriptTAnimationCurvefloat>(arraySize__output);
		for(int i = 0; i < arraySize__output; i++)
		{
			array__output.set(i, ScriptTAnimationCurvefloat::create(vec__output[i]));
		}
		__output = array__output.getInternal();

		return __output;
	}

	MonoObject* ScriptAnimationUtility::Internal_combineCurve(MonoArray* curveComponents)
	{
		SPtr<TAnimationCurve<Vector3>> tmp__output;
		Vector<SPtr<TAnimationCurve<float>>> veccurveComponents;
		if(curveComponents != nullptr)
		{
			ScriptArray arraycurveComponents(curveComponents);
			veccurveComponents.resize(arraycurveComponents.size());
			for(int i = 0; i < (int)arraycurveComponents.size(); i++)
			{
				ScriptTAnimationCurvefloat* scriptcurveComponents;
				scriptcurveComponents = ScriptTAnimationCurvefloat::toNative(arraycurveComponents.get<MonoObject*>(i));
				if(scriptcurveComponents != nullptr)
					veccurveComponents[i] = scriptcurveComponents->getInternal();
			}
		}
		tmp__output = AnimationUtility::combineCurve(veccurveComponents);

		MonoObject* __output;
		__output = ScriptTAnimationCurveVector3::create(tmp__output);

		return __output;
	}
}
