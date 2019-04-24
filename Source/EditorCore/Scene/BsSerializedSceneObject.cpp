//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2019 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Scene/BsSerializedSceneObject.h"
#include "Scene/BsSceneObject.h"
#include "Serialization/BsMemorySerializer.h"
#include "Utility/BsUtility.h"

namespace bs
{
	SerializedSceneObject::SerializedSceneObject(const HSceneObject& sceneObject, bool hierarchy)
		:mSceneObject(sceneObject), mRecordHierarchy(hierarchy)
	{
		if(mSceneObject.isDestroyed())
			return;

		UINT32 numChildren = mSceneObject->getNumChildren();
		HSceneObject* children = nullptr;

		if (!mRecordHierarchy)
		{
			children = bs_stack_new<HSceneObject>(numChildren);
			for (UINT32 i = 0; i < numChildren; i++)
			{
				HSceneObject child = mSceneObject->getChild(i);
				children[i] = child;

				child->setParent(HSceneObject());
			}
		}

		bool isInstantiated = !mSceneObject->hasFlag(SOF_DontInstantiate);
		mSceneObject->_setFlags(SOF_DontInstantiate);

		MemorySerializer serializer;
		mSerializedObject = serializer.encode(mSceneObject.get(), mSerializedObjectSize);

		if (isInstantiated)
			mSceneObject->_unsetFlags(SOF_DontInstantiate);

		mSceneObjectProxy = EditorUtility::createProxy(mSceneObject);

		HSceneObject parent = sceneObject->getParent();
		if (parent != nullptr)
			mSerializedObjectParentId = parent->getInstanceId();

		if (!mRecordHierarchy)
		{
			for (UINT32 i = 0; i < numChildren; i++)
				children[i]->setParent(sceneObject->getHandle());

			bs_stack_delete(children, numChildren);
		}
	}

	SerializedSceneObject::~SerializedSceneObject()
	{
		if (mSerializedObject != nullptr)
		{
			bs_free(mSerializedObject);
			mSerializedObject = nullptr;
		}
	}

	void SerializedSceneObject::restore()
	{
		HSceneObject parent;
		if (mSerializedObjectParentId != 0)
			parent = static_object_cast<SceneObject>(GameObjectManager::instance().getObject(mSerializedObjectParentId));

		HSceneObject* children = nullptr;
		UINT32 numChildren = 0;
		if (!mSceneObject.isDestroyed())
		{
			numChildren = mSceneObject->getNumChildren();
			if (!mRecordHierarchy)
			{
				children = bs_stack_new<HSceneObject>(numChildren);
				for (UINT32 i = 0; i < numChildren; i++)
				{
					HSceneObject child = mSceneObject->getChild(i);
					children[i] = child;

					child->setParent(HSceneObject());
				}
			}

			mSceneObject->destroy(true);
		}

		CoreSerializationContext serzContext;
		serzContext.goState = bs_shared_ptr_new<GameObjectDeserializationState>(GODM_RestoreExternal | GODM_UseNewIds);

		MemorySerializer serializer;
		SPtr<SceneObject> restored = std::static_pointer_cast<SceneObject>(
			serializer.decode(mSerializedObject, mSerializedObjectSize, &serzContext));

		EditorUtility::restoreIds(restored->getHandle(), mSceneObjectProxy);
		restored->setParent(parent);

		if (children)
		{
			for (UINT32 i = 0; i < numChildren; i++)
				children[i]->setParent(restored->getHandle());

			bs_stack_delete(children, numChildren);
		}

		restored->_instantiate();
	}
}
