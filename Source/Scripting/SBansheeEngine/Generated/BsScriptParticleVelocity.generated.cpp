#include "BsScriptParticleVelocity.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Particles/BsParticleEvolver.h"
#include "BsScriptPARTICLE_VELOCITY_DESC.generated.h"

namespace bs
{
	ScriptParticleVelocity::ScriptParticleVelocity(MonoObject* managedInstance, const SPtr<ParticleVelocity>& value)
		:ScriptObject(managedInstance)
	{
		mInternal = value;
	}

	SPtr<ParticleVelocity> ScriptParticleVelocity::getInternal() const 
	{
		return std::static_pointer_cast<ParticleVelocity>(mInternal);
	}

	void ScriptParticleVelocity::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_setOptions", (void*)&ScriptParticleVelocity::Internal_setOptions);
		metaData.scriptClass->addInternalCall("Internal_getOptions", (void*)&ScriptParticleVelocity::Internal_getOptions);

	}

	MonoObject* ScriptParticleVelocity::create(const SPtr<ParticleVelocity>& value)
	{
		if(value == nullptr) return nullptr; 

		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		MonoObject* managedInstance = metaData.scriptClass->createInstance("bool", ctorParams);
		new (bs_alloc<ScriptParticleVelocity>()) ScriptParticleVelocity(managedInstance, value);
		return managedInstance;
	}
	void ScriptParticleVelocity::Internal_setOptions(ScriptParticleVelocity* thisPtr, __PARTICLE_VELOCITY_DESCInterop* options)
	{
		PARTICLE_VELOCITY_DESC tmpoptions;
		tmpoptions = ScriptPARTICLE_VELOCITY_DESC::fromInterop(*options);
		thisPtr->getInternal()->setOptions(tmpoptions);
	}

	void ScriptParticleVelocity::Internal_getOptions(ScriptParticleVelocity* thisPtr, __PARTICLE_VELOCITY_DESCInterop* __output)
	{
		PARTICLE_VELOCITY_DESC tmp__output;
		tmp__output = thisPtr->getInternal()->getOptions();

		__PARTICLE_VELOCITY_DESCInterop interop__output;
		interop__output = ScriptPARTICLE_VELOCITY_DESC::toInterop(tmp__output);
		MonoUtil::valueCopy(__output, &interop__output, ScriptPARTICLE_VELOCITY_DESC::getMetaData()->scriptClass->_getInternalClass());
	}
}
