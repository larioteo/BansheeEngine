//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Serialization/BsManagedDiff.h"
#include "Serialization/BsManagedSerializableDiff.h"
#include "Serialization/BsBinarySerializer.h"
#include "Serialization/BsMemorySerializer.h"
#include "Serialization/BsManagedSerializableObject.h"
#include "Scene/BsGameObjectManager.h"
#include "Reflection/BsRTTIType.h"

namespace bs
{
	SPtr<SerializedObject> ManagedDiff::generateDiff(const SPtr<SerializedObject>& orgSerzObj,
		const SPtr<SerializedObject>& newSerzObj, ObjectMap& objectMap)
	{
		// Need to call GameObjectManager because GameObject handles call it during deserialization, but we don't really need it
		GameObjectManager::instance().startDeserialization();
		SPtr<ManagedSerializableObject> orgObj = std::static_pointer_cast<ManagedSerializableObject>(orgSerzObj->decode());
		SPtr<ManagedSerializableObject> newObj = std::static_pointer_cast<ManagedSerializableObject>(newSerzObj->decode());
		GameObjectManager::instance().endDeserialization();

		SPtr<ManagedSerializableDiff> diff = ManagedSerializableDiff::create(orgObj, newObj);
		if (diff == nullptr)
			return nullptr;

		SPtr<SerializedObject> output = bs_shared_ptr_new<SerializedObject>();
		output->subObjects.push_back(SerializedSubObject());

		SerializedSubObject& subObject = output->subObjects.back();
		subObject.typeId = ManagedSerializableObject::getRTTIStatic()->getRTTIId();

		SerializedEntry entry;
		entry.fieldId = 0;
		entry.serialized = SerializedObject::create(*diff);

		subObject.entries[0] = entry;

		return output;
	}

	void ManagedDiff::applyDiff(const SPtr<IReflectable>& object, const SPtr<SerializedObject>& serzDiff,
		FrameAlloc& alloc, DiffObjectMap& objectMap, FrameVector<DiffCommand>& diffCommands)
	{
		SPtr<SerializedObject> diffObj = std::static_pointer_cast<SerializedObject>(serzDiff->subObjects[0].entries[0].serialized);

		SPtr<ManagedSerializableDiff> diff = std::static_pointer_cast<ManagedSerializableDiff>(diffObj->decode());
		
		if (diff != nullptr)
		{
			SPtr<ManagedSerializableObject> managedObj = std::static_pointer_cast<ManagedSerializableObject>(object);
			diff->apply(managedObj);
		}
	}
}