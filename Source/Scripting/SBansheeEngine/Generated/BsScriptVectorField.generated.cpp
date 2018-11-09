#include "BsScriptVectorField.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Particles/BsVectorField.h"

namespace bs
{
	ScriptVectorField::ScriptVectorField(MonoObject* managedInstance, const ResourceHandle<VectorField>& value)
		:TScriptResource(managedInstance, value)
	{
	}

	void ScriptVectorField::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_GetRef", (void*)&ScriptVectorField::Internal_getRef);

	}

	 MonoObject*ScriptVectorField::createInstance()
	{
		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		return metaData.scriptClass->createInstance("bool", ctorParams);
	}
	MonoObject* ScriptVectorField::Internal_getRef(ScriptVectorField* thisPtr)
	{
		return thisPtr->getRRef();
	}

}
