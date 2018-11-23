#include "BsScriptParticleSize.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Particles/BsParticleEvolver.h"
#include "BsScriptPARTICLE_SIZE_DESC.generated.h"

namespace bs
{
	ScriptParticleSize::ScriptParticleSize(MonoObject* managedInstance, const SPtr<ParticleSize>& value)
		:ScriptObject(managedInstance)
	{
		mInternal = value;
	}

	SPtr<ParticleSize> ScriptParticleSize::getInternal() const 
	{
		return std::static_pointer_cast<ParticleSize>(mInternal);
	}

	void ScriptParticleSize::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_setOptions", (void*)&ScriptParticleSize::Internal_setOptions);
		metaData.scriptClass->addInternalCall("Internal_getOptions", (void*)&ScriptParticleSize::Internal_getOptions);

	}

	MonoObject* ScriptParticleSize::create(const SPtr<ParticleSize>& value)
	{
		if(value == nullptr) return nullptr; 

		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		MonoObject* managedInstance = metaData.scriptClass->createInstance("bool", ctorParams);
		new (bs_alloc<ScriptParticleSize>()) ScriptParticleSize(managedInstance, value);
		return managedInstance;
	}
	void ScriptParticleSize::Internal_setOptions(ScriptParticleSize* thisPtr, __PARTICLE_SIZE_DESCInterop* options)
	{
		PARTICLE_SIZE_DESC tmpoptions;
		tmpoptions = ScriptPARTICLE_SIZE_DESC::fromInterop(*options);
		thisPtr->getInternal()->setOptions(tmpoptions);
	}

	void ScriptParticleSize::Internal_getOptions(ScriptParticleSize* thisPtr, __PARTICLE_SIZE_DESCInterop* __output)
	{
		PARTICLE_SIZE_DESC tmp__output;
		tmp__output = thisPtr->getInternal()->getOptions();

		__PARTICLE_SIZE_DESCInterop interop__output;
		interop__output = ScriptPARTICLE_SIZE_DESC::toInterop(tmp__output);
		MonoUtil::valueCopy(__output, &interop__output, ScriptPARTICLE_SIZE_DESC::getMetaData()->scriptClass->_getInternalClass());
	}
}
