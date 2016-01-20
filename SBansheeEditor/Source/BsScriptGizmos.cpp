//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsScriptGizmos.h"
#include "BsScriptMeta.h"
#include "BsMonoClass.h"
#include "BsScriptSpriteTexture.h"
#include "BsGizmoManager.h"
#include "BsMonoUtil.h"
#include "BsScriptFont.h"

namespace BansheeEngine
{
	void ScriptGizmos::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_SetColor", &ScriptGizmos::internal_SetColor);
		metaData.scriptClass->addInternalCall("Internal_GetColor", &ScriptGizmos::internal_GetColor);
		metaData.scriptClass->addInternalCall("Internal_SetTransform", &ScriptGizmos::internal_SetTransform);
		metaData.scriptClass->addInternalCall("Internal_GetTransform", &ScriptGizmos::internal_GetTransform);
		metaData.scriptClass->addInternalCall("Internal_DrawCube", &ScriptGizmos::internal_DrawCube);
		metaData.scriptClass->addInternalCall("Internal_DrawSphere", &ScriptGizmos::internal_DrawSphere);
		metaData.scriptClass->addInternalCall("Internal_DrawWireCube", &ScriptGizmos::internal_DrawWireCube);
		metaData.scriptClass->addInternalCall("Internal_DrawWireSphere", &ScriptGizmos::internal_DrawWireSphere);
		metaData.scriptClass->addInternalCall("Internal_DrawWireDisc", &ScriptGizmos::internal_DrawWireDisc);
		metaData.scriptClass->addInternalCall("Internal_DrawWireArc", &ScriptGizmos::internal_DrawWireArc);
		metaData.scriptClass->addInternalCall("Internal_DrawLine", &ScriptGizmos::internal_DrawLine);
		metaData.scriptClass->addInternalCall("Internal_DrawFrustum", &ScriptGizmos::internal_DrawFrustum);
		metaData.scriptClass->addInternalCall("Internal_DrawIcon", &ScriptGizmos::internal_DrawIcon);
		metaData.scriptClass->addInternalCall("Internal_DrawText", &ScriptGizmos::internal_DrawText);
	}

	void ScriptGizmos::internal_SetColor(Color* color)
	{
		GizmoManager::instance().setColor(*color);
	}

	void ScriptGizmos::internal_GetColor(Color* color)
	{
		*color = GizmoManager::instance().getColor();
	}

	void ScriptGizmos::internal_SetTransform(Matrix4* transform)
	{
		GizmoManager::instance().setTransform(*transform);
	}

	void ScriptGizmos::internal_GetTransform(Matrix4* transform)
	{
		*transform = GizmoManager::instance().getTransform();
	}

	void ScriptGizmos::internal_DrawCube(Vector3* position, Vector3* extents)
	{
		GizmoManager::instance().drawCube(*position, *extents);
	}

	void ScriptGizmos::internal_DrawSphere(Vector3* position, float radius)
	{
		GizmoManager::instance().drawSphere(*position, radius);
	}

	void ScriptGizmos::internal_DrawWireCube(Vector3* position, Vector3* extents)
	{
		GizmoManager::instance().drawWireCube(*position, *extents);
	}

	void ScriptGizmos::internal_DrawWireSphere(Vector3* position, float radius)
	{
		GizmoManager::instance().drawWireSphere(*position, radius);
	}

	void ScriptGizmos::internal_DrawLine(Vector3* start, Vector3* end)
	{
		GizmoManager::instance().drawLine(*start, *end);
	}

	void ScriptGizmos::internal_DrawWireDisc(Vector3* position, Vector3* normal, float radius)
	{
		GizmoManager::instance().drawWireDisc(*position, *normal, radius);
	}

	void ScriptGizmos::internal_DrawWireArc(Vector3* position, Vector3* normal, float radius, float startAngle, 
		float amountAngle)
	{
		GizmoManager::instance().drawWireArc(*position, *normal, radius, Degree(startAngle), Degree(amountAngle));
	}

	void ScriptGizmos::internal_DrawFrustum(Vector3* position, float aspect, Degree* FOV, float near, float far)
	{
		GizmoManager::instance().drawFrustum(*position, aspect, *FOV, near, far);
	}

	void ScriptGizmos::internal_DrawIcon(Vector3* position, MonoObject* image, bool fixedScale)
	{
		HSpriteTexture nativeTexture;
		if (image != nullptr)
			nativeTexture = ScriptSpriteTexture::toNative(image)->getHandle();

		GizmoManager::instance().drawIcon(*position, nativeTexture, fixedScale);
	}

	void ScriptGizmos::internal_DrawText(Vector3* position, MonoString* text, ScriptFont* font, int size)
	{
		WString nativeText = MonoUtil::monoToWString(text);

		HFont fontHandle;
		if (font != nullptr)
			fontHandle = font->getHandle();

		GizmoManager::instance().drawText(*position, nativeText, fontHandle, size);
	}
}