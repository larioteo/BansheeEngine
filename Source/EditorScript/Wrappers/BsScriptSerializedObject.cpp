//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Wrappers/BsScriptSerializedObject.h"
#include "BsScriptMeta.h"
#include "BsMonoClass.h"
#include "Wrappers/BsScriptManagedComponent.h"
#include "Wrappers/BsScriptManagedResource.h"
#include "BsManagedComponent.h"
#include "BsManagedResource.h"
#include "Serialization/BsManagedSerializableObject.h"
#include "Serialization/BsScriptAssemblyManager.h"
#include "Reflection/BsRTTIType.h"
#include "BsScriptGameObjectManager.h"
#include "Serialization/BsSerializedObject.h"

namespace bs
{
	ScriptSerializedObject::ScriptSerializedObject(MonoObject* instance, const SPtr<IReflectable>& obj)
		: ScriptObject(instance), mSerializedObject(obj)
	{

	}

	void ScriptSerializedObject::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateComponent", (void*)&ScriptSerializedObject::internal_CreateComponent);
		metaData.scriptClass->addInternalCall("Internal_CreateResource", (void*)&ScriptSerializedObject::internal_CreateResource);
		metaData.scriptClass->addInternalCall("Internal_CreateGeneric", (void*)&ScriptSerializedObject::internal_CreateGeneric);
		metaData.scriptClass->addInternalCall("Internal_Deserialize", (void*)&ScriptSerializedObject::internal_Deserialize);
	}

	MonoObject* ScriptSerializedObject::internal_CreateComponent(ScriptComponentBase* componentPtr)
	{
		HComponent component = componentPtr->getComponent();
		if (component.isDestroyed())
			return nullptr;

		SPtr<IReflectable> serializedObject;
		if (rtti_is_of_type<ManagedComponent>(component.get()))
		{
			ManagedComponent* managedComponent = static_cast<ManagedComponent*>(component.get());
			MonoObject* managedInstance = managedComponent->getManagedInstance();

			SPtr<ManagedSerializableObject> managedSerializedObject = ManagedSerializableObject::createFromExisting(managedInstance);
			if (managedSerializedObject == nullptr)
				return nullptr;

			managedSerializedObject->serialize();
			serializedObject = managedSerializedObject;
		}
		else
			serializedObject = SerializedObject::create(*component.get());


		MonoObject* instance = metaData.scriptClass->createInstance();
		new (bs_alloc<ScriptSerializedObject>()) ScriptSerializedObject(instance, serializedObject);

		return instance;
	}

	MonoObject* ScriptSerializedObject::internal_CreateResource(ScriptManagedResource* resourcePtr)
	{
		HManagedResource resource = resourcePtr->getHandle();
		if (!resource.isLoaded())
			return nullptr;

		MonoObject* managedInstance = resource->getManagedInstance();
		SPtr<ManagedSerializableObject> serializedObject = ManagedSerializableObject::createFromExisting(managedInstance);
		if (serializedObject == nullptr)
			return nullptr;

		serializedObject->serialize();

		MonoObject* instance = metaData.scriptClass->createInstance();
		new (bs_alloc<ScriptSerializedObject>()) ScriptSerializedObject(instance, serializedObject);

		return instance;
	}

	MonoObject* ScriptSerializedObject::internal_CreateGeneric(MonoObject* obj)
	{
		if (obj == nullptr)
			return nullptr;

		SPtr<IReflectable> nativeValue = ScriptAssemblyManager::instance().getReflectableFromManagedObject(obj);
		if (!nativeValue)
			return nullptr;

		if(!rtti_is_of_type<ManagedSerializableObject>(nativeValue))
			nativeValue = SerializedObject::create(*nativeValue);

		MonoObject* instance = metaData.scriptClass->createInstance();
		new (bs_alloc<ScriptSerializedObject>()) ScriptSerializedObject(instance, nativeValue);

		return instance;
	}

	MonoObject* ScriptSerializedObject::internal_Deserialize(ScriptSerializedObject* thisPtr)
	{
		SPtr<IReflectable> serializedObject = thisPtr->mSerializedObject;
		if (serializedObject == nullptr)
			return nullptr;

		if(auto managedSerializableObject = rtti_cast<ManagedSerializableObject>(serializedObject))
		{
			if (!managedSerializableObject)
				return nullptr;

			return managedSerializableObject->deserialize();
		}
		else
		{
			if(auto nativeSerializedObject = rtti_cast<SerializedObject>(serializedObject))
			{
				SPtr<IReflectable> obj = nativeSerializedObject->decode();

				UINT32 rttiId = obj->getRTTI()->getRTTIId();
				const ReflectableTypeInfo* reflTypeInfo = ScriptAssemblyManager::instance().getReflectableTypeInfo(rttiId);
				if (reflTypeInfo == nullptr)
				{
					LOGERR(StringUtil::format("Mapping between a reflectable object and a managed type is missing "
						"for type \"{0}\"", rttiId))
						return nullptr;
				}

				return reflTypeInfo->createCallback(obj);
			}
		}

		return nullptr;
	}
}
