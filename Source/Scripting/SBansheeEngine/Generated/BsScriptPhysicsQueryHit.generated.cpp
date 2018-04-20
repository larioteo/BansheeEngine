#include "BsScriptPhysicsQueryHit.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "BsScriptGameObjectManager.h"
#include "Wrappers/BsScriptVector.h"
#include "Wrappers/BsScriptVector.h"
#include "Wrappers/BsScriptVector.h"
#include "Wrappers/BsScriptVector.h"
#include "BsScriptCCollider.generated.h"

namespace bs
{
	ScriptPhysicsQueryHit::ScriptPhysicsQueryHit(MonoObject* managedInstance)
		:ScriptObject(managedInstance)
	{ }

	void ScriptPhysicsQueryHit::initRuntimeData()
	{ }

	MonoObject*ScriptPhysicsQueryHit::box(const __PhysicsQueryHitInterop& value)
	{
		return MonoUtil::box(metaData.scriptClass->_getInternalClass(), (void*)&value);
	}

	__PhysicsQueryHitInterop ScriptPhysicsQueryHit::unbox(MonoObject* value)
	{
		return *(__PhysicsQueryHitInterop*)MonoUtil::unbox(value);
	}

	PhysicsQueryHit ScriptPhysicsQueryHit::fromInterop(const __PhysicsQueryHitInterop& value)
	{
		PhysicsQueryHit output;
		output.point = value.point;
		output.normal = value.normal;
		output.uv = value.uv;
		output.distance = value.distance;
		output.triangleIdx = value.triangleIdx;
		GameObjectHandle<CCollider> tmpcollider;
		ScriptCColliderBase* scriptcollider;
		scriptcollider = (ScriptCColliderBase*)ScriptCCollider::toNative(value.collider);
		if(scriptcollider != nullptr)
			tmpcollider = static_object_cast<CCollider>(scriptcollider->getComponent());
		output.collider = tmpcollider;

		return output;
	}

	__PhysicsQueryHitInterop ScriptPhysicsQueryHit::toInterop(const PhysicsQueryHit& value)
	{
		__PhysicsQueryHitInterop output;
		output.point = value.point;
		output.normal = value.normal;
		output.uv = value.uv;
		output.distance = value.distance;
		output.triangleIdx = value.triangleIdx;
		ScriptComponentBase* scriptcollider = nullptr;
		if(value.collider)
				scriptcollider = ScriptGameObjectManager::instance().getBuiltinScriptComponent(value.collider);
		MonoObject* tmpcollider;
		if(scriptcollider != nullptr)
			tmpcollider = scriptcollider->getManagedInstance();
		else
			tmpcollider = nullptr;
		output.collider = tmpcollider;

		return output;
	}

}
