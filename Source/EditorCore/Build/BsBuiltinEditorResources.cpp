//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Utility/BsBuiltinEditorResources.h"
#include "Resources/BsBuiltinResources.h"
#include "GUI/BsGUIElementStyle.h"
#include "GUI/BsGUILabel.h"
#include "GUI/BsGUITexture.h"
#include "GUI/BsGUIButton.h"
#include "GUI/BsGUIInputBox.h"
#include "GUI/BsGUIToggle.h"
#include "GUI/BsGUIColor.h"
#include "2D/BsTextSprite.h"
#include "2D/BsSpriteTexture.h"
#include "GUI/BsGUITreeViewEditBox.h"
#include "GUI/BsGUIIntField.h"
#include "GUI/BsGUIFloatField.h"
#include "GUI/BsGUIColorField.h"
#include "GUI/BsGUITextField.h"
#include "GUI/BsGUIToggleField.h"
#include "GUI/BsGUIVector2Field.h"
#include "GUI/BsGUIVector3Field.h"
#include "GUI/BsGUIVector4Field.h"
#include "GUI/BsGUIListBoxField.h"
#include "GUI/BsGUISliderField.h"
#include "GUI/BsGUIProgressBar.h"
#include "GUI/BsGUISlider.h"
#include "GUI/BsGUIDropDownContent.h"
#include "GUI/BsGUIStatusBar.h"
#include "GUI/BsGUIMenuBar.h"
#include "GUI/BsGUIListBox.h"
#include "GUI/BsGUIScrollBar.h"
#include "CoreThread/BsCoreThread.h"
#include "Text/BsFont.h"
#include "Image/BsTexture.h"
#include "Material/BsShader.h"
#include "Material/BsMaterial.h"
#include "Resources/BsResources.h"
#include "FileSystem/BsFileSystem.h"
#include "Resources/BsResourceManifest.h"
#include "FileSystem/BsDataStream.h"
#include "GUI/BsGUITooltip.h"
#include "Resources/BsBuiltinResourcesHelper.h"
#include "Importer/BsImporter.h"
#include "Importer/BsTextureImportOptions.h"
#include "Serialization/BsFileSerializer.h"
#include "BsEditorApplication.h"

using json = nlohmann::json;

namespace bs
{
	const String BuiltinEditorResources::ObjectFieldStyleName = "GUIObjectField";
	const String BuiltinEditorResources::ObjectFieldLabelStyleName = "EditorFieldLabel";
	const String BuiltinEditorResources::ObjectFieldDropBtnStyleName = "DropButton";
	const String BuiltinEditorResources::ObjectFieldClearBtnStyleName = "ObjectClearButton";

	const String BuiltinEditorResources::TextureFieldStyleName = "GUITextureField";
	const String BuiltinEditorResources::TextureFieldLabelStyleName = "TextureFieldLabel";
	const String BuiltinEditorResources::TextureFieldDropStyleName = "TextureDrop";
	const String BuiltinEditorResources::TextureFieldClearBtnStyleName = "TextureClearButton";

	const String BuiltinEditorResources::DefaultFontFilename = "arial.ttf";
	const String BuiltinEditorResources::DefaultAAFontFilename = "arialAA.ttf";
	const UINT32 BuiltinEditorResources::DefaultFontSize = 8;
	const UINT32 BuiltinEditorResources::TitleFontSize = 16;

	const Color BuiltinEditorResources::TextNormalColor = Color(0.7f, 0.7f, 0.7f);
	const Color BuiltinEditorResources::TextActiveColor = Color(0.0f, 0.0f, 0.0f);

	const String BuiltinEditorResources::GUISkinFile = "GUISkin";

	const char* BuiltinEditorResources::ShaderFolder = "Shaders/";
	const char* BuiltinEditorResources::SkinFolder = "Skin/";
	const char* BuiltinEditorResources::IconFolder = "Icons/";
	const char* BuiltinEditorResources::ShaderIncludeFolder = "Shaders/Includes/";
	const char* BuiltinEditorResources::SpriteSubFolder = "Sprites/";

	const String BuiltinEditorResources::FolderIconTex = u8"FolderIcon.psd";
	const String BuiltinEditorResources::MeshIconTex = u8"MeshIcon.psd";
	const String BuiltinEditorResources::TextureIconTex = u8"TextureIcon.psd";
	const String BuiltinEditorResources::FontIconTex = u8"FontIcon.psd";
	const String BuiltinEditorResources::PlainTextIconTex = u8"TextIcon.psd";
	const String BuiltinEditorResources::ScriptCodeIconTex = u8"CSharpIcon.psd";
	const String BuiltinEditorResources::ShaderIconTex = u8"ShaderIcon.psd";
	const String BuiltinEditorResources::ShaderIncludeIconTex = u8"ShaderIncludeIcon.psd";
	const String BuiltinEditorResources::MaterialIconTex = u8"MaterialIcon.psd";
	const String BuiltinEditorResources::SpriteTextureIconTex = u8"SpriteIcon.psd";
	const String BuiltinEditorResources::PrefabIconTex = u8"PrefabIcon.psd";
	const String BuiltinEditorResources::GUISkinIconTex = u8"GUISkinIcon.psd";
	const String BuiltinEditorResources::PhysicsMaterialIconTex = u8"PhysicsMaterialIcon.psd";
	const String BuiltinEditorResources::PhysicsMeshIconTex = u8"PhysicsMeshIcon.psd";
	const String BuiltinEditorResources::AudioClipIconTex = u8"AudioClipIcon.psd";
	const String BuiltinEditorResources::AnimationClipIconTex = u8"AnimationClipIcon.psd";

	const char* BuiltinEditorResources::SplashScreenName = u8"SplashScreen.png";
	const String BuiltinEditorResources::XButtonNormalTex = u8"XBtnNormal.png";

	/************************************************************************/
	/* 									SHADERS                      		*/
	/************************************************************************/

	const String BuiltinEditorResources::ShaderDockOverlayFile = u8"DockDropOverlay.bsl";
	const String BuiltinEditorResources::ShaderSceneGridFile = u8"SceneGrid.bsl";
	const String BuiltinEditorResources::ShaderPickingCullNoneFile = u8"PickingCullNone.bsl";
	const String BuiltinEditorResources::ShaderPickingCullCWFile = u8"PickingCullCW.bsl";
	const String BuiltinEditorResources::ShaderPickingCullCCWFile = u8"PickingCullCCW.bsl";
	const String BuiltinEditorResources::ShaderPickingAlphaCullNoneFile = u8"PickingAlphaCullNone.bsl";
	const String BuiltinEditorResources::ShaderPickingAlphaCullCWFile = u8"PickingAlphaCullCW.bsl";
	const String BuiltinEditorResources::ShaderPickingAlphaCullCCWFile = u8"PickingAlphaCullCCW.bsl";
	const String BuiltinEditorResources::ShaderLineGizmoFile = u8"LineGizmo.bsl";
	const String BuiltinEditorResources::ShaderWireGizmoFile = u8"WireGizmo.bsl";
	const String BuiltinEditorResources::ShaderSolidGizmoFile = u8"SolidGizmo.bsl";
	const String BuiltinEditorResources::ShaderLineHandleFile = u8"LineHandle.bsl";
	const String BuiltinEditorResources::ShaderSolidHandleFile = u8"SolidHandle.bsl";
	const String BuiltinEditorResources::ShaderHandleClearAlphaFile = u8"ClearHandleAlpha.bsl";
	const String BuiltinEditorResources::ShaderIconGizmoFile = u8"IconGizmo.bsl";
	const String BuiltinEditorResources::ShaderGizmoPickingFile = u8"GizmoPicking.bsl";
	const String BuiltinEditorResources::ShaderGizmoPickingAlphaFile = u8"GizmoPickingAlpha.bsl";
	const String BuiltinEditorResources::ShaderTextGizmoFile = u8"TextGizmo.bsl";
	const String BuiltinEditorResources::ShaderSelectionFile = u8"Selection.bsl";

	/************************************************************************/
	/* 								OTHER							  		*/
	/************************************************************************/
	const String BuiltinEditorResources::EmptyShaderCodeFile = u8"EmptyShaderText.txt";
	const String BuiltinEditorResources::EmptyCSScriptCodeFile = u8"EmptyCSScriptText.txt";

	BuiltinEditorResources::BuiltinEditorResources()
	{
		// Set up paths
		BuiltinRawDataFolder = gEditorApplication().getDataPath() + "Raw/";
		EditorRawSkinFolder = BuiltinRawDataFolder + SkinFolder;
		EditorRawIconsFolder = BuiltinRawDataFolder + IconFolder;
		EditorRawShaderFolder = BuiltinRawDataFolder + ShaderFolder;
		EditorRawShaderIncludeFolder = BuiltinRawDataFolder + ShaderIncludeFolder;

		BuiltinDataFolder = gEditorApplication().getDataPath();
		EditorSkinFolder = BuiltinDataFolder + SkinFolder;
		EditorSkinSpritesFolder = EditorSkinFolder + SpriteSubFolder;
		EditorIconFolder = BuiltinDataFolder + IconFolder;
		EditorIconSpritesFolder = EditorIconFolder + SpriteSubFolder;
		EditorShaderFolder = BuiltinDataFolder + ShaderFolder;
		EditorShaderIncludeFolder = BuiltinDataFolder + ShaderIncludeFolder;

		ResourceManifestPath = BuiltinDataFolder + "ResourceManifest.asset";

		// Update from raw assets if needed
		if (FileSystem::exists(BuiltinRawDataFolder))
		{
			time_t lastUpdateTime;
			UINT32 modifications = BuiltinResourcesHelper::checkForModifications(BuiltinRawDataFolder,
				BuiltinDataFolder + "Timestamp.asset", lastUpdateTime);

			// Check if manifest needs to be rebuilt
			if (modifications == 0 && !FileSystem::exists(ResourceManifestPath))
				modifications = 1;

			if (modifications > 0)
			{
				bool forceReimport = modifications == 2;

				SPtr<ResourceManifest> oldResourceManifest;
				if (!forceReimport && FileSystem::exists(ResourceManifestPath))
				{
					oldResourceManifest = ResourceManifest::load(ResourceManifestPath, BuiltinDataFolder);
					if (oldResourceManifest != nullptr)
						gResources().registerResourceManifest(oldResourceManifest);
				}

				if (oldResourceManifest)
					mResourceManifest = oldResourceManifest;
				else
				{
					mResourceManifest = ResourceManifest::create("BuiltinResources");
					gResources().registerResourceManifest(mResourceManifest);
				}

				preprocess(modifications == 2, lastUpdateTime);
				BuiltinResourcesHelper::writeTimestamp(BuiltinDataFolder + "Timestamp.asset");

				ResourceManifest::save(mResourceManifest, ResourceManifestPath, BuiltinDataFolder);
			}
		}

		// Load manifest
		if (mResourceManifest == nullptr)
		{
			if (FileSystem::exists(ResourceManifestPath))
				mResourceManifest = ResourceManifest::load(ResourceManifestPath, BuiltinDataFolder);

			if (mResourceManifest == nullptr)
				mResourceManifest = ResourceManifest::create("BuiltinResources");

			gResources().registerResourceManifest(mResourceManifest);
		}

		// Load basic resources
		mShaderDockOverlay = getShader(ShaderDockOverlayFile);
		mShaderSceneGrid = getShader(ShaderSceneGridFile);
		mShaderPicking[(int)CULL_NONE] = getShader(ShaderPickingCullNoneFile);
		mShaderPicking[(int)CULL_CLOCKWISE] = getShader(ShaderPickingCullCWFile);
		mShaderPicking[(int)CULL_COUNTERCLOCKWISE] = getShader(ShaderPickingCullCCWFile);
		mShaderPickingAlpha[(int)CULL_NONE] = getShader(ShaderPickingAlphaCullNoneFile);
		mShaderPickingAlpha[(int)CULL_CLOCKWISE] = getShader(ShaderPickingAlphaCullCWFile);
		mShaderPickingAlpha[(int)CULL_COUNTERCLOCKWISE] = getShader(ShaderPickingAlphaCullCCWFile);
		mShaderGizmoSolid = getShader(ShaderSolidGizmoFile);
		mShaderGizmoLine = getShader(ShaderLineGizmoFile);
		mShaderGizmoWire = getShader(ShaderWireGizmoFile);
		mShaderGizmoIcon = getShader(ShaderIconGizmoFile);
		mShaderGizmoPicking = getShader(ShaderGizmoPickingFile);
		mShaderGizmoAlphaPicking = getShader(ShaderGizmoPickingAlphaFile);
		mShaderGizmoText = getShader(ShaderTextGizmoFile);
		mShaderHandleSolid = getShader(ShaderSolidHandleFile);
		mShaderHandleClearAlpha = getShader(ShaderHandleClearAlphaFile);
		mShaderHandleLine = getShader(ShaderLineHandleFile);
		mShaderSelection = getShader(ShaderSelectionFile);

		mDefaultFont = gResources().load<Font>(BuiltinDataFolder + (DefaultFontFilename + ".asset"));
		mDefaultAAFont = gResources().load<Font>(BuiltinDataFolder + (DefaultAAFontFilename + ".asset"));
		mSkin = gResources().load<GUISkin>(BuiltinDataFolder + (GUISkinFile + ".asset"));
	}

	void BuiltinEditorResources::preprocess(bool forceImport, time_t lastUpdateTime)
	{
		Resources::instance().unloadAllUnused();

		Path dataListsFilePath = BuiltinRawDataFolder + DATA_LIST_JSON;
		SPtr<DataStream> dataListStream = FileSystem::openFile(dataListsFilePath);

		json dataListJSON = json::parse(dataListStream->getAsString().c_str());

		json skinJSON = dataListJSON["Skin"];
		json iconsJSON = dataListJSON["Icons"];
		json includesJSON = dataListJSON["Includes"];
		json shadersJSON = dataListJSON["Shaders"];

		// Update DataList.json if needed
		bool updatedDataLists = false;
		updatedDataLists |= BuiltinResourcesHelper::updateJSON(
			EditorRawIconsFolder,
			BuiltinResourcesHelper::AssetType::Sprite,
			iconsJSON);

		updatedDataLists |= BuiltinResourcesHelper::updateJSON(
			EditorRawShaderIncludeFolder,
			BuiltinResourcesHelper::AssetType::Normal,
			includesJSON);

		updatedDataLists |= BuiltinResourcesHelper::updateJSON(
			EditorRawShaderFolder,
			BuiltinResourcesHelper::AssetType::Normal,
			shadersJSON);

		updatedDataLists |= BuiltinResourcesHelper::updateJSON(
			EditorRawSkinFolder,
			BuiltinResourcesHelper::AssetType::Sprite,
			skinJSON);

		dataListStream->close();

		if (updatedDataLists)
		{
			FileSystem::remove(dataListsFilePath);

			dataListJSON["Skin"] = skinJSON;
			dataListJSON["Icons"] = iconsJSON;
			dataListJSON["Includes"] = includesJSON;
			dataListJSON["Shaders"] = shadersJSON;

			String jsonString = dataListJSON.dump(4).c_str();
			dataListStream = FileSystem::createAndOpenFile(dataListsFilePath);
			dataListStream->writeString(jsonString);
			dataListStream->close();
		}

		// If forcing import, clear all data folders since everything will be recreated anyway
		Path shaderDependenciesFile = BuiltinDataFolder + "ShaderDependencies.json";
		if(forceImport)
		{
			FileSystem::remove(EditorIconFolder);
			FileSystem::remove(EditorShaderIncludeFolder);
			FileSystem::remove(EditorShaderFolder);
			FileSystem::remove(EditorSkinFolder);
			
			FileSystem::remove(shaderDependenciesFile);
		}

		// Read shader dependencies JSON
		json shaderDependenciesJSON;
		if(FileSystem::exists(shaderDependenciesFile))
		{
			SPtr<DataStream> stream = FileSystem::openFile(shaderDependenciesFile);
			shaderDependenciesJSON = json::parse(stream->getAsString().c_str());
			stream->close();
		}

		// Import icons
		{
			BuiltinResourcesHelper::updateManifest(
				EditorIconFolder,
				iconsJSON,
				mResourceManifest,
				BuiltinResourcesHelper::AssetType::Sprite);

			Vector<bool> importFlags = BuiltinResourcesHelper::generateImportFlags(
				iconsJSON,
				EditorRawIconsFolder,
				lastUpdateTime,
				forceImport);

			BuiltinResourcesHelper::importAssets(
				iconsJSON,
				importFlags,
				EditorRawIconsFolder,
				EditorIconFolder,
				mResourceManifest,
				BuiltinResourcesHelper::AssetType::Sprite);
		}

		// Import shaders
		{
			BuiltinResourcesHelper::updateManifest(
				EditorShaderIncludeFolder,
				includesJSON,
				mResourceManifest,
				BuiltinResourcesHelper::AssetType::Normal);

			BuiltinResourcesHelper::updateManifest(
				EditorShaderFolder,
				shadersJSON,
				mResourceManifest,
				BuiltinResourcesHelper::AssetType::Normal);

			Vector<bool> includeImportFlags = BuiltinResourcesHelper::generateImportFlags(
				includesJSON,
				EditorRawShaderIncludeFolder,
				lastUpdateTime,
				forceImport);

			Vector<bool> shaderImportFlags = BuiltinResourcesHelper::generateImportFlags(
				shadersJSON,
				EditorRawShaderFolder,
				lastUpdateTime,
				forceImport,
				&shaderDependenciesJSON,
				EditorRawShaderIncludeFolder);

			// Hidden dependency: Includes must be imported before shaders, but import flags for shaders must be generated
			// before includes are imported, since the process checks if imports changed
			BuiltinResourcesHelper::importAssets(
				includesJSON,
				includeImportFlags,
				EditorRawShaderIncludeFolder,
				EditorShaderIncludeFolder,
				mResourceManifest,
				BuiltinResourcesHelper::AssetType::Normal);

			BuiltinResourcesHelper::importAssets(
				shadersJSON,
				shaderImportFlags,
				EditorRawShaderFolder,
				EditorShaderFolder,
				mResourceManifest,
				BuiltinResourcesHelper::AssetType::Normal,
				&shaderDependenciesJSON);
		}

		// Import GUI sprites
		{
			BuiltinResourcesHelper::updateManifest(
				EditorSkinFolder,
				skinJSON,
				mResourceManifest,
				BuiltinResourcesHelper::AssetType::Sprite);

			Vector<bool> includeImportFlags = BuiltinResourcesHelper::generateImportFlags(
				skinJSON,
				EditorRawSkinFolder,
				lastUpdateTime,
				forceImport);

			BuiltinResourcesHelper::importAssets(
				skinJSON,
				includeImportFlags,
				EditorRawSkinFolder,
				EditorSkinFolder,
				mResourceManifest,
				BuiltinResourcesHelper::AssetType::Sprite);
		}

		// Update shader dependencies JSON
		{
			String jsonString = shaderDependenciesJSON.dump(4).c_str();

			dataListStream = FileSystem::createAndOpenFile(shaderDependenciesFile);
			dataListStream->writeString(jsonString);
			dataListStream->close();
		}

		// Import fonts
		BuiltinResourcesHelper::importFont(
			BuiltinRawDataFolder + DefaultFontFilename,
			DefaultFontFilename,
			BuiltinDataFolder,
			{ DefaultFontSize },
			true,
			UUID("6ce69053-00d7-4c60-a229-249b8d8fd60e"),
			mResourceManifest);

		BuiltinResourcesHelper::importFont(
			BuiltinRawDataFolder + DefaultFontFilename,
			DefaultAAFontFilename,
			BuiltinDataFolder,
			{ TitleFontSize },
			true,
			UUID("10999b74-d976-4116-9f72-21e489a7a8e4"),
			mResourceManifest);

		// Import splash screen
		{
			Path inputPath = BuiltinRawDataFolder + String(SplashScreenName);
			Path outputPath = BuiltinDataFolder + (String(SplashScreenName) + ".asset");

			auto textureIO = gImporter().createImportOptions<TextureImportOptions>(inputPath);
			textureIO->setCPUCached(true);
			textureIO->setGenerateMipmaps(false);
			HTexture splashTexture = gImporter().import<Texture>(inputPath, textureIO);

			SPtr<PixelData> splashPixelData = splashTexture->getProperties().allocBuffer(0, 0);
			splashTexture->readCachedData(*splashPixelData);

			FileEncoder fe(outputPath);
			fe.encode(splashPixelData.get());
		}

		// Generate & save GUI skin
		{
			SPtr<GUISkin> skin = generateGUISkin();
			Path outputPath = BuiltinDataFolder + (GUISkinFile + ".asset");

			HResource skinResource = gResources()._createResourceHandle(skin, UUID("ec0ea68d-efa5-4a3b-a6fc-b15aaec9689f"));

			gResources().save(skinResource, outputPath, true);
			mResourceManifest->registerResource(skinResource.getUUID(), outputPath);
		}

		Resources::instance().unloadAllUnused();
	}

	SPtr<GUISkin> BuiltinEditorResources::generateGUISkin()
	{		
		BuiltinResourceGUIElementStyleLoader loader(BuiltinDataFolder, EditorSkinSpritesFolder);

		Path guiSkinPath = BuiltinRawDataFolder + GUI_SKIN_JSON;
		SPtr<DataStream> guiSkinStream = FileSystem::openFile(guiSkinPath);
		json guiSkinJSON = json::parse(guiSkinStream->getAsString().c_str());

		SPtr<GUISkin> skin = GUISkin::_createPtr();

		for (auto& entry : guiSkinJSON)
		{
			std::string name = entry["name"];

			GUIElementStyle style = BuiltinResourcesHelper::loadGUIStyleFromJSON(entry, loader);
			skin->setStyle(name.c_str(), style);
		}

		return skin;
	}

	HSpriteTexture BuiltinEditorResources::getGUIIcon(const String& name) const
	{
		Path texturePath = EditorIconSpritesFolder;
		texturePath.append("sprite_" + name + ".asset");

		return gResources().load<SpriteTexture>(texturePath);
	}

	HShader BuiltinEditorResources::getShader(const String& name) const
	{
		Path programPath = EditorShaderFolder;
		programPath.append(name + ".asset");

		HShader shader = gResources().load<Shader>(programPath);

#if BS_DEBUG_MODE
		BuiltinResourcesHelper::verifyAndReportShader(shader);
#endif

		return shader;
	}

	HMaterial BuiltinEditorResources::createDockDropOverlayMaterial() const
	{
		return Material::create(mShaderDockOverlay);
	}

	HMaterial BuiltinEditorResources::createSceneGridMaterial() const
	{
		return Material::create(mShaderSceneGrid);
	}

	HMaterial BuiltinEditorResources::createPicking(CullingMode cullMode) const
	{
		UINT32 modeIdx = (UINT32)cullMode;

		return Material::create(mShaderPicking[modeIdx]);
	}

	HMaterial BuiltinEditorResources::createPickingAlpha(CullingMode cullMode) const
	{
		UINT32 modeIdx = (UINT32)cullMode;

		return Material::create(mShaderPickingAlpha[modeIdx]);
	}

	HMaterial BuiltinEditorResources::createLineGizmoMat() const
	{
		return Material::create(mShaderGizmoLine);
	}

	HMaterial BuiltinEditorResources::createSolidGizmoMat() const
	{
		return Material::create(mShaderGizmoSolid);
	}

	HMaterial BuiltinEditorResources::createWireGizmoMat() const
	{
		return Material::create(mShaderGizmoWire);
	}

	HMaterial BuiltinEditorResources::createIconGizmoMat() const
	{
		return Material::create(mShaderGizmoIcon);
	}

	HMaterial BuiltinEditorResources::createGizmoPickingMat() const
	{
		return Material::create(mShaderGizmoPicking);
	}

	HMaterial BuiltinEditorResources::createAlphaGizmoPickingMat() const
	{
		return Material::create(mShaderGizmoAlphaPicking);
	}

	HMaterial BuiltinEditorResources::createLineHandleMat() const
	{
		return Material::create(mShaderHandleLine);
	}

	HMaterial BuiltinEditorResources::createTextGizmoMat() const
	{
		return Material::create(mShaderGizmoText);
	}

	HMaterial BuiltinEditorResources::createSolidHandleMat() const
	{
		return Material::create(mShaderHandleSolid);
	}

	HMaterial BuiltinEditorResources::createHandleClearAlphaMat() const
	{
		return Material::create(mShaderHandleClearAlpha);
	}

	HMaterial BuiltinEditorResources::createSelectionMat() const
	{
		return Material::create(mShaderSelection);
	}

	HSpriteTexture BuiltinEditorResources::getLibraryIcon(ProjectIcon icon, int size) const
	{
		String iconName;

		switch (icon)
		{
		case ProjectIcon::Folder:
			iconName = FolderIconTex;
			break;
		case ProjectIcon::Font:
			iconName = FontIconTex;
			break;
		case ProjectIcon::Mesh:
			iconName = MeshIconTex;
			break;
		case ProjectIcon::Texture:
			iconName = TextureIconTex;
			break;
		case ProjectIcon::PlainText:
			iconName = PlainTextIconTex;
			break;
		case ProjectIcon::ScriptCode:
			iconName = ScriptCodeIconTex;
			break;
		case ProjectIcon::Shader:
			iconName = ShaderIconTex;
			break;
		case ProjectIcon::ShaderInclude:
			iconName = ShaderIncludeIconTex;
			break;
		case ProjectIcon::Material:
			iconName = MaterialIconTex;
			break;
		case ProjectIcon::SpriteTexture:
			iconName = SpriteTextureIconTex;
			break;
		case ProjectIcon::Prefab:
			iconName = PrefabIconTex;
			break;
		case ProjectIcon::GUISkin:
			iconName = GUISkinIconTex;
			break;
		case ProjectIcon::PhysicsMaterial:
			iconName = PhysicsMaterialIconTex;
			break;
		case ProjectIcon::PhysicsMesh:
			iconName = PhysicsMeshIconTex;
			break;
		case ProjectIcon::AudioClip:
			iconName = AudioClipIconTex;
			break;
		case ProjectIcon::AnimationClip:
			iconName = AnimationClipIconTex;
			break;
		}

		if (iconName.empty())
			return HSpriteTexture();

		if (size <= 16)
			iconName += "16";
		else if (size <= 32)
			iconName += "32";
		else if (size <= 48)
			iconName += "48";

		return getGUIIcon(iconName);
	}

	HSpriteTexture BuiltinEditorResources::getToolbarIcon(ToolbarIcon icon) const
	{
		switch (icon)
		{
		case ToolbarIcon::NewCamera:
			return getGUIIcon("ToolbarNewCameraIcon.png");
		case ToolbarIcon::NewRenderable:
			return getGUIIcon("ToolbarNewRenderableIcon.png");
		case ToolbarIcon::NewPointLight:
			return getGUIIcon("ToolbarNewPointLightIcon.png");
		case ToolbarIcon::NewDirLight:
			return getGUIIcon("ToolbarNewDirectionalLightIcon.png");
		case ToolbarIcon::NewSpotLight:
			return getGUIIcon("ToolbarNewSpotLightIcon.png");
		case ToolbarIcon::NewSceneObject:
			return getGUIIcon("ToolbarNewSceneObjectIcon.png");
		case ToolbarIcon::NewCube:
			return getGUIIcon("ToolbarNewCubeIcon.png");
		case ToolbarIcon::NewSphere:
			return getGUIIcon("ToolbarNewSphereIcon.png");
		case ToolbarIcon::NewCone:
			return getGUIIcon("ToolbarNewConeIcon.png");
		case ToolbarIcon::NewQuad:
			return getGUIIcon("ToolbarNewQuadIcon.png");
		case ToolbarIcon::NewMat:
			return getGUIIcon("ToolbarNewMaterialIcon.png");
		case ToolbarIcon::NewCSScript:
			return getGUIIcon("ToolbarNewCSScriptIcon.png");
		case ToolbarIcon::NewShader:
			return getGUIIcon("ToolbarNewShaderIcon.png");
		case ToolbarIcon::NewSpriteTex:
			return getGUIIcon("ToolbarNewSpriteTextureIcon.png");
		case ToolbarIcon::Pause:
			return getGUIIcon("ToolbarPauseIcon.png");
		case ToolbarIcon::Play:
			return getGUIIcon("ToolbarPlayIcon.png");
		case ToolbarIcon::Step:
			return getGUIIcon("ToolbarStepIcon.png");
		case ToolbarIcon::Undo:
			return getGUIIcon("ToolbarUndoIcon.png");
		case ToolbarIcon::Redo:
			return getGUIIcon("ToolbarRedoIcon.png");
		case ToolbarIcon::OpenProject:
			return getGUIIcon("ToolbarOpenProjectIcon.png");
		case ToolbarIcon::SaveProject:
			return getGUIIcon("ToolbarSaveProjectIcon.png");
		case ToolbarIcon::SaveScene:
			return getGUIIcon("ToolbarSaveSceneIcon.png");
		}

		return HSpriteTexture();
	}

	GUIContentImages BuiltinEditorResources::getSceneWindowIcon(SceneWindowIcon icon) const
	{
		HSpriteTexture off;
		HSpriteTexture on;

		switch (icon)
		{
		case SceneWindowIcon::View:
			off = getGUIIcon("SceneViewIcon.png");
			on = getGUIIcon("SceneViewIconOn.png");
			break;
		case SceneWindowIcon::Move:
			off = getGUIIcon("SceneMoveIcon.png");
			on = getGUIIcon("SceneMoveIconOn.png");
			break;
		case SceneWindowIcon::Rotate:
			off = getGUIIcon("SceneRotateIcon.png");
			on = getGUIIcon("SceneRotateIconOn.png");
			break;
		case SceneWindowIcon::Scale:
			off = getGUIIcon("SceneScaleIcon.png");
			on = getGUIIcon("SceneScaleIconOn.png");
			break;
		case SceneWindowIcon::Pivot:
			off = getGUIIcon("ScenePivotIcon.png");
			on = getGUIIcon("ScenePivotIconOn.png");
			break;
		case SceneWindowIcon::Center:
			off = getGUIIcon("SceneCenterIcon.png");
			on = getGUIIcon("SceneCenterIconOn.png");
			break;
		case SceneWindowIcon::Local:
			off = getGUIIcon("SceneLocalIcon.png");
			on = getGUIIcon("SceneLocalIconOn.png");
			break;
		case SceneWindowIcon::World:
			off = getGUIIcon("SceneWorldIcon.png");
			on = getGUIIcon("SceneWorldIconOn.png");
			break;
		case SceneWindowIcon::MoveSnap:
			off = getGUIIcon("SceneMoveSnapIcon.png");
			on = getGUIIcon("SceneMoveSnapIconOn.png");
			break;
		case SceneWindowIcon::RotateSnap:
			off = getGUIIcon("SceneRotateSnapIcon.png");
			on = getGUIIcon("SceneRotateSnapIconOn.png");
			break;
		}

		GUIContentImages output;
		output.normal = off;
		output.hover = off;
		output.active = on;
		output.focused = off;
		output.normalOn = on;
		output.hoverOn = on;
		output.activeOn = on;
		output.focusedOn = on;

		return output;
	}

	HSpriteTexture BuiltinEditorResources::getLibraryWindowIcon(LibraryWindowIcon icon) const
	{
		switch (icon)
		{
		case LibraryWindowIcon::Home:
			return getGUIIcon("LibraryHomeIcon.png");
		case LibraryWindowIcon::Up:
			return getGUIIcon("LibraryUpIcon.png");
		case LibraryWindowIcon::Clear:
			return getGUIIcon("LibraryClearSearchIcon.png");
		case LibraryWindowIcon::Options:
			return getGUIIcon("LibraryOptionsIcon.png");
		}

		return HSpriteTexture();
	}

	HSpriteTexture BuiltinEditorResources::getInspectorWindowIcon(InspectorWindowIcon icon) const
	{
		switch (icon)
		{
		case InspectorWindowIcon::Create:
			return getGUIIcon("InspectorCreateIcon.png");
		case InspectorWindowIcon::Clone:
			return getGUIIcon("InspectorCloneIcon.png");
		case InspectorWindowIcon::Clear:
			return getGUIIcon("InspectorClearIcon.png");
		case InspectorWindowIcon::Resize:
			return getGUIIcon("InspectorResizeIcon.png");
		case InspectorWindowIcon::Delete:
			return getGUIIcon("InspectorDeleteIcon.png");
		case InspectorWindowIcon::MoveUp:
			return getGUIIcon("InspectorMoveUpIcon.png");
		case InspectorWindowIcon::MoveDown:
			return getGUIIcon("InspectorMoveDownIcon.png");
		case InspectorWindowIcon::Edit:
			return getGUIIcon("InspectorEditIcon.png");
		case InspectorWindowIcon::Apply:
			return getGUIIcon("InspectorApplyIcon.png");
		case InspectorWindowIcon::Add:
			return getGUIIcon("InspectorAddIcon.png");
		case InspectorWindowIcon::Cancel:
			return getGUIIcon("InspectorCancelIcon.png");
		}

		return HSpriteTexture();
	}

	GUIContentImages BuiltinEditorResources::getAnimationWindowIcon(AnimationWindowIcon icon) const
	{
		HSpriteTexture off;
		HSpriteTexture on;

		switch (icon)
		{
		case AnimationWindowIcon::Play:
			off = getGUIIcon("AnimationPlayIcon.png");
			on = getGUIIcon("AnimationPlayIconOn.png");
			break;
		case AnimationWindowIcon::Record:
			off = getGUIIcon("AnimationRecordIcon.png");
			on = getGUIIcon("AnimationRecordIconOn.png");
			break;
		case AnimationWindowIcon::FrameForward:
			off = getGUIIcon("AnimationFrameForwardIcon.png");
			on = getGUIIcon("AnimationFrameForwardIconOn.png");
			break;
		case AnimationWindowIcon::FrameBack:
			off = getGUIIcon("AnimationFrameBackIcon.png");
			on = getGUIIcon("AnimationFrameBackIconOn.png");
			break;
		case AnimationWindowIcon::AddEvent:
			off = getGUIIcon("AnimationAddEventIcon.png");
			on = getGUIIcon("AnimationAddEventIconOn.png");
			break;
		case AnimationWindowIcon::AddKeyframe:
			off = getGUIIcon("AnimationAddKeyframeIcon.png");
			on = getGUIIcon("AnimationAddKeyframeIconOn.png");
			break;
		case AnimationWindowIcon::Event:
			off = getGUIIcon("AnimationEventIcon.png");
			on = off;
			break;
		case AnimationWindowIcon::Keyframe:
			off = getGUIIcon("AnimationKeyframeIcon.png");
			on = off;
			break;
		}

		GUIContentImages output;
		output.normal = off;
		output.hover = off;
		output.active = on;
		output.focused = off;
		output.normalOn = on;
		output.hoverOn = on;
		output.activeOn = on;
		output.focusedOn = on;

		return output;
	}

	HSpriteTexture BuiltinEditorResources::getIcon(EditorIcon icon) const
	{
		switch (icon)
		{
		case EditorIcon::X:
			return getGUIIcon(XButtonNormalTex);
		case EditorIcon::Component:
			return getGUIIcon("IconComponent.png");
		case EditorIcon::SceneObject:
			return getGUIIcon("IconSceneObject.png");
		}

		return HSpriteTexture();
	}

	HSpriteTexture BuiltinEditorResources::getLogMessageIcon(LogMessageIcon icon, UINT32 size, bool dark) const
	{
		if (size < 24) // Round to 16
		{
			if (dark)
			{
				switch (icon)
				{
				case LogMessageIcon::Info:
					return getGUIIcon("IconInfoDark.png");
				case LogMessageIcon::Warning:
					return getGUIIcon("IconWarningDark.png");
				case LogMessageIcon::Error:
					return getGUIIcon("IconErrorDark.png");
				}
			}
			else
			{
				switch (icon)
				{
				case LogMessageIcon::Info:
					return getGUIIcon("IconInfo.png");
				case LogMessageIcon::Warning:
					return getGUIIcon("IconWarning.png");
				case LogMessageIcon::Error:
					return getGUIIcon("IconError.png");
				}
			}
		}
		else // Round to 32
		{
			switch (icon)
			{
			case LogMessageIcon::Info:
				return getGUIIcon("IconInfo32.png");
			case LogMessageIcon::Warning:
				return getGUIIcon("IconWarning32.png");
			case LogMessageIcon::Error:
				return getGUIIcon("IconError32.png");
			}
		}

		return HSpriteTexture();
	}

	SPtr<PixelData> BuiltinEditorResources::getSplashScreen()
	{
		Path splashScreenPath = gEditorApplication().getDataPath() + (String(SplashScreenName) + ".asset");
		FileDecoder fd(splashScreenPath);

		return std::static_pointer_cast<PixelData>(fd.decode());
	}

	String BuiltinEditorResources::getEmptyShaderCode() const
	{
		Path filePath = BuiltinDataFolder;
		filePath.append(EmptyShaderCodeFile);

		SPtr<DataStream> fileStream = FileSystem::openFile(filePath);
		if (fileStream != nullptr)
			return fileStream->getAsString();

		return StringUtil::BLANK;
	}

	String BuiltinEditorResources::getEmptyCSScriptCode() const
	{
		Path filePath = BuiltinDataFolder;
		filePath.append(EmptyCSScriptCodeFile);

		SPtr<DataStream> fileStream = FileSystem::openFile(filePath);
		if (fileStream != nullptr)
			return fileStream->getAsString();

		return StringUtil::BLANK;
	}

	Path BuiltinEditorResources::getShaderIncludeFolder()
	{
		return gEditorApplication().getDataPath() + ShaderIncludeFolder;
	}

	Path BuiltinEditorResources::getDefaultWidgetLayoutPath()
	{
		return gEditorApplication().getDataPath() + "Layout.asset";
	}
}