#include "BsScriptParticleGravity.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Particles/BsParticleEvolver.h"
#include "BsScriptPARTICLE_GRAVITY_DESC.generated.h"

namespace bs
{
	ScriptParticleGravity::ScriptParticleGravity(MonoObject* managedInstance, const SPtr<ParticleGravity>& value)
		:ScriptObject(managedInstance)
	{
		mInternal = value;
	}

	SPtr<ParticleGravity> ScriptParticleGravity::getInternal() const 
	{
		return std::static_pointer_cast<ParticleGravity>(mInternal);
	}

	void ScriptParticleGravity::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_setOptions", (void*)&ScriptParticleGravity::Internal_setOptions);
		metaData.scriptClass->addInternalCall("Internal_getOptions", (void*)&ScriptParticleGravity::Internal_getOptions);

	}

	MonoObject* ScriptParticleGravity::create(const SPtr<ParticleGravity>& value)
	{
		if(value == nullptr) return nullptr; 

		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		MonoObject* managedInstance = metaData.scriptClass->createInstance("bool", ctorParams);
		new (bs_alloc<ScriptParticleGravity>()) ScriptParticleGravity(managedInstance, value);
		return managedInstance;
	}
	void ScriptParticleGravity::Internal_setOptions(ScriptParticleGravity* thisPtr, PARTICLE_GRAVITY_DESC* options)
	{
		thisPtr->getInternal()->setOptions(*options);
	}

	void ScriptParticleGravity::Internal_getOptions(ScriptParticleGravity* thisPtr, PARTICLE_GRAVITY_DESC* __output)
	{
		PARTICLE_GRAVITY_DESC tmp__output;
		tmp__output = thisPtr->getInternal()->getOptions();

		*__output = tmp__output;
	}
}
