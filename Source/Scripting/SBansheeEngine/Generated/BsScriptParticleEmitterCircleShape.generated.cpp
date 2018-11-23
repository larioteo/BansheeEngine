#include "BsScriptParticleEmitterCircleShape.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Particles/BsParticleEmitter.h"
#include "BsScriptPARTICLE_CIRCLE_SHAPE_DESC.generated.h"

namespace bs
{
	ScriptParticleEmitterCircleShape::ScriptParticleEmitterCircleShape(MonoObject* managedInstance, const SPtr<ParticleEmitterCircleShape>& value)
		:ScriptObject(managedInstance)
	{
		mInternal = value;
	}

	SPtr<ParticleEmitterCircleShape> ScriptParticleEmitterCircleShape::getInternal() const 
	{
		return std::static_pointer_cast<ParticleEmitterCircleShape>(mInternal);
	}

	void ScriptParticleEmitterCircleShape::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_setOptions", (void*)&ScriptParticleEmitterCircleShape::Internal_setOptions);
		metaData.scriptClass->addInternalCall("Internal_getOptions", (void*)&ScriptParticleEmitterCircleShape::Internal_getOptions);

	}

	MonoObject* ScriptParticleEmitterCircleShape::create(const SPtr<ParticleEmitterCircleShape>& value)
	{
		if(value == nullptr) return nullptr; 

		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		MonoObject* managedInstance = metaData.scriptClass->createInstance("bool", ctorParams);
		new (bs_alloc<ScriptParticleEmitterCircleShape>()) ScriptParticleEmitterCircleShape(managedInstance, value);
		return managedInstance;
	}
	void ScriptParticleEmitterCircleShape::Internal_setOptions(ScriptParticleEmitterCircleShape* thisPtr, __PARTICLE_CIRCLE_SHAPE_DESCInterop* options)
	{
		PARTICLE_CIRCLE_SHAPE_DESC tmpoptions;
		tmpoptions = ScriptPARTICLE_CIRCLE_SHAPE_DESC::fromInterop(*options);
		thisPtr->getInternal()->setOptions(tmpoptions);
	}

	void ScriptParticleEmitterCircleShape::Internal_getOptions(ScriptParticleEmitterCircleShape* thisPtr, __PARTICLE_CIRCLE_SHAPE_DESCInterop* __output)
	{
		PARTICLE_CIRCLE_SHAPE_DESC tmp__output;
		tmp__output = thisPtr->getInternal()->getOptions();

		__PARTICLE_CIRCLE_SHAPE_DESCInterop interop__output;
		interop__output = ScriptPARTICLE_CIRCLE_SHAPE_DESC::toInterop(tmp__output);
		MonoUtil::valueCopy(__output, &interop__output, ScriptPARTICLE_CIRCLE_SHAPE_DESC::getMetaData()->scriptClass->_getInternalClass());
	}
}
