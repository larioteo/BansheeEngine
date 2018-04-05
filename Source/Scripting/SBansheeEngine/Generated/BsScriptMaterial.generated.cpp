#include "BsScriptMaterial.generated.h"
#include "BsMonoMethod.h"
#include "BsMonoClass.h"
#include "BsMonoUtil.h"
#include "../../../bsf/Source/Foundation/bsfCore/Material/BsMaterial.h"
#include "BsScriptResourceManager.h"
#include "BsScriptShader.generated.h"
#include "Wrappers/BsScriptVector.h"
#include "Wrappers/BsScriptColor.h"
#include "BsScriptMaterial.generated.h"
#include "Wrappers/BsScriptVector.h"
#include "Wrappers/BsScriptVector.h"
#include "BsScriptTexture.generated.h"
#include "../../SBansheeEngine/Extensions/BsMaterialEx.h"

namespace bs
{
	ScriptMaterial::ScriptMaterial(MonoObject* managedInstance, const ResourceHandle<Material>& value)
		:TScriptResource(managedInstance, value)
	{
	}

	void ScriptMaterial::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_setShader", (void*)&ScriptMaterial::Internal_setShader);
		metaData.scriptClass->addInternalCall("Internal_clone", (void*)&ScriptMaterial::Internal_clone);
		metaData.scriptClass->addInternalCall("Internal_getShader", (void*)&ScriptMaterial::Internal_getShader);
		metaData.scriptClass->addInternalCall("Internal_setFloat", (void*)&ScriptMaterial::Internal_setFloat);
		metaData.scriptClass->addInternalCall("Internal_setColor", (void*)&ScriptMaterial::Internal_setColor);
		metaData.scriptClass->addInternalCall("Internal_setVec2", (void*)&ScriptMaterial::Internal_setVec2);
		metaData.scriptClass->addInternalCall("Internal_setVec3", (void*)&ScriptMaterial::Internal_setVec3);
		metaData.scriptClass->addInternalCall("Internal_setVec4", (void*)&ScriptMaterial::Internal_setVec4);
		metaData.scriptClass->addInternalCall("Internal_setMat3", (void*)&ScriptMaterial::Internal_setMat3);
		metaData.scriptClass->addInternalCall("Internal_setMat4", (void*)&ScriptMaterial::Internal_setMat4);
		metaData.scriptClass->addInternalCall("Internal_getFloat", (void*)&ScriptMaterial::Internal_getFloat);
		metaData.scriptClass->addInternalCall("Internal_getColor", (void*)&ScriptMaterial::Internal_getColor);
		metaData.scriptClass->addInternalCall("Internal_getVec2", (void*)&ScriptMaterial::Internal_getVec2);
		metaData.scriptClass->addInternalCall("Internal_getVec3", (void*)&ScriptMaterial::Internal_getVec3);
		metaData.scriptClass->addInternalCall("Internal_getVec4", (void*)&ScriptMaterial::Internal_getVec4);
		metaData.scriptClass->addInternalCall("Internal_getMat3", (void*)&ScriptMaterial::Internal_getMat3);
		metaData.scriptClass->addInternalCall("Internal_getMat4", (void*)&ScriptMaterial::Internal_getMat4);
		metaData.scriptClass->addInternalCall("Internal_create", (void*)&ScriptMaterial::Internal_create);
		metaData.scriptClass->addInternalCall("Internal_create0", (void*)&ScriptMaterial::Internal_create0);
		metaData.scriptClass->addInternalCall("Internal_setTexture", (void*)&ScriptMaterial::Internal_setTexture);
		metaData.scriptClass->addInternalCall("Internal_getTexture", (void*)&ScriptMaterial::Internal_getTexture);

	}

	 MonoObject*ScriptMaterial::createInstance()
	{
		bool dummy = false;
		void* ctorParams[1] = { &dummy };

		return metaData.scriptClass->createInstance("bool", ctorParams);
	}
	void ScriptMaterial::Internal_setShader(ScriptMaterial* thisPtr, MonoObject* shader)
	{
		ResourceHandle<Shader> tmpshader;
		ScriptShader* scriptshader;
		scriptshader = ScriptShader::toNative(shader);
		if(scriptshader != nullptr)
			tmpshader = scriptshader->getHandle();
		thisPtr->getHandle()->setShader(tmpshader);
	}

	MonoObject* ScriptMaterial::Internal_clone(ScriptMaterial* thisPtr)
	{
		ResourceHandle<Material> tmp__output;
		tmp__output = thisPtr->getHandle()->clone();

		MonoObject* __output;
		ScriptResourceBase* script__output;
		script__output = ScriptResourceManager::instance().getScriptResource(tmp__output, true);
		if(script__output != nullptr)
			__output = script__output->getManagedInstance();
		else
			__output = nullptr;

		return __output;
	}

	MonoObject* ScriptMaterial::Internal_getShader(ScriptMaterial* thisPtr)
	{
		ResourceHandle<Shader> tmp__output;
		tmp__output = thisPtr->getHandle()->getShader();

		MonoObject* __output;
		ScriptResourceBase* script__output;
		script__output = ScriptResourceManager::instance().getScriptResource(tmp__output, true);
		if(script__output != nullptr)
			__output = script__output->getManagedInstance();
		else
			__output = nullptr;

		return __output;
	}

	void ScriptMaterial::Internal_setFloat(ScriptMaterial* thisPtr, MonoString* name, float value, uint32_t arrayIdx)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		thisPtr->getHandle()->setFloat(tmpname, value, arrayIdx);
	}

	void ScriptMaterial::Internal_setColor(ScriptMaterial* thisPtr, MonoString* name, Color* value, uint32_t arrayIdx)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		thisPtr->getHandle()->setColor(tmpname, *value, arrayIdx);
	}

	void ScriptMaterial::Internal_setVec2(ScriptMaterial* thisPtr, MonoString* name, Vector2* value, uint32_t arrayIdx)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		thisPtr->getHandle()->setVec2(tmpname, *value, arrayIdx);
	}

	void ScriptMaterial::Internal_setVec3(ScriptMaterial* thisPtr, MonoString* name, Vector3* value, uint32_t arrayIdx)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		thisPtr->getHandle()->setVec3(tmpname, *value, arrayIdx);
	}

	void ScriptMaterial::Internal_setVec4(ScriptMaterial* thisPtr, MonoString* name, Vector4* value, uint32_t arrayIdx)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		thisPtr->getHandle()->setVec4(tmpname, *value, arrayIdx);
	}

	void ScriptMaterial::Internal_setMat3(ScriptMaterial* thisPtr, MonoString* name, Matrix3* value, uint32_t arrayIdx)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		thisPtr->getHandle()->setMat3(tmpname, *value, arrayIdx);
	}

	void ScriptMaterial::Internal_setMat4(ScriptMaterial* thisPtr, MonoString* name, Matrix4* value, uint32_t arrayIdx)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		thisPtr->getHandle()->setMat4(tmpname, *value, arrayIdx);
	}

	float ScriptMaterial::Internal_getFloat(ScriptMaterial* thisPtr, MonoString* name, uint32_t arrayIdx)
	{
		float tmp__output;
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		tmp__output = thisPtr->getHandle()->getFloat(tmpname, arrayIdx);

		float __output;
		__output = tmp__output;

		return __output;
	}

	void ScriptMaterial::Internal_getColor(ScriptMaterial* thisPtr, MonoString* name, uint32_t arrayIdx, Color* __output)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		Color tmp__output;
		tmp__output = thisPtr->getHandle()->getColor(tmpname, arrayIdx);

		*__output = tmp__output;
	}

	void ScriptMaterial::Internal_getVec2(ScriptMaterial* thisPtr, MonoString* name, uint32_t arrayIdx, Vector2* __output)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		Vector2 tmp__output;
		tmp__output = thisPtr->getHandle()->getVec2(tmpname, arrayIdx);

		*__output = tmp__output;
	}

	void ScriptMaterial::Internal_getVec3(ScriptMaterial* thisPtr, MonoString* name, uint32_t arrayIdx, Vector3* __output)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		Vector3 tmp__output;
		tmp__output = thisPtr->getHandle()->getVec3(tmpname, arrayIdx);

		*__output = tmp__output;
	}

	void ScriptMaterial::Internal_getVec4(ScriptMaterial* thisPtr, MonoString* name, uint32_t arrayIdx, Vector4* __output)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		Vector4 tmp__output;
		tmp__output = thisPtr->getHandle()->getVec4(tmpname, arrayIdx);

		*__output = tmp__output;
	}

	void ScriptMaterial::Internal_getMat3(ScriptMaterial* thisPtr, MonoString* name, uint32_t arrayIdx, Matrix3* __output)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		Matrix3 tmp__output;
		tmp__output = thisPtr->getHandle()->getMat3(tmpname, arrayIdx);

		*__output = tmp__output;
	}

	void ScriptMaterial::Internal_getMat4(ScriptMaterial* thisPtr, MonoString* name, uint32_t arrayIdx, Matrix4* __output)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		Matrix4 tmp__output;
		tmp__output = thisPtr->getHandle()->getMat4(tmpname, arrayIdx);

		*__output = tmp__output;
	}

	void ScriptMaterial::Internal_create(MonoObject* managedInstance)
	{
		ResourceHandle<Material> instance = Material::create();
		ScriptResourceManager::instance().createBuiltinScriptResource(instance, managedInstance);
	}

	void ScriptMaterial::Internal_create0(MonoObject* managedInstance, MonoObject* shader)
	{
		ResourceHandle<Shader> tmpshader;
		ScriptShader* scriptshader;
		scriptshader = ScriptShader::toNative(shader);
		if(scriptshader != nullptr)
			tmpshader = scriptshader->getHandle();
		ResourceHandle<Material> instance = Material::create(tmpshader);
		ScriptResourceManager::instance().createBuiltinScriptResource(instance, managedInstance);
	}

	void ScriptMaterial::Internal_setTexture(ScriptMaterial* thisPtr, MonoString* name, MonoObject* value, uint32_t mipLevel, uint32_t numMipLevels, uint32_t arraySlice, uint32_t numArraySlices)
	{
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		ResourceHandle<Texture> tmpvalue;
		ScriptTexture* scriptvalue;
		scriptvalue = ScriptTexture::toNative(value);
		if(scriptvalue != nullptr)
			tmpvalue = scriptvalue->getHandle();
		MaterialEx::setTexture(thisPtr->getHandle(), tmpname, tmpvalue, mipLevel, numMipLevels, arraySlice, numArraySlices);
	}

	MonoObject* ScriptMaterial::Internal_getTexture(ScriptMaterial* thisPtr, MonoString* name)
	{
		ResourceHandle<Texture> tmp__output;
		String tmpname;
		tmpname = MonoUtil::monoToString(name);
		tmp__output = MaterialEx::getTexture(thisPtr->getHandle(), tmpname);

		MonoObject* __output;
		ScriptResourceBase* script__output;
		script__output = ScriptResourceManager::instance().getScriptResource(tmp__output, true);
		if(script__output != nullptr)
			__output = script__output->getManagedInstance();
		else
			__output = nullptr;

		return __output;
	}
}
