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

	const char* BuiltinEditorResources::DataListFile = "DataList.json";
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

	const String BuiltinEditorResources::ButtonNormalTex = u8"ButtonNormal.png";
	const String BuiltinEditorResources::ButtonHoverTex = u8"ButtonHover.png";
	const String BuiltinEditorResources::ButtonActiveTex = u8"ButtonActive.png";

	const String BuiltinEditorResources::ButtonLeftNormalTex = u8"ButtonLeftNormal.png";
	const String BuiltinEditorResources::ButtonLeftHoverTex = u8"ButtonLeftHover.png";
	const String BuiltinEditorResources::ButtonLeftActiveTex = u8"ButtonLeftActive.png";

	const String BuiltinEditorResources::ButtonRightNormalTex = u8"ButtonRightNormal.png";
	const String BuiltinEditorResources::ButtonRightHoverTex = u8"ButtonRightHover.png";
	const String BuiltinEditorResources::ButtonRightActiveTex = u8"ButtonRightActive.png";

	const String BuiltinEditorResources::ToggleNormalTex = u8"ToggleNormal.png";
	const String BuiltinEditorResources::ToggleHoverTex = u8"ToggleHover.png";
	const String BuiltinEditorResources::ToggleNormalOnTex = u8"ToggleNormalOn.png";
	const String BuiltinEditorResources::ToggleHoverOnTex = u8"ToggleHoverOn.png";

	const String BuiltinEditorResources::InputBoxNormalTex = u8"InputBoxNormal.png";
	const String BuiltinEditorResources::InputBoxHoverTex = u8"InputBoxHover.png";
	const String BuiltinEditorResources::InputBoxFocusedTex = u8"InputBoxActive.png";

	const String BuiltinEditorResources::ObjectDropBtnNormalTex = u8"ObjectDropNormal.png";
	const String BuiltinEditorResources::ObjectDropBtnNormalOnTex = u8"ObjectDropNormalOn.png";
	const String BuiltinEditorResources::ObjectClearBtnNormalTex = u8"ObjectDropClearNormal.png";
	const String BuiltinEditorResources::ObjectClearBtnHoverTex = u8"ObjectDropClearHover.png";
	const String BuiltinEditorResources::ObjectClearBtnActiveTex = u8"ObjectDropClearActive.png";
	
	const String BuiltinEditorResources::DropDownBtnNormalTex = u8"DropDownButtonNormal.png";
	const String BuiltinEditorResources::DropDownBtnHoverTex = u8"DropDownButtonHover.png";
	const String BuiltinEditorResources::DropDownBtnActiveTex = u8"DropDownButtonActive.png";

	const String BuiltinEditorResources::SliderHBackgroundTex = u8"SliderHBackground.png";
	const String BuiltinEditorResources::SliderHFillTex = u8"SliderHFill.png";
	const String BuiltinEditorResources::SliderVBackgroundTex = u8"SliderVBackground.png";
	const String BuiltinEditorResources::SliderVFillTex = u8"SliderVFill.png";
	const String BuiltinEditorResources::SliderHandleNormalTex = u8"SliderHandleNormal.png";
	const String BuiltinEditorResources::SliderHandleHoverTex = u8"SliderHandleHover.png";
	const String BuiltinEditorResources::SliderHandleActiveTex = u8"SliderHandleActive.png";

	const String BuiltinEditorResources::FoldoutOpenNormalTex = u8"FoldoutNormalOn.png";
	const String BuiltinEditorResources::FoldoutOpenHoverTex = u8"FoldoutHoverOn.png";
	const String BuiltinEditorResources::FoldoutOpenActiveTex = u8"FoldoutHoverOn.png";
	const String BuiltinEditorResources::FoldoutClosedNormalTex = u8"FoldoutNormalOff.png";
	const String BuiltinEditorResources::FoldoutClosedHoverTex = u8"FoldoutHoverOff.png";
	const String BuiltinEditorResources::FoldoutClosedActiveTex = u8"FoldoutHoverOff.png";

	const String BuiltinEditorResources::WindowBackgroundTex = u8"WindowBackground.png";

	const String BuiltinEditorResources::WindowFrameNormal = u8"WindowFrameNormal.png";
	const String BuiltinEditorResources::WindowFrameFocused = u8"WindowFrameFocused.png";

	const String BuiltinEditorResources::CloseButtonNormalTex = u8"CloseButtonNormal.png";
	const String BuiltinEditorResources::CloseButtonHoverTex = u8"CloseButtonHover.png";
	const String BuiltinEditorResources::CloseButtonActiveTex = u8"CloseButtonActive.png";

	const String BuiltinEditorResources::MinButtonNormalTex = u8"MinimizeButtonNormal.png"; 
	const String BuiltinEditorResources::MinButtonHoverTex = u8"MinimizeButtonHover.png"; 
	const String BuiltinEditorResources::MinButtonActiveTex = u8"MinimizeButtonActive.png";

	const String BuiltinEditorResources::MaxButtonNormalTex = u8"MaximizeButtonNormal.png";
	const String BuiltinEditorResources::MaxButtonHoverTex = u8"MaximizeButtonHover.png";
	const String BuiltinEditorResources::MaxButtonActiveTex = u8"MaximizeButtonActive.png";

	const String BuiltinEditorResources::TabBarBackgroundTex = u8"TabBarBackground.png";
	const String BuiltinEditorResources::TitleBarBackgroundTex = u8"TitleBarBackground.png";

	const String BuiltinEditorResources::TabButtonNormalTex = u8"TabButtonNormal.png";
	const String BuiltinEditorResources::TabButtonFocusedTex = u8"TabButtonFocused.png";

	const String BuiltinEditorResources::ScrollBarUpNormalTex = u8"ScrollArrowUpNormal.png";
	const String BuiltinEditorResources::ScrollBarUpHoverTex = u8"ScrollArrowUpHover.png";
	const String BuiltinEditorResources::ScrollBarUpActiveTex = u8"ScrollArrowUpActive.png";

	const String BuiltinEditorResources::ScrollBarDownNormalTex = u8"ScrollArrowDownNormal.png";
	const String BuiltinEditorResources::ScrollBarDownHoverTex = u8"ScrollArrowDownHover.png";
	const String BuiltinEditorResources::ScrollBarDownActiveTex = u8"ScrollArrowDownActive.png";

	const String BuiltinEditorResources::ScrollBarLeftNormalTex = u8"ScrollArrowLeftNormal.png";
	const String BuiltinEditorResources::ScrollBarLeftHoverTex = u8"ScrollArrowLeftHover.png";
	const String BuiltinEditorResources::ScrollBarLeftActiveTex = u8"ScrollArrowLeftActive.png";

	const String BuiltinEditorResources::ScrollBarRightNormalTex = u8"ScrollArrowRightNormal.png";
	const String BuiltinEditorResources::ScrollBarRightHoverTex = u8"ScrollArrowRightHover.png";
	const String BuiltinEditorResources::ScrollBarRightActiveTex = u8"ScrollArrowRightActive.png";

	const String BuiltinEditorResources::ScrollBarHandleHorzNormalTex = u8"ScrollBarHHandleNormal.png";
	const String BuiltinEditorResources::ScrollBarHandleHorzHoverTex = u8"ScrollBarHHandleHover.png";
	const String BuiltinEditorResources::ScrollBarHandleHorzActiveTex = u8"ScrollBarHHandleActive.png";

	const String BuiltinEditorResources::ScrollBarHandleVertNormalTex = u8"ScrollBarVHandleNormal.png";
	const String BuiltinEditorResources::ScrollBarHandleVertHoverTex = u8"ScrollBarVHandleHover.png";
	const String BuiltinEditorResources::ScrollBarHandleVertActiveTex = u8"ScrollBarVHandleActive.png";

	const String BuiltinEditorResources::ScrollBarResizeableHandleHorzNormalTex = u8"ScrollBarHHandleResizeableNormal.png";
	const String BuiltinEditorResources::ScrollBarResizeableHandleHorzHoverTex = u8"ScrollBarHHandleResizeableHover.png";
	const String BuiltinEditorResources::ScrollBarResizeableHandleHorzActiveTex = u8"ScrollBarHHandleResizeableActive.png";

	const String BuiltinEditorResources::ScrollBarResizeableHandleVertNormalTex = u8"ScrollBarVHandleResizeableNormal.png";
	const String BuiltinEditorResources::ScrollBarResizeableHandleVertHoverTex = u8"ScrollBarVHandleResizeableHover.png";
	const String BuiltinEditorResources::ScrollBarResizeableHandleVertActiveTex = u8"ScrollBarVHandleResizeableActive.png";

	const String BuiltinEditorResources::ScrollBarHBgTex = u8"ScrollBarHBackground.png";
	const String BuiltinEditorResources::ScrollBarVBgTex = u8"ScrollBarVBackground.png";

	const String BuiltinEditorResources::DropDownBoxBgTex = u8"DropDownBoxBg.png";
	const String BuiltinEditorResources::DropDownBoxSideBgTex = u8"DropDownBoxSideBg.png";
	const String BuiltinEditorResources::DropDownBoxHandleTex = u8"DropDownBoxScrollHandle.png";

	const String BuiltinEditorResources::DropDownBoxEntryNormalTex = u8"DropDownBoxEntryNormal.png";
	const String BuiltinEditorResources::DropDownBoxEntryHoverTex = u8"DropDownBoxEntryHover.png";

	const String BuiltinEditorResources::DropDownBoxEntryToggleNormalTex = u8"DropDownBoxEntryToggleNormal.png";
	const String BuiltinEditorResources::DropDownBoxEntryToggleHoverTex = u8"DropDownBoxEntryToggleHover.png";
	const String BuiltinEditorResources::DropDownBoxEntryToggleNormalOnTex = u8"DropDownBoxEntryToggleNormalOn.png";
	const String BuiltinEditorResources::DropDownBoxEntryToggleHoverOnTex = u8"DropDownBoxEntryToggleHoverOn.png";

	const String BuiltinEditorResources::DropDownBoxBtnUpNormalTex = u8"DropDownBoxArrowUpNormal.png";
	const String BuiltinEditorResources::DropDownBoxBtnUpHoverTex = u8"DropDownBoxArrowUpHover.png";

	const String BuiltinEditorResources::DropDownBoxBtnDownNormalTex = u8"DropDownBoxArrowDownNormal.png";
	const String BuiltinEditorResources::DropDownBoxBtnDownHoverTex = u8"DropDownBoxArrowDownHover.png";

	const String BuiltinEditorResources::DropDownBoxEntryExpNormalTex = u8"DropDownBoxExpandBtnNormal.png";
	const String BuiltinEditorResources::DropDownBoxEntryExpHoverTex = u8"DropDownBoxExpandBtnHover.png";

	const String BuiltinEditorResources::DropDownSeparatorTex = u8"DropDownBoxSeparator.png";

	const String BuiltinEditorResources::MenuBarBgTex = u8"MenuBarBackground.png";
	const String BuiltinEditorResources::MenuBarBansheeLogoTex = u8"MenuBarLog.png";

	const String BuiltinEditorResources::MenuBarBtnNormalTex = u8"MenuBarButtonNormal.png";
	const String BuiltinEditorResources::MenuBarBtnActiveTex = u8"MenuBarButtonActive.png";
	const String BuiltinEditorResources::MenuBarBtnHoverTex = u8"MenuBarButtonHover.png";

	const String BuiltinEditorResources::MenuBarLineNormalTex = u8"MenuBarLineNormal.png";
	const String BuiltinEditorResources::MenuBarLineActiveTex = u8"MenuBarLineActive.png";

	const String BuiltinEditorResources::ToolBarBtnNormalTex = u8"ToolBarButtonNormal.png";
	const String BuiltinEditorResources::ToolBarBtnHoverTex = u8"ToolBarButtonHover.png";
	const String BuiltinEditorResources::ToolBarBtnActiveTex = u8"ToolBarButtonActive.png";

	const String BuiltinEditorResources::ToolBarSeparatorTex = u8"ToolBarSeparator.png";

	const String BuiltinEditorResources::TreeViewExpandButtonOffNormal = u8"ExpandArrowNormalOff.png";
	const String BuiltinEditorResources::TreeViewExpandButtonOffHover = u8"ExpandArrowHoverOff.png";
	const String BuiltinEditorResources::TreeViewExpandButtonOnNormal = u8"ExpandArrowNormalOn.png";
	const String BuiltinEditorResources::TreeViewExpandButtonOnHover = u8"ExpandArrowHoverOn.png";

	const String BuiltinEditorResources::TreeViewHighlightBackground = u8"TreeViewHighlightBackground.psd";
	const String BuiltinEditorResources::TreeViewEditBox = u8"TreeViewEditBox.psd";
	const String BuiltinEditorResources::TreeViewElementHighlight = u8"TreeViewElementHighlight.psd";
	const String BuiltinEditorResources::TreeViewElementSepHighlight = u8"TreeViewElementSepHighlight.psd";

	const String BuiltinEditorResources::ColorPickerSliderHorzHandleTex = u8"ColorPickerSliderHorzHandle.psd";
	const String BuiltinEditorResources::ColorPickerSliderVertHandleTex = u8"ColorPickerSliderVertHandle.psd";
	const String BuiltinEditorResources::ColorPickerSlider2DHandleTex = u8"ColorPicker2DHandle.psd";

	const String BuiltinEditorResources::ProgressBarFillTex = u8"ProgressBarFill.png";
	const String BuiltinEditorResources::ProgressBarBgTex = u8"ProgressBarBg.png";

	const String BuiltinEditorResources::SelectionAreaTex = u8"SelectionHighlight.png";
	const String BuiltinEditorResources::SelectionBgTex = u8"SelectionBg.psd";

	const String BuiltinEditorResources::TextureDropTex = u8"TextureDrop.png";
	const String BuiltinEditorResources::TextureDropOnTex = u8"TextureDropHover.png";

	const String BuiltinEditorResources::XButtonNormalTex = u8"XBtnNormal.png";
	const String BuiltinEditorResources::XButtonHoverTex = u8"XBtnHover.png";
	const String BuiltinEditorResources::XButtonActiveTex = u8"XBtnActive.png";

	const String BuiltinEditorResources::StatusBarBgTex = u8"StatusBarBackground.png";
	const String BuiltinEditorResources::ScrollAreaBgTex = u8"ScrollAreaBg.png";

	const String BuiltinEditorResources::InspectorTitleBgTex = u8"InspectorTitleBg.png";
	const String BuiltinEditorResources::InspectorContentBgTex = u8"InspectorContentBg.png";
	const String BuiltinEditorResources::InspectorContentBgAlternateTex = u8"InspectorContentBgAlternate.png";

	const String BuiltinEditorResources::LibraryEntryFirstBgTex = u8"LibraryEntryFirstBg.png";
	const String BuiltinEditorResources::LibraryEntryBgTex = u8"LibraryEntryBg.png";
	const String BuiltinEditorResources::LibraryEntryLastBgTex = u8"LibraryEntryLastBg.png";

	const String BuiltinEditorResources::LibraryEntryVertFirstBgTex = u8"LibraryEntryVertFirstBg.png";
	const String BuiltinEditorResources::LibraryEntryVertBgTex = u8"LibraryEntryVertBg.png";
	const String BuiltinEditorResources::LibraryEntryVertLastBgTex = u8"LibraryEntryVertLastBg.png";

	const char* BuiltinEditorResources::SplashScreenName = u8"SplashScreen.png";

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

	BuiltinEditorResources::~BuiltinEditorResources()
	{ }

	void BuiltinEditorResources::preprocess(bool forceImport, time_t lastUpdateTime)
	{
		Resources::instance().unloadAllUnused();

		Path dataListsFilePath = BuiltinRawDataFolder + DataListFile;
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
		SPtr<GUISkin> skin = GUISkin::_createPtr();

		Path defaultFontPath = BuiltinDataFolder;
		defaultFontPath.append(DefaultFontFilename + ".asset");

		HFont defaultFont = gResources().load<Font>(defaultFontPath);

		Path defaultAAFontPath = BuiltinDataFolder;
		defaultAAFontPath.append(DefaultAAFontFilename + ".asset");

		HFont defaultAAFont = gResources().load<Font>(defaultAAFontPath);

		// Blank entry
		GUIElementStyle blankStyle;

		skin->setStyle("Blank", blankStyle);
		skin->setStyle(GUITexture::getGUITypeName(), blankStyle);

		// Label
		GUIElementStyle labelStyle;
		labelStyle.font = defaultFont;
		labelStyle.fontSize = DefaultFontSize;
		labelStyle.fixedWidth = false;
		labelStyle.fixedHeight = true;
		labelStyle.height = 14;
		labelStyle.minWidth = 10;
		labelStyle.normal.textColor = TextNormalColor;

		skin->setStyle(GUILabel::getGUITypeName(), labelStyle);

		// Window frame
		GUIElementStyle windowFrameStyle;
		windowFrameStyle.normal.texture = getGUITexture(WindowFrameNormal);
		windowFrameStyle.focused.texture = getGUITexture(WindowFrameFocused);
		windowFrameStyle.border.left = 1;
		windowFrameStyle.border.right = 1;
		windowFrameStyle.border.top = 1;
		windowFrameStyle.border.bottom = 1;

		skin->setStyle("WindowFrame", windowFrameStyle);

		// Button
		GUIElementStyle buttonStyle;
		buttonStyle.normal.texture = getGUITexture(ButtonNormalTex);
		buttonStyle.hover.texture = getGUITexture(ButtonHoverTex);
		buttonStyle.active.texture = getGUITexture(ButtonActiveTex);
		buttonStyle.normalOn.texture = getGUITexture(ButtonActiveTex);
		buttonStyle.hoverOn.texture = getGUITexture(ButtonActiveTex);
		buttonStyle.activeOn.texture = getGUITexture(ButtonActiveTex);
		buttonStyle.normal.textColor = TextNormalColor;
		buttonStyle.hover.textColor = TextNormalColor;
		buttonStyle.active.textColor = TextActiveColor;
		buttonStyle.normalOn.textColor = TextActiveColor;
		buttonStyle.hoverOn.textColor = TextActiveColor;
		buttonStyle.activeOn.textColor = TextActiveColor;
		buttonStyle.border.left = 2;
		buttonStyle.border.right = 2;
		buttonStyle.border.top = 2;
		buttonStyle.border.bottom = 4;
		buttonStyle.contentOffset.top = 2;
		buttonStyle.contentOffset.left = 3;
		buttonStyle.contentOffset.right = 3;
		buttonStyle.margins.bottom = 2;
		buttonStyle.fixedHeight = true;
		buttonStyle.height = 21;
		buttonStyle.minWidth = 20;
		buttonStyle.font = defaultFont;
		buttonStyle.fontSize = DefaultFontSize;
		buttonStyle.textHorzAlign = THA_Center;
		buttonStyle.textVertAlign = TVA_Center;

		skin->setStyle(GUIButton::getGUITypeName(), buttonStyle);

		// Left edge button
		GUIElementStyle leftButtonStyle;
		leftButtonStyle.normal.texture = getGUITexture(ButtonLeftNormalTex);
		leftButtonStyle.hover.texture = getGUITexture(ButtonLeftHoverTex);
		leftButtonStyle.active.texture = getGUITexture(ButtonLeftActiveTex);
		leftButtonStyle.normalOn.texture = getGUITexture(ButtonLeftActiveTex);
		leftButtonStyle.hoverOn.texture = getGUITexture(ButtonLeftActiveTex);
		leftButtonStyle.activeOn.texture = getGUITexture(ButtonLeftActiveTex);
		leftButtonStyle.normal.textColor = TextNormalColor;
		leftButtonStyle.hover.textColor = TextNormalColor;
		leftButtonStyle.active.textColor = TextActiveColor;
		leftButtonStyle.normalOn.textColor = TextActiveColor;
		leftButtonStyle.hoverOn.textColor = TextActiveColor;
		leftButtonStyle.activeOn.textColor = TextActiveColor;
		leftButtonStyle.border.left = 7;
		leftButtonStyle.border.right = 2;
		leftButtonStyle.border.top = 2;
		leftButtonStyle.border.bottom = 4;
		leftButtonStyle.contentOffset.top = 2;
		leftButtonStyle.contentOffset.left = 7;
		leftButtonStyle.contentOffset.right = 3;
		leftButtonStyle.margins.bottom = 2;
		leftButtonStyle.fixedHeight = true;
		leftButtonStyle.height = 21;
		leftButtonStyle.minWidth = 20;
		leftButtonStyle.font = defaultFont;
		leftButtonStyle.fontSize = DefaultFontSize;
		leftButtonStyle.textHorzAlign = THA_Center;
		leftButtonStyle.textVertAlign = TVA_Center;

		skin->setStyle("ButtonLeft", leftButtonStyle);

		// Right edge button
		GUIElementStyle rightButtonStyle;
		rightButtonStyle.normal.texture = getGUITexture(ButtonRightNormalTex);
		rightButtonStyle.hover.texture = getGUITexture(ButtonRightHoverTex);
		rightButtonStyle.active.texture = getGUITexture(ButtonRightActiveTex);
		rightButtonStyle.normalOn.texture = getGUITexture(ButtonRightActiveTex);
		rightButtonStyle.hoverOn.texture = getGUITexture(ButtonRightActiveTex);
		rightButtonStyle.activeOn.texture = getGUITexture(ButtonRightActiveTex);
		rightButtonStyle.normal.textColor = TextNormalColor;
		rightButtonStyle.hover.textColor = TextNormalColor;
		rightButtonStyle.active.textColor = TextActiveColor;
		rightButtonStyle.normalOn.textColor = TextActiveColor;
		rightButtonStyle.hoverOn.textColor = TextActiveColor;
		rightButtonStyle.activeOn.textColor = TextActiveColor;
		rightButtonStyle.border.left = 2;
		rightButtonStyle.border.right = 7;
		rightButtonStyle.border.top = 2;
		rightButtonStyle.border.bottom = 4;
		rightButtonStyle.contentOffset.top = 2;
		rightButtonStyle.contentOffset.left = 3;
		rightButtonStyle.contentOffset.right = 7;
		rightButtonStyle.margins.bottom = 2;
		rightButtonStyle.fixedHeight = true;
		rightButtonStyle.height = 21;
		rightButtonStyle.minWidth = 20;
		rightButtonStyle.font = defaultFont;
		rightButtonStyle.fontSize = DefaultFontSize;
		rightButtonStyle.textHorzAlign = THA_Center;
		rightButtonStyle.textVertAlign = TVA_Center;

		skin->setStyle("ButtonRight", rightButtonStyle);

		// Toggle
		GUIElementStyle toggleStyle;
		toggleStyle.normal.texture = getGUITexture(ToggleNormalTex);
		toggleStyle.hover.texture = getGUITexture(ToggleHoverTex);
		toggleStyle.active.texture = toggleStyle.hover.texture;
		toggleStyle.normalOn.texture = getGUITexture(ToggleNormalOnTex);
		toggleStyle.hoverOn.texture = getGUITexture(ToggleHoverOnTex);
		toggleStyle.activeOn.texture = toggleStyle.hoverOn.texture;
		toggleStyle.fixedHeight = true;
		toggleStyle.fixedWidth = true;
		toggleStyle.margins.bottom = 2;
		toggleStyle.height = 15;
		toggleStyle.width = 13;

		skin->setStyle(GUIToggle::getGUITypeName(), toggleStyle);

		// Color
		GUIElementStyle colorStyle;
		colorStyle.margins.left = 2;
		colorStyle.margins.right = 2;
		colorStyle.margins.top = 2;
		colorStyle.margins.bottom = 2;
		colorStyle.fixedHeight = true;
		colorStyle.height = 15;
		colorStyle.minWidth = 10;

		skin->setStyle(GUIColor::getGUITypeName(), colorStyle);

		// Window background texture
		GUIElementStyle windowBgStyle;
		windowBgStyle.normal.texture = getGUITexture(WindowBackgroundTex);

		skin->setStyle("WindowBackground", windowBgStyle);

		// Window tab bar background
		GUIElementStyle tabBarBgStyle;
		tabBarBgStyle.normal.texture = getGUITexture(TabBarBackgroundTex);
		tabBarBgStyle.fixedHeight = true;
		tabBarBgStyle.height = 16;

		skin->setStyle("TabBarBackground", tabBarBgStyle);

		// Tabbed title bar tab button
		GUIElementStyle tabbedBarButton;
		tabbedBarButton.normal.texture = getGUITexture(TabButtonNormalTex);
		tabbedBarButton.hover.texture = tabbedBarButton.normal.texture;
		tabbedBarButton.active.texture = getGUITexture(TabButtonFocusedTex);
		tabbedBarButton.normalOn.texture = tabbedBarButton.active.texture;
		tabbedBarButton.hoverOn.texture = tabbedBarButton.active.texture;
		tabbedBarButton.activeOn.texture = tabbedBarButton.active.texture;
		tabbedBarButton.normal.textColor = TextNormalColor;
		tabbedBarButton.hover.textColor = TextNormalColor;
		tabbedBarButton.active.textColor = TextActiveColor;
		tabbedBarButton.normalOn.textColor = TextActiveColor;
		tabbedBarButton.hoverOn.textColor = TextActiveColor;
		tabbedBarButton.activeOn.textColor = TextActiveColor;
		tabbedBarButton.border.left = 12;
		tabbedBarButton.border.right = 12;
		tabbedBarButton.margins.left = 5;
		tabbedBarButton.margins.right = 5;
		tabbedBarButton.contentOffset.top = 3;
		tabbedBarButton.contentOffset.left = 6;
		tabbedBarButton.contentOffset.right = 6;
		tabbedBarButton.fixedHeight = true;
		tabbedBarButton.height = 15;
		tabbedBarButton.minWidth = 24;
		tabbedBarButton.maxWidth = 110;
		tabbedBarButton.font = defaultFont;
		tabbedBarButton.fontSize = DefaultFontSize;
		tabbedBarButton.textHorzAlign = THA_Center;
		tabbedBarButton.textVertAlign = TVA_Center;

		skin->setStyle("TabbedBarBtn", tabbedBarButton);

		// Tabbed title bar drag/drop button
		GUIElementStyle tabbedBarDropButton;
		tabbedBarDropButton.fixedHeight = true;
		tabbedBarDropButton.fixedWidth = true;
		tabbedBarDropButton.height = 13;
		tabbedBarDropButton.width = 6;

		skin->setStyle("TabbedBarDropArea", tabbedBarDropButton);

		// Window title bar background
		GUIElementStyle titleBarBgStyle;
		titleBarBgStyle.normal.texture = getGUITexture(TitleBarBackgroundTex);
		titleBarBgStyle.fixedHeight = true;
		titleBarBgStyle.height = 17;

		skin->setStyle("TitleBarBackground", titleBarBgStyle);

		// Window minimize button
		GUIElementStyle winMinButtonStyle;
		winMinButtonStyle.normal.texture = getGUITexture(MinButtonNormalTex);
		winMinButtonStyle.hover.texture = getGUITexture(MinButtonHoverTex);
		winMinButtonStyle.active.texture = getGUITexture(MinButtonActiveTex);
		winMinButtonStyle.fixedHeight = true;
		winMinButtonStyle.fixedWidth = true;
		winMinButtonStyle.height = 14;
		winMinButtonStyle.width = 14;

		skin->setStyle("WinMinimizeBtn", winMinButtonStyle);

		// Window maximize button
		GUIElementStyle winMaxButtonStyle;
		winMaxButtonStyle.normal.texture = getGUITexture(MaxButtonNormalTex);
		winMaxButtonStyle.hover.texture = getGUITexture(MaxButtonHoverTex);
		winMaxButtonStyle.active.texture = getGUITexture(MaxButtonActiveTex);
		winMaxButtonStyle.fixedHeight = true;
		winMaxButtonStyle.fixedWidth = true;
		winMaxButtonStyle.height = 14;
		winMaxButtonStyle.width = 14;

		skin->setStyle("WinMaximizeBtn", winMaxButtonStyle);

		// Window close button
		GUIElementStyle winCloseButtonStyle;
		winCloseButtonStyle.normal.texture = getGUITexture(CloseButtonNormalTex);
		winCloseButtonStyle.hover.texture = getGUITexture(CloseButtonHoverTex);
		winCloseButtonStyle.active.texture = getGUITexture(CloseButtonActiveTex);
		winCloseButtonStyle.fixedHeight = true;
		winCloseButtonStyle.fixedWidth = true;
		winCloseButtonStyle.height = 14;
		winCloseButtonStyle.width = 14;

		skin->setStyle("WinCloseBtn", winCloseButtonStyle);

		// Input box
		GUIElementStyle inputBoxStyle;
		inputBoxStyle.normal.texture = getGUITexture(InputBoxNormalTex);
		inputBoxStyle.hover.texture = getGUITexture(InputBoxHoverTex);
		inputBoxStyle.focused.texture = getGUITexture(InputBoxFocusedTex);
		inputBoxStyle.active.texture = inputBoxStyle.normal.texture;
		inputBoxStyle.normal.textColor = TextNormalColor;
		inputBoxStyle.hover.textColor = TextNormalColor;
		inputBoxStyle.focused.textColor = TextNormalColor;
		inputBoxStyle.active.textColor = TextNormalColor;
		inputBoxStyle.border.left = 1;
		inputBoxStyle.border.right = 3;
		inputBoxStyle.border.top = 4;
		inputBoxStyle.border.bottom = 1;
		inputBoxStyle.contentOffset.left = 4;
		inputBoxStyle.contentOffset.right = 4;
		inputBoxStyle.contentOffset.top = 4;
		inputBoxStyle.contentOffset.bottom = 4;
		inputBoxStyle.fixedHeight = true;
		inputBoxStyle.height = 19;
		inputBoxStyle.minWidth = 10;
		inputBoxStyle.font = defaultFont;
		inputBoxStyle.fontSize = DefaultFontSize;
		inputBoxStyle.textHorzAlign = THA_Left;
		inputBoxStyle.textVertAlign = TVA_Top;

		skin->setStyle(GUIInputBox::getGUITypeName(), inputBoxStyle);

		/************************************************************************/
		/* 								SCROLL BAR                      		*/
		/************************************************************************/

		// Up button
		GUIElementStyle scrollUpBtnStyle;
		scrollUpBtnStyle.normal.texture = getGUITexture(ScrollBarUpNormalTex);
		scrollUpBtnStyle.hover.texture = getGUITexture(ScrollBarUpHoverTex);
		scrollUpBtnStyle.active.texture = getGUITexture(ScrollBarUpActiveTex);
		scrollUpBtnStyle.fixedHeight = true;
		scrollUpBtnStyle.fixedWidth = true;
		scrollUpBtnStyle.height = 11;
		scrollUpBtnStyle.width = 13;

		skin->setStyle("ScrollUpBtn", scrollUpBtnStyle);

		// Down button
		GUIElementStyle scrollDownBtnStyle;
		scrollDownBtnStyle.normal.texture = getGUITexture(ScrollBarDownNormalTex);
		scrollDownBtnStyle.hover.texture = getGUITexture(ScrollBarDownHoverTex);
		scrollDownBtnStyle.active.texture = getGUITexture(ScrollBarDownActiveTex);
		scrollDownBtnStyle.fixedHeight = true;
		scrollDownBtnStyle.fixedWidth = true;
		scrollDownBtnStyle.height = 11;
		scrollDownBtnStyle.width = 13;

		skin->setStyle("ScrollDownBtn", scrollDownBtnStyle);

		// Left button
		GUIElementStyle scrollLeftBtnStyle;
		scrollLeftBtnStyle.normal.texture = getGUITexture(ScrollBarLeftNormalTex);
		scrollLeftBtnStyle.hover.texture = getGUITexture(ScrollBarLeftHoverTex);
		scrollLeftBtnStyle.active.texture = getGUITexture(ScrollBarLeftActiveTex);
		scrollLeftBtnStyle.fixedHeight = true;
		scrollLeftBtnStyle.fixedWidth = true;
		scrollLeftBtnStyle.height = 13;
		scrollLeftBtnStyle.width = 11;

		skin->setStyle("ScrollLeftBtn", scrollLeftBtnStyle);

		// Right button
		GUIElementStyle scrollRightBtnStyle;
		scrollRightBtnStyle.normal.texture = getGUITexture(ScrollBarRightNormalTex);
		scrollRightBtnStyle.hover.texture = getGUITexture(ScrollBarRightHoverTex);
		scrollRightBtnStyle.active.texture = getGUITexture(ScrollBarRightActiveTex);
		scrollRightBtnStyle.fixedHeight = true;
		scrollRightBtnStyle.fixedWidth = true;
		scrollRightBtnStyle.height = 13;
		scrollRightBtnStyle.width = 11;

		skin->setStyle("ScrollRightBtn", scrollRightBtnStyle);

		// Horizontal handle
		GUIElementStyle scrollBarHorzBtnStyle;
		scrollBarHorzBtnStyle.normal.texture = getGUITexture(ScrollBarHandleHorzNormalTex);
		scrollBarHorzBtnStyle.hover.texture = getGUITexture(ScrollBarHandleHorzHoverTex);
		scrollBarHorzBtnStyle.active.texture = getGUITexture(ScrollBarHandleHorzActiveTex);
		scrollBarHorzBtnStyle.fixedHeight = true;
		scrollBarHorzBtnStyle.fixedWidth = false;
		scrollBarHorzBtnStyle.minWidth = 10;
		scrollBarHorzBtnStyle.height = 13;
		scrollBarHorzBtnStyle.border.left = 4;
		scrollBarHorzBtnStyle.border.right = 4;

		skin->setStyle("ScrollBarHorzBtn", scrollBarHorzBtnStyle);

		// Vertical handle
		GUIElementStyle scrollBarVertBtnStyle;
		scrollBarVertBtnStyle.normal.texture = getGUITexture(ScrollBarHandleVertNormalTex);
		scrollBarVertBtnStyle.hover.texture = getGUITexture(ScrollBarHandleVertHoverTex);
		scrollBarVertBtnStyle.active.texture = getGUITexture(ScrollBarHandleVertActiveTex);
		scrollBarVertBtnStyle.fixedHeight = false;
		scrollBarVertBtnStyle.fixedWidth = true;
		scrollBarVertBtnStyle.width = 13;
		scrollBarVertBtnStyle.minHeight = 10;
		scrollBarVertBtnStyle.border.top = 4;
		scrollBarVertBtnStyle.border.bottom = 4;

		skin->setStyle("ScrollBarVertBtn", scrollBarVertBtnStyle);

		// Vertical scroll bar
		GUIElementStyle vertScrollBarStyle;
		vertScrollBarStyle.normal.texture = getGUITexture(ScrollBarVBgTex);
		vertScrollBarStyle.hover.texture = vertScrollBarStyle.normal.texture;
		vertScrollBarStyle.active.texture = vertScrollBarStyle.normal.texture;
		vertScrollBarStyle.fixedHeight = false;
		vertScrollBarStyle.fixedWidth = true;
		vertScrollBarStyle.minHeight = 8;
		vertScrollBarStyle.width = 16;

		vertScrollBarStyle.subStyles[GUIScrollBar::getVScrollHandleType()] = "ScrollBarVertBtn";
		vertScrollBarStyle.subStyles[GUIScrollBar::getHScrollHandleType()] = "ScrollBarHorzBtn";

		skin->setStyle("ScrollBarVert", vertScrollBarStyle);

		// Horizontal scroll bar
		GUIElementStyle horzScrollBarStyle;
		horzScrollBarStyle.normal.texture = getGUITexture(ScrollBarHBgTex);
		horzScrollBarStyle.hover.texture = horzScrollBarStyle.normal.texture;
		horzScrollBarStyle.active.texture = horzScrollBarStyle.normal.texture;
		horzScrollBarStyle.fixedHeight = true;
		horzScrollBarStyle.fixedWidth = false;
		horzScrollBarStyle.minWidth = 8;
		horzScrollBarStyle.height = 16;

		horzScrollBarStyle.subStyles[GUIScrollBar::getVScrollHandleType()] = "ScrollBarVertBtn";
		horzScrollBarStyle.subStyles[GUIScrollBar::getHScrollHandleType()] = "ScrollBarHorzBtn";

		skin->setStyle("ScrollBarHorz", horzScrollBarStyle);

		// Horizontal resizeable handle
		GUIElementStyle scrollBarHorzResizeableBtnStyle;
		scrollBarHorzResizeableBtnStyle.normal.texture = getGUITexture(ScrollBarResizeableHandleHorzNormalTex);
		scrollBarHorzResizeableBtnStyle.hover.texture = getGUITexture(ScrollBarResizeableHandleHorzHoverTex);
		scrollBarHorzResizeableBtnStyle.active.texture = getGUITexture(ScrollBarResizeableHandleHorzActiveTex);
		scrollBarHorzResizeableBtnStyle.fixedHeight = true;
		scrollBarHorzResizeableBtnStyle.fixedWidth = false;
		scrollBarHorzResizeableBtnStyle.minWidth = 15;
		scrollBarHorzResizeableBtnStyle.height = 13;
		scrollBarHorzResizeableBtnStyle.border.left = 7;
		scrollBarHorzResizeableBtnStyle.border.right = 7;

		skin->setStyle("ScrollBarResizeableHorzBtn", scrollBarHorzResizeableBtnStyle);

		// Vertical resizeable handle
		GUIElementStyle scrollBarVertResizeableBtnStyle;
		scrollBarVertResizeableBtnStyle.normal.texture = getGUITexture(ScrollBarResizeableHandleVertNormalTex);
		scrollBarVertResizeableBtnStyle.hover.texture = getGUITexture(ScrollBarResizeableHandleVertHoverTex);
		scrollBarVertResizeableBtnStyle.active.texture = getGUITexture(ScrollBarResizeableHandleVertActiveTex);
		scrollBarVertResizeableBtnStyle.fixedHeight = false;
		scrollBarVertResizeableBtnStyle.fixedWidth = true;
		scrollBarVertResizeableBtnStyle.width = 13;
		scrollBarVertResizeableBtnStyle.minHeight = 15;
		scrollBarVertResizeableBtnStyle.border.top = 7;
		scrollBarVertResizeableBtnStyle.border.bottom = 7;

		skin->setStyle("ScrollBarResizeableVertBtn", scrollBarVertResizeableBtnStyle);

		// Vertical resizeable scroll bar
		GUIElementStyle vertResizeableScrollBarStyle;
		vertResizeableScrollBarStyle.normal.texture = getGUITexture(ScrollBarVBgTex);
		vertResizeableScrollBarStyle.hover.texture = vertResizeableScrollBarStyle.normal.texture;
		vertResizeableScrollBarStyle.active.texture = vertResizeableScrollBarStyle.normal.texture;
		vertResizeableScrollBarStyle.fixedHeight = false;
		vertResizeableScrollBarStyle.fixedWidth = true;
		vertResizeableScrollBarStyle.minHeight = 15;
		vertResizeableScrollBarStyle.width = 16;

		vertResizeableScrollBarStyle.subStyles[GUIScrollBar::getVScrollHandleType()] = "ScrollBarResizeableVertBtn";
		vertResizeableScrollBarStyle.subStyles[GUIScrollBar::getHScrollHandleType()] = "ScrollBarResizeableHorzBtn";

		skin->setStyle("ResizeableScrollBarVert", vertResizeableScrollBarStyle);

		// Horizontal resizeable scroll bar
		GUIElementStyle horzResizeableScrollBarStyle;
		horzResizeableScrollBarStyle.normal.texture = getGUITexture(ScrollBarHBgTex);
		horzResizeableScrollBarStyle.hover.texture = horzResizeableScrollBarStyle.normal.texture;
		horzResizeableScrollBarStyle.active.texture = horzResizeableScrollBarStyle.normal.texture;
		horzResizeableScrollBarStyle.fixedHeight = true;
		horzResizeableScrollBarStyle.fixedWidth = false;
		horzResizeableScrollBarStyle.minWidth = 15;
		horzResizeableScrollBarStyle.height = 16;

		horzResizeableScrollBarStyle.subStyles[GUIScrollBar::getVScrollHandleType()] = "ScrollBarResizeableVertBtn";
		horzResizeableScrollBarStyle.subStyles[GUIScrollBar::getHScrollHandleType()] = "ScrollBarResizeableHorzBtn";

		skin->setStyle("ResizeableScrollBarHorz", horzResizeableScrollBarStyle);

		/************************************************************************/
		/* 								DROP DOWN BOX                      		*/
		/************************************************************************/

		// ListBox button
		GUIElementStyle dropDownListStyle;
		dropDownListStyle.normal.texture = getGUITexture(DropDownBtnNormalTex);
		dropDownListStyle.hover.texture = getGUITexture(DropDownBtnHoverTex);
		dropDownListStyle.active.texture = getGUITexture(DropDownBtnActiveTex);
		dropDownListStyle.normalOn.texture = dropDownListStyle.active.texture;
		dropDownListStyle.hoverOn.texture = dropDownListStyle.active.texture;
		dropDownListStyle.activeOn.texture = dropDownListStyle.active.texture;
		dropDownListStyle.normal.textColor = TextNormalColor;
		dropDownListStyle.hover.textColor = TextNormalColor;
		dropDownListStyle.active.textColor = TextNormalColor;
		dropDownListStyle.normalOn.textColor = TextNormalColor;
		dropDownListStyle.hoverOn.textColor = TextNormalColor;
		dropDownListStyle.activeOn.textColor = TextNormalColor;
		dropDownListStyle.fixedHeight = true;
		dropDownListStyle.fixedWidth = false;
		dropDownListStyle.height = 21;
		dropDownListStyle.minWidth = 20;
		dropDownListStyle.contentOffset.left = 3;
		dropDownListStyle.contentOffset.right = 18;
		dropDownListStyle.contentOffset.top = 2;
		dropDownListStyle.contentOffset.bottom = 2;
		dropDownListStyle.border.left = 2;
		dropDownListStyle.border.right = 16;
		dropDownListStyle.border.top = 2;
		dropDownListStyle.border.bottom = 4;
		dropDownListStyle.margins.bottom = 2;
		dropDownListStyle.font = defaultFont;
		dropDownListStyle.fontSize = DefaultFontSize;
		dropDownListStyle.textHorzAlign = THA_Left;
		dropDownListStyle.textVertAlign = TVA_Center;

		skin->setStyle(GUIListBox::getGUITypeName(), dropDownListStyle);

		// DropDown scroll up button
		GUIElementStyle dropDownScrollUpBtnStyle;
		dropDownScrollUpBtnStyle.normal.texture = getGUITexture(DropDownBoxBtnUpNormalTex);
		dropDownScrollUpBtnStyle.hover.texture = getGUITexture(DropDownBoxBtnUpHoverTex);
		dropDownScrollUpBtnStyle.active.texture = dropDownScrollUpBtnStyle.hover.texture;
		dropDownScrollUpBtnStyle.fixedHeight = true;
		dropDownScrollUpBtnStyle.fixedWidth = true;
		dropDownScrollUpBtnStyle.width = 8;
		dropDownScrollUpBtnStyle.height = 12;

		skin->setStyle("ListBoxScrollUpBtn", dropDownScrollUpBtnStyle);
		skin->setStyle("MenuBarScrollUpBtn", dropDownScrollUpBtnStyle);
		skin->setStyle("ContextMenuScrollUpBtn", dropDownScrollUpBtnStyle);

		// DropDown scroll down button
		GUIElementStyle dropDownScrollDownBtnStyle;
		dropDownScrollDownBtnStyle.normal.texture = getGUITexture(DropDownBoxBtnDownNormalTex);
		dropDownScrollDownBtnStyle.hover.texture = getGUITexture(DropDownBoxBtnDownHoverTex);
		dropDownScrollDownBtnStyle.active.texture = dropDownScrollDownBtnStyle.hover.texture;
		dropDownScrollDownBtnStyle.fixedHeight = true;
		dropDownScrollDownBtnStyle.fixedWidth = true;
		dropDownScrollDownBtnStyle.width = 8;
		dropDownScrollDownBtnStyle.height = 12;

		skin->setStyle("ListBoxScrollDownBtn", dropDownScrollDownBtnStyle);
		skin->setStyle("MenuBarScrollDownBtn", dropDownScrollDownBtnStyle);
		skin->setStyle("ContextMenuScrollDownBtn", dropDownScrollDownBtnStyle);

		// DropDown handle
		GUIElementStyle dropDownScrollHandleStyle;
		dropDownScrollHandleStyle.normal.texture = getGUITexture(DropDownBoxHandleTex);
		dropDownScrollHandleStyle.fixedHeight = false;
		dropDownScrollHandleStyle.fixedWidth = true;
		dropDownScrollHandleStyle.height = 8;
		dropDownScrollHandleStyle.width = 8;

		skin->setStyle("ListBoxHandle", dropDownScrollHandleStyle);
		skin->setStyle("MenuBarHandle", dropDownScrollHandleStyle);
		skin->setStyle("ContextMenuHandle", dropDownScrollHandleStyle);

		// DropDown sidebar background
		GUIElementStyle dropDownSidebarBg;
		dropDownSidebarBg.normal.texture = getGUITexture(DropDownBoxSideBgTex);
		dropDownSidebarBg.fixedHeight = false;
		dropDownSidebarBg.fixedWidth = true;
		dropDownSidebarBg.height = 8;
		dropDownSidebarBg.width = 9;
		dropDownSidebarBg.border.left = 1;
		dropDownSidebarBg.border.top = 1;
		dropDownSidebarBg.border.bottom = 1;

		skin->setStyle("ListBoxSidebarBg", dropDownSidebarBg);
		skin->setStyle("MenuBarSidebarBg", dropDownSidebarBg);
		skin->setStyle("ContextMenuSidebarBg", dropDownSidebarBg);

		// DropDown entry button
		GUIElementStyle dropDownEntryBtnStyle;
		dropDownEntryBtnStyle.normal.texture = getGUITexture(DropDownBoxEntryNormalTex);
		dropDownEntryBtnStyle.hover.texture = getGUITexture(DropDownBoxEntryHoverTex);
		dropDownEntryBtnStyle.active.texture = dropDownEntryBtnStyle.hover.texture;
		dropDownEntryBtnStyle.normalOn.texture = dropDownEntryBtnStyle.hover.texture;
		dropDownEntryBtnStyle.hoverOn.texture = dropDownEntryBtnStyle.hover.texture;
		dropDownEntryBtnStyle.activeOn.texture = dropDownEntryBtnStyle.hover.texture;
		dropDownEntryBtnStyle.normal.textColor = TextNormalColor;
		dropDownEntryBtnStyle.hover.textColor = TextNormalColor;
		dropDownEntryBtnStyle.active.textColor = TextNormalColor;
		dropDownEntryBtnStyle.normalOn.textColor = TextNormalColor;
		dropDownEntryBtnStyle.hoverOn.textColor = TextNormalColor;
		dropDownEntryBtnStyle.activeOn.textColor = TextNormalColor;
		dropDownEntryBtnStyle.fixedHeight = true;
		dropDownEntryBtnStyle.fixedWidth = false;
		dropDownEntryBtnStyle.height = 16;
		dropDownEntryBtnStyle.width = 30;
		dropDownEntryBtnStyle.font = defaultFont;
		dropDownEntryBtnStyle.fontSize = DefaultFontSize;
		dropDownEntryBtnStyle.textHorzAlign = THA_Left;
		dropDownEntryBtnStyle.textVertAlign = TVA_Center;

		skin->setStyle(GUIDropDownContent::ENTRY_STYLE_TYPE, dropDownEntryBtnStyle);

		// DropDown toggle entry button
		GUIElementStyle dropDownToggleEntryBtnStyle;
		dropDownToggleEntryBtnStyle.normal.texture = getGUITexture(DropDownBoxEntryToggleNormalTex);
		dropDownToggleEntryBtnStyle.hover.texture = getGUITexture(DropDownBoxEntryToggleHoverTex);
		dropDownToggleEntryBtnStyle.active.texture = dropDownToggleEntryBtnStyle.hover.texture;
		dropDownToggleEntryBtnStyle.normalOn.texture = getGUITexture(DropDownBoxEntryToggleNormalOnTex);
		dropDownToggleEntryBtnStyle.hoverOn.texture = getGUITexture(DropDownBoxEntryToggleHoverOnTex);
		dropDownToggleEntryBtnStyle.activeOn.texture = dropDownToggleEntryBtnStyle.hoverOn.texture;
		dropDownToggleEntryBtnStyle.normal.textColor = TextNormalColor;
		dropDownToggleEntryBtnStyle.hover.textColor = TextNormalColor;
		dropDownToggleEntryBtnStyle.active.textColor = TextNormalColor;
		dropDownToggleEntryBtnStyle.normalOn.textColor = TextNormalColor;
		dropDownToggleEntryBtnStyle.hoverOn.textColor = TextNormalColor;
		dropDownToggleEntryBtnStyle.activeOn.textColor = TextNormalColor;
		dropDownToggleEntryBtnStyle.fixedHeight = true;
		dropDownToggleEntryBtnStyle.fixedWidth = false;
		dropDownToggleEntryBtnStyle.height = 18;
		dropDownToggleEntryBtnStyle.width = 30;
		dropDownToggleEntryBtnStyle.border.left = 17;
		dropDownToggleEntryBtnStyle.contentOffset.left = 17;
		dropDownToggleEntryBtnStyle.font = defaultFont;
		dropDownToggleEntryBtnStyle.fontSize = DefaultFontSize;
		dropDownToggleEntryBtnStyle.textHorzAlign = THA_Left;
		dropDownToggleEntryBtnStyle.textVertAlign = TVA_Center;

		skin->setStyle(GUIDropDownContent::ENTRY_TOGGLE_STYLE_TYPE, dropDownToggleEntryBtnStyle);

		// DropDown entry button with expand
		GUIElementStyle dropDownEntryExpBtnStyle;
		dropDownEntryExpBtnStyle.normal.texture = getGUITexture(DropDownBoxEntryExpNormalTex);
		dropDownEntryExpBtnStyle.hover.texture = getGUITexture(DropDownBoxEntryExpHoverTex);
		dropDownEntryExpBtnStyle.active.texture = dropDownEntryExpBtnStyle.hover.texture;
		dropDownEntryExpBtnStyle.normalOn.texture = dropDownEntryExpBtnStyle.hover.texture;
		dropDownEntryExpBtnStyle.hoverOn.texture = dropDownEntryExpBtnStyle.hover.texture;
		dropDownEntryExpBtnStyle.activeOn.texture = dropDownEntryExpBtnStyle.hover.texture;
		dropDownEntryExpBtnStyle.normal.textColor = TextNormalColor;
		dropDownEntryExpBtnStyle.hover.textColor = TextNormalColor;
		dropDownEntryExpBtnStyle.active.textColor = TextNormalColor;
		dropDownEntryExpBtnStyle.normalOn.textColor = TextNormalColor;
		dropDownEntryExpBtnStyle.hoverOn.textColor = TextNormalColor;
		dropDownEntryExpBtnStyle.activeOn.textColor = TextNormalColor;
		dropDownEntryExpBtnStyle.fixedHeight = true;
		dropDownEntryExpBtnStyle.fixedWidth = false;
		dropDownEntryExpBtnStyle.height = 16;
		dropDownEntryExpBtnStyle.width = 30;
		dropDownEntryExpBtnStyle.border.right = 13;
		dropDownEntryExpBtnStyle.font = defaultFont;
		dropDownEntryExpBtnStyle.fontSize = DefaultFontSize;
		dropDownEntryExpBtnStyle.textHorzAlign = THA_Left;
		dropDownEntryExpBtnStyle.textVertAlign = TVA_Center;

		skin->setStyle(GUIDropDownContent::ENTRY_EXP_STYLE_TYPE, dropDownEntryExpBtnStyle);

		// Drop down separator
		GUIElementStyle dropDownSeparatorStyle;
		dropDownSeparatorStyle.normal.texture = getGUITexture(DropDownSeparatorTex);
		dropDownSeparatorStyle.fixedHeight = true;
		dropDownSeparatorStyle.fixedWidth = false;
		dropDownSeparatorStyle.height = 3;
		dropDownSeparatorStyle.width = 30;

		skin->setStyle(GUIDropDownContent::SEPARATOR_STYLE_TYPE, dropDownSeparatorStyle);

		// Drop down content
		GUIElementStyle dropDownContentStyle;
		dropDownContentStyle.minWidth = 50;
		dropDownContentStyle.minHeight = 20;
		dropDownContentStyle.subStyles[GUIDropDownContent::ENTRY_TOGGLE_STYLE_TYPE] = GUIDropDownContent::ENTRY_TOGGLE_STYLE_TYPE;
		dropDownContentStyle.subStyles[GUIDropDownContent::ENTRY_STYLE_TYPE] = GUIDropDownContent::ENTRY_STYLE_TYPE;
		dropDownContentStyle.subStyles[GUIDropDownContent::ENTRY_EXP_STYLE_TYPE] = GUIDropDownContent::ENTRY_EXP_STYLE_TYPE;
		dropDownContentStyle.subStyles[GUIDropDownContent::SEPARATOR_STYLE_TYPE] = GUIDropDownContent::SEPARATOR_STYLE_TYPE;

		skin->setStyle("ListBoxContent", dropDownContentStyle);
		skin->setStyle("MenuBarContent", dropDownContentStyle);
		skin->setStyle("ContextMenuContent", dropDownContentStyle);

		// DropDown box frame
		GUIElementStyle dropDownBoxStyle;
		dropDownBoxStyle.normal.texture = getGUITexture(DropDownBoxBgTex);
		dropDownBoxStyle.hover.texture = dropDownBoxStyle.normal.texture;
		dropDownBoxStyle.active.texture = dropDownBoxStyle.hover.texture;
		dropDownBoxStyle.fixedHeight = false;
		dropDownBoxStyle.fixedWidth = false;
		dropDownBoxStyle.border.left = 2;
		dropDownBoxStyle.border.right = 2;
		dropDownBoxStyle.border.top = 2;
		dropDownBoxStyle.border.bottom = 4;
		dropDownBoxStyle.margins.left = 6;
		dropDownBoxStyle.margins.right = 6;
		dropDownBoxStyle.margins.top = 4;
		dropDownBoxStyle.margins.bottom = 6;

		skin->setStyle("ListBoxFrame", dropDownBoxStyle);
		skin->setStyle("MenuBarFrame", dropDownBoxStyle);
		skin->setStyle("ContextMenuFrame", dropDownBoxStyle);

		/************************************************************************/
		/* 								TOOLTIP                      			*/
		/************************************************************************/

		GUIElementStyle tooltipFrameStyle;
		tooltipFrameStyle.normal.texture = getGUITexture(DropDownBoxBgTex);
		tooltipFrameStyle.hover.texture = tooltipFrameStyle.normal.texture;
		tooltipFrameStyle.active.texture = tooltipFrameStyle.hover.texture;
		tooltipFrameStyle.fixedHeight = false;
		tooltipFrameStyle.fixedWidth = false;
		tooltipFrameStyle.border.left = 2;
		tooltipFrameStyle.border.right = 2;
		tooltipFrameStyle.border.top = 2;
		tooltipFrameStyle.border.bottom = 4;
		tooltipFrameStyle.margins.left = 6;
		tooltipFrameStyle.margins.right = 6;
		tooltipFrameStyle.margins.top = 4;
		tooltipFrameStyle.margins.bottom = 6;

		skin->setStyle(GUITooltip::getFrameStyleName(), tooltipFrameStyle);

		/************************************************************************/
		/* 								MENU BAR	                     		*/
		/************************************************************************/

		// MenuBar background
		GUIElementStyle menuBarBgStyle;
		menuBarBgStyle.normal.texture = getGUITexture(MenuBarBgTex);
		menuBarBgStyle.height = 14;
		menuBarBgStyle.width = 2;
		menuBarBgStyle.border.bottom = 2;

		skin->setStyle(GUIMenuBar::getBackgroundStyleType(), menuBarBgStyle);

		// MenuBar separator line
		GUIElementStyle menuBarLineStyle;
		menuBarLineStyle.normal.texture = getGUITexture(MenuBarLineNormalTex);
		menuBarLineStyle.normalOn.texture = getGUITexture(MenuBarLineActiveTex);
		menuBarLineStyle.fixedHeight = true;
		menuBarLineStyle.height = 1;

		skin->setStyle(GUIMenuBar::getLineStyleType(), menuBarLineStyle);

		// MenuBar Banshee logo
		GUIElementStyle menuBarBansheeLogoStyle;
		menuBarBansheeLogoStyle.normal.texture = getGUITexture(MenuBarBansheeLogoTex);
		menuBarBansheeLogoStyle.fixedHeight = true;
		menuBarBansheeLogoStyle.fixedWidth = true;
		menuBarBansheeLogoStyle.height = 46;
		menuBarBansheeLogoStyle.width = 46;

		skin->setStyle(GUIMenuBar::getLogoStyleType(), menuBarBansheeLogoStyle);

		// MenuBar button
		GUIElementStyle menuBarBtnStyle;
		menuBarBtnStyle.normal.texture = getGUITexture(MenuBarBtnNormalTex);
		menuBarBtnStyle.hover.texture = getGUITexture(MenuBarBtnHoverTex);
		menuBarBtnStyle.active.texture = getGUITexture(MenuBarBtnActiveTex);
		menuBarBtnStyle.normalOn.texture = menuBarBtnStyle.active.texture;
		menuBarBtnStyle.hoverOn.texture = menuBarBtnStyle.active.texture;
		menuBarBtnStyle.activeOn.texture = menuBarBtnStyle.active.texture;
		menuBarBtnStyle.normal.textColor = TextNormalColor;
		menuBarBtnStyle.hover.textColor = TextNormalColor;
		menuBarBtnStyle.active.textColor = TextActiveColor;
		menuBarBtnStyle.normalOn.textColor = TextActiveColor;
		menuBarBtnStyle.hoverOn.textColor = TextActiveColor;
		menuBarBtnStyle.activeOn.textColor = TextActiveColor;
		menuBarBtnStyle.fixedHeight = true;
		menuBarBtnStyle.fixedWidth = false;
		menuBarBtnStyle.height = 14;
		menuBarBtnStyle.width = 4;
		menuBarBtnStyle.margins.left = 2;
		menuBarBtnStyle.margins.right = 2;
		menuBarBtnStyle.margins.top = 2;
		menuBarBtnStyle.margins.bottom = 2;
		menuBarBtnStyle.font = defaultFont;
		menuBarBtnStyle.fontSize = DefaultFontSize;
		menuBarBtnStyle.textHorzAlign = THA_Left;
		menuBarBtnStyle.textVertAlign = TVA_Top;

		skin->setStyle(GUIMenuBar::getMenuItemButtonStyleType(), menuBarBtnStyle);

		// ToolBar separator
		GUIElementStyle toolBarSeparator;
		toolBarSeparator.normal.texture = getGUITexture(ToolBarSeparatorTex);
		toolBarSeparator.fixedWidth = true;
		toolBarSeparator.width = 3;
		toolBarSeparator.height = 32;

		skin->setStyle(GUIMenuBar::getToolBarSeparatorStyleType(), toolBarSeparator);

		// ToolBar button
		GUIElementStyle toolBarBtnStyle;
		toolBarBtnStyle.normal.texture = getGUITexture(ToolBarBtnNormalTex);
		toolBarBtnStyle.hover.texture = getGUITexture(ToolBarBtnHoverTex);
		toolBarBtnStyle.active.texture = getGUITexture(ToolBarBtnActiveTex);
		toolBarBtnStyle.normalOn.texture = getGUITexture(ToolBarBtnActiveTex);
		toolBarBtnStyle.hoverOn.texture = getGUITexture(ToolBarBtnActiveTex);
		toolBarBtnStyle.activeOn.texture = getGUITexture(ToolBarBtnActiveTex);
		toolBarBtnStyle.normal.textColor = TextNormalColor;
		toolBarBtnStyle.hover.textColor = TextNormalColor;
		toolBarBtnStyle.active.textColor = TextActiveColor;
		toolBarBtnStyle.normalOn.textColor = TextNormalColor;
		toolBarBtnStyle.hoverOn.textColor = TextNormalColor;
		toolBarBtnStyle.activeOn.textColor = TextActiveColor;
		toolBarBtnStyle.fixedHeight = true;
		toolBarBtnStyle.fixedWidth = true;
		toolBarBtnStyle.height = 32;
		toolBarBtnStyle.width = 32;

		skin->setStyle(GUIMenuBar::getToolBarButtonStyleType(), toolBarBtnStyle);

		/************************************************************************/
		/* 								SEPARATOR	                     		*/
		/************************************************************************/

		GUIElementStyle separator;
		separator.normal.texture = getGUITexture("Separator.png");
		separator.hover.texture = separator.normal.texture;
		separator.active.texture = separator.normal.texture;
		separator.fixedHeight = false;
		separator.fixedWidth = false;
		separator.height = 2;
		separator.width = 2;

		skin->setStyle("Separator", separator);

		/************************************************************************/
		/* 								HEADER	                     			*/
		/************************************************************************/

		GUIElementStyle headerBackground;
		headerBackground.normal.texture = getGUITexture("HeaderBg.png");

		skin->setStyle("HeaderBackground", headerBackground);

		GUIElementStyle header;
		header.normal.texture = getGUITexture("Header.png");
		header.normal.textColor = TextNormalColor;
		header.border.bottom = 2;
		header.fixedHeight = true;
		header.height = 21;
		header.minWidth = 4;
		header.minHeight = 4;
		header.font = defaultFont;
		header.fontSize = DefaultFontSize;
		header.textHorzAlign = THA_Center;
		header.textVertAlign = TVA_Center;

		skin->setStyle("Header", header);

		/************************************************************************/
		/* 								TREE VIEW	                     		*/
		/************************************************************************/

		// Expand button
		GUIElementStyle expandButtonStyle;
		expandButtonStyle.normal.texture = getGUITexture(TreeViewExpandButtonOffNormal);
		expandButtonStyle.hover.texture = getGUITexture(TreeViewExpandButtonOffHover);
		expandButtonStyle.active.texture = expandButtonStyle.hover.texture;
		expandButtonStyle.normalOn.texture = getGUITexture(TreeViewExpandButtonOnNormal);
		expandButtonStyle.hoverOn.texture = getGUITexture(TreeViewExpandButtonOnHover);
		expandButtonStyle.activeOn.texture = expandButtonStyle.hoverOn.texture;
		expandButtonStyle.fixedHeight = true;
		expandButtonStyle.fixedWidth = true;
		expandButtonStyle.height = 10;
		expandButtonStyle.width = 11;
		expandButtonStyle.normal.textColor = TextNormalColor;
		expandButtonStyle.hover.textColor = TextNormalColor;
		expandButtonStyle.active.textColor = TextNormalColor;
		expandButtonStyle.normalOn.textColor = TextNormalColor;
		expandButtonStyle.hoverOn.textColor = TextNormalColor;
		expandButtonStyle.activeOn.textColor = TextNormalColor;
		expandButtonStyle.font = defaultFont;
		expandButtonStyle.fontSize = DefaultFontSize;
		expandButtonStyle.textHorzAlign = THA_Left;
		expandButtonStyle.textVertAlign = TVA_Center;
		expandButtonStyle.contentOffset = RectOffset(16, 0, 0, 0);
		expandButtonStyle.border.left = 10;

		skin->setStyle("Expand", expandButtonStyle);

		// Entry
		GUIElementStyle treeViewEntryStyle;
		treeViewEntryStyle.font = defaultFont;
		treeViewEntryStyle.fontSize = DefaultFontSize;
		treeViewEntryStyle.fixedWidth = false;
		treeViewEntryStyle.fixedHeight = true;
		treeViewEntryStyle.height = 16;
		treeViewEntryStyle.minWidth = 10;
		treeViewEntryStyle.normal.textColor = TextNormalColor;

		skin->setStyle("TreeViewElementBtn", treeViewEntryStyle);

		// Background
		GUIElementStyle treeViewBackgroundStyle;

		skin->setStyle("TreeViewBackground", treeViewBackgroundStyle);

		// Selection background
		GUIElementStyle treeViewSelBackgroundStyle;
		treeViewSelBackgroundStyle.normal.texture = getGUITexture(SelectionBgTex);
		treeViewSelBackgroundStyle.fixedHeight = false;
		treeViewSelBackgroundStyle.fixedWidth = false;
		treeViewSelBackgroundStyle.height = 2;
		treeViewSelBackgroundStyle.width = 2;

		skin->setStyle("TreeViewSelectionBackground", treeViewSelBackgroundStyle);

		// Highlight background
		GUIElementStyle treeViewHLBackgroundStyle;
		treeViewHLBackgroundStyle.normal.texture = getGUITexture(TreeViewHighlightBackground);
		treeViewHLBackgroundStyle.fixedHeight = false;
		treeViewHLBackgroundStyle.fixedWidth = false;
		treeViewHLBackgroundStyle.height = 2;
		treeViewHLBackgroundStyle.width = 2;

		skin->setStyle("TreeViewHighlightBackground", treeViewHLBackgroundStyle);

		// Edit box
		GUIElementStyle treeViewEditBox;
		treeViewEditBox.normal.texture = getGUITexture(TreeViewEditBox);
		treeViewEditBox.hover.texture = treeViewEditBox.normal.texture;
		treeViewEditBox.focused.texture = treeViewEditBox.normal.texture;
		treeViewEditBox.active.texture = treeViewEditBox.normal.texture;
		treeViewEditBox.normal.textColor = TextNormalColor;
		treeViewEditBox.hover.textColor = TextNormalColor;
		treeViewEditBox.focused.textColor = TextNormalColor;
		treeViewEditBox.active.textColor = TextNormalColor;
		treeViewEditBox.border.left = 1;
		treeViewEditBox.border.right = 1;
		treeViewEditBox.border.top = 1;
		treeViewEditBox.border.bottom = 1;
		treeViewEditBox.margins.left = 1;
		treeViewEditBox.margins.right = 1;
		treeViewEditBox.margins.top = 1;
		treeViewEditBox.margins.bottom = 1;
		treeViewEditBox.fixedHeight = true;
		treeViewEditBox.height = 13;
		treeViewEditBox.minWidth = 10;
		treeViewEditBox.font = defaultFont;
		treeViewEditBox.fontSize = DefaultFontSize;
		treeViewEditBox.textHorzAlign = THA_Left;
		treeViewEditBox.textVertAlign = TVA_Top;

		skin->setStyle(GUITreeViewEditBox::getGUITypeName(), treeViewEditBox);

		// Element highlight
		GUIElementStyle treeViewElementHighlight;
		treeViewElementHighlight.normal.texture = getGUITexture(TreeViewElementHighlight);
		treeViewElementHighlight.border.left = 1;
		treeViewElementHighlight.border.right = 1;
		treeViewElementHighlight.border.top = 1;
		treeViewElementHighlight.border.bottom = 1;

		skin->setStyle("TreeViewElementHighlight", treeViewElementHighlight);

		// Element separator highlight
		GUIElementStyle treeViewElementSepHighlight;
		treeViewElementSepHighlight.normal.texture = getGUITexture(TreeViewElementSepHighlight);
		treeViewElementSepHighlight.border.left = 1;
		treeViewElementSepHighlight.border.right = 1;
		treeViewElementSepHighlight.border.top = 1;
		treeViewElementSepHighlight.border.bottom = 1;

		skin->setStyle("TreeViewElementSepHighlight", treeViewElementSepHighlight);

		/************************************************************************/
		/* 							OBJECT DROP FIELD                      		*/
		/************************************************************************/
		GUIElementStyle objectDropStyle;
		objectDropStyle.normal.texture = getGUITexture(ObjectDropBtnNormalTex);
		objectDropStyle.normalOn.texture = getGUITexture(ObjectDropBtnNormalOnTex);
		objectDropStyle.hover.texture = objectDropStyle.normal.texture;
		objectDropStyle.hoverOn.texture = objectDropStyle.normalOn.texture;
		objectDropStyle.active.texture = objectDropStyle.normal.texture;
		objectDropStyle.activeOn.texture = objectDropStyle.normalOn.texture;
		objectDropStyle.normal.textColor = TextNormalColor;
		objectDropStyle.hover.textColor = TextNormalColor;
		objectDropStyle.active.textColor = TextNormalColor;
		objectDropStyle.normalOn.textColor = TextNormalColor;
		objectDropStyle.hoverOn.textColor = TextNormalColor;
		objectDropStyle.activeOn.textColor = TextNormalColor;
		objectDropStyle.border.left = 2;
		objectDropStyle.border.top = 2;
		objectDropStyle.border.bottom = 4;
		objectDropStyle.contentOffset.left = 3;
		objectDropStyle.contentOffset.right = 1;
		objectDropStyle.margins.bottom = 2;
		objectDropStyle.fixedHeight = true;
		objectDropStyle.height = 21;
		objectDropStyle.minWidth = 20;
		objectDropStyle.font = defaultFont;
		objectDropStyle.fontSize = DefaultFontSize;
		objectDropStyle.textHorzAlign = THA_Center;
		objectDropStyle.textVertAlign = TVA_Center;

		skin->setStyle(ObjectFieldDropBtnStyleName, objectDropStyle);

		GUIElementStyle objectClearBtnStyle;
		objectClearBtnStyle.normal.texture = getGUITexture(ObjectClearBtnNormalTex);
		objectClearBtnStyle.hover.texture = getGUITexture(ObjectClearBtnHoverTex);
		objectClearBtnStyle.active.texture = getGUITexture(ObjectClearBtnActiveTex);
		objectClearBtnStyle.fixedHeight = true;
		objectClearBtnStyle.fixedWidth = true;
		objectClearBtnStyle.height = 21;
		objectClearBtnStyle.width = 16;
		objectClearBtnStyle.margins.bottom = 2;

		skin->setStyle(ObjectFieldClearBtnStyleName, objectClearBtnStyle);

		GUIElementStyle editorObjectFieldStyle;
		editorObjectFieldStyle.fixedHeight = true;
		editorObjectFieldStyle.height = 21;
		editorObjectFieldStyle.minWidth = 30;
		editorObjectFieldStyle.subStyles[ObjectFieldLabelStyleName] = GUITextField::getLabelStyleType();
		editorObjectFieldStyle.subStyles[ObjectFieldDropBtnStyleName] = ObjectFieldDropBtnStyleName;
		editorObjectFieldStyle.subStyles[ObjectFieldClearBtnStyleName] = ObjectFieldClearBtnStyleName;

		skin->setStyle(ObjectFieldStyleName, editorObjectFieldStyle);

		/************************************************************************/
		/* 						TEXTURE DROP FIELD                      		*/
		/************************************************************************/
		GUIElementStyle textureFieldStyle;
		textureFieldStyle.minHeight = 15;
		textureFieldStyle.minWidth = 15;
		textureFieldStyle.subStyles[TextureFieldDropStyleName] = TextureFieldDropStyleName;
		textureFieldStyle.subStyles[TextureFieldClearBtnStyleName] = TextureFieldClearBtnStyleName;
		textureFieldStyle.subStyles[TextureFieldLabelStyleName] = GUITextField::getLabelStyleType();

		skin->setStyle(TextureFieldStyleName, textureFieldStyle);

		GUIElementStyle textureDropStyle;
		textureDropStyle.font = defaultFont;
		textureDropStyle.fontSize = DefaultFontSize;
		textureDropStyle.textHorzAlign = THA_Center;
		textureDropStyle.textVertAlign = TVA_Center;
		textureDropStyle.normal.textColor = Color(95 / 255.0f, 95 / 255.0f, 95 / 255.0f, 1.0f);
		textureDropStyle.normal.texture = getGUITexture(TextureDropTex);
		textureDropStyle.hover.textColor = textureDropStyle.normal.textColor;
		textureDropStyle.hover.texture = textureDropStyle.normal.texture;
		textureDropStyle.active.textColor = textureDropStyle.normal.textColor;
		textureDropStyle.active.texture = textureDropStyle.normal.texture;
		textureDropStyle.normalOn.textColor = Color(95 / 255.0f, 95 / 255.0f, 95 / 255.0f, 1.0f);
		textureDropStyle.normalOn.texture = getGUITexture(TextureDropOnTex);
		textureDropStyle.hoverOn.textColor = textureDropStyle.normalOn.textColor;
		textureDropStyle.hoverOn.texture = textureDropStyle.normalOn.texture;
		textureDropStyle.activeOn.textColor = textureDropStyle.normalOn.textColor;
		textureDropStyle.activeOn.texture = textureDropStyle.normalOn.texture;
		textureDropStyle.height = 84;
		textureDropStyle.width = 82;
		textureDropStyle.fixedHeight = true;
		textureDropStyle.fixedWidth = true;
		textureDropStyle.border.left = 2;
		textureDropStyle.border.right = 2;
		textureDropStyle.border.top = 2;
		textureDropStyle.border.bottom = 4;
		textureDropStyle.contentOffset.left = 4;
		textureDropStyle.contentOffset.right = 4;
		textureDropStyle.contentOffset.top = 4;
		textureDropStyle.contentOffset.bottom = 4;

		skin->setStyle(TextureFieldDropStyleName, textureDropStyle);
		
		GUIElementStyle textureDropClearStyle;
		textureDropClearStyle.normal.texture = getGUITexture(XButtonNormalTex);
		textureDropClearStyle.hover.texture = getGUITexture(XButtonHoverTex);
		textureDropClearStyle.active.texture = getGUITexture(XButtonActiveTex);
		textureDropClearStyle.fixedWidth = true;
		textureDropClearStyle.fixedHeight = true;
		textureDropClearStyle.height = 10;
		textureDropClearStyle.width = 10;

		skin->setStyle(TextureFieldClearBtnStyleName, textureDropClearStyle);

		/************************************************************************/
		/* 								EDITOR FIELDS                      		*/
		/************************************************************************/

		GUIElementStyle editorFieldLabelStyle;
		editorFieldLabelStyle.font = defaultFont;
		editorFieldLabelStyle.fontSize = DefaultFontSize;
		editorFieldLabelStyle.normal.textColor = TextNormalColor;
		editorFieldLabelStyle.fixedWidth = false;
		editorFieldLabelStyle.fixedHeight = true;
		editorFieldLabelStyle.height = 14;
		editorFieldLabelStyle.minWidth = 10;
		editorFieldLabelStyle.textHorzAlign = THA_Left;

		skin->setStyle(GUITextField::getLabelStyleType(), editorFieldLabelStyle);

		GUIElementStyle editorIntFieldStyle;
		editorIntFieldStyle.fixedHeight = true;
		editorIntFieldStyle.height = 21;
		editorIntFieldStyle.minWidth = 30;
		editorIntFieldStyle.subStyles[GUIIntField::getLabelStyleType()] = GUITextField::getLabelStyleType();
		editorIntFieldStyle.subStyles[GUIIntField::getInputStyleType()] = GUIInputBox::getGUITypeName();

		skin->setStyle(GUIIntField::getGUITypeName(), editorIntFieldStyle);

		GUIElementStyle editorFloatFieldStyle;
		editorFloatFieldStyle.fixedHeight = true;
		editorFloatFieldStyle.height = 21;
		editorFloatFieldStyle.minWidth = 30;
		editorFloatFieldStyle.subStyles[GUIFloatField::getLabelStyleType()] = GUITextField::getLabelStyleType();
		editorFloatFieldStyle.subStyles[GUIFloatField::getInputStyleType()] = GUIInputBox::getGUITypeName();

		skin->setStyle(GUIFloatField::getGUITypeName(), editorFloatFieldStyle);

		GUIElementStyle editorTextFieldStyle;
		editorTextFieldStyle.fixedHeight = true;
		editorTextFieldStyle.height = 21;
		editorTextFieldStyle.minWidth = 30;
		editorTextFieldStyle.subStyles[GUITextField::getLabelStyleType()] = GUITextField::getLabelStyleType();
		editorTextFieldStyle.subStyles[GUITextField::getInputStyleType()] = GUIInputBox::getGUITypeName();

		skin->setStyle(GUITextField::getGUITypeName(), editorTextFieldStyle);

		GUIElementStyle editorColorFieldStyle;
		editorColorFieldStyle.fixedHeight = true;
		editorColorFieldStyle.height = 21;
		editorColorFieldStyle.minWidth = 30;
		editorColorFieldStyle.subStyles[GUIColorField::getLabelStyleType()] = GUITextField::getLabelStyleType();
		editorColorFieldStyle.subStyles[GUIColorField::getColorInputStyleType()] = GUIColor::getGUITypeName();

		skin->setStyle(GUIColorField::getGUITypeName(), editorColorFieldStyle);

		GUIElementStyle editorToggleFieldStyle;
		editorToggleFieldStyle.fixedHeight = true;
		editorToggleFieldStyle.height = 15;
		editorToggleFieldStyle.minWidth = 30;
		editorToggleFieldStyle.subStyles[GUIToggleField::getLabelStyleType()] = GUITextField::getLabelStyleType();
		editorToggleFieldStyle.subStyles[GUIToggleField::getToggleStyleType()] = GUIToggle::getGUITypeName();

		skin->setStyle(GUIToggleField::getGUITypeName(), editorToggleFieldStyle);

		GUIElementStyle editorVector2FieldStyle;
		editorVector2FieldStyle.fixedHeight = true;
		editorVector2FieldStyle.height = 35;
		editorVector2FieldStyle.minWidth = 30;
		editorVector2FieldStyle.subStyles[GUIVector2Field::getLabelStyleType()] = GUITextField::getLabelStyleType();
		editorVector2FieldStyle.subStyles[GUIVector2Field::getFloatFieldStyleType()] = GUIFloatField::getGUITypeName();

		skin->setStyle(GUIVector2Field::getGUITypeName(), editorVector2FieldStyle);

		GUIElementStyle editorVector3FieldStyle;
		editorVector3FieldStyle.fixedHeight = true;
		editorVector3FieldStyle.height = 35;
		editorVector3FieldStyle.minWidth = 30;
		editorVector3FieldStyle.subStyles[GUIVector3Field::getLabelStyleType()] = GUITextField::getLabelStyleType();
		editorVector3FieldStyle.subStyles[GUIVector3Field::getFloatFieldStyleType()] = GUIFloatField::getGUITypeName();

		skin->setStyle(GUIVector3Field::getGUITypeName(), editorVector3FieldStyle);

		GUIElementStyle editorVector4FieldStyle;
		editorVector4FieldStyle.fixedHeight = true;
		editorVector4FieldStyle.height = 35;
		editorVector4FieldStyle.minWidth = 30;
		editorVector4FieldStyle.subStyles[GUIVector4Field::getLabelStyleType()] = GUITextField::getLabelStyleType();
		editorVector4FieldStyle.subStyles[GUIVector4Field::getFloatFieldStyleType()] = GUIFloatField::getGUITypeName();

		skin->setStyle(GUIVector4Field::getGUITypeName(), editorVector4FieldStyle);

		GUIElementStyle editorListBoxFieldStyle;
		editorListBoxFieldStyle.fixedHeight = true;
		editorListBoxFieldStyle.height = 21;
		editorListBoxFieldStyle.minWidth = 30;
		editorListBoxFieldStyle.subStyles[GUIListBoxField::getLabelStyleType()] = GUIListBoxField::getLabelStyleType();
		editorListBoxFieldStyle.subStyles[GUIListBoxField::getListBoxStyleType()] = GUIListBox::getGUITypeName();

		skin->setStyle(GUIListBoxField::getGUITypeName(), editorListBoxFieldStyle);

		GUIElementStyle editorSliderFieldStyle;
		editorSliderFieldStyle.fixedHeight = true;
		editorSliderFieldStyle.height = 21;
		editorSliderFieldStyle.minWidth = 30;
		editorSliderFieldStyle.subStyles[GUISliderField::getLabelStyleType()] = GUISliderField::getLabelStyleType();
		editorSliderFieldStyle.subStyles[GUISliderField::getInputStyleType()] = GUIInputBox::getGUITypeName();
		editorSliderFieldStyle.subStyles[GUISliderField::getSliderStyleType()] = GUISliderHorz::getGUITypeName();

		skin->setStyle(GUISliderField::getGUITypeName(), editorSliderFieldStyle);

		/************************************************************************/
		/* 							     FOLDOUT                      		    */
		/************************************************************************/

		GUIElementStyle foldoutStyle;
		foldoutStyle.normal.texture = getGUITexture(FoldoutClosedNormalTex);
		foldoutStyle.hover.texture = getGUITexture(FoldoutClosedHoverTex);
		foldoutStyle.active.texture = getGUITexture(FoldoutOpenActiveTex);
		foldoutStyle.normalOn.texture = getGUITexture(FoldoutOpenNormalTex);
		foldoutStyle.hoverOn.texture = getGUITexture(FoldoutOpenHoverTex);
		foldoutStyle.activeOn.texture = getGUITexture(FoldoutOpenActiveTex);
		foldoutStyle.normal.textColor = TextNormalColor;
		foldoutStyle.hover.textColor = TextNormalColor;
		foldoutStyle.active.textColor = TextNormalColor;
		foldoutStyle.normalOn.textColor = TextNormalColor;
		foldoutStyle.hoverOn.textColor = TextNormalColor;
		foldoutStyle.activeOn.textColor = TextNormalColor;
		foldoutStyle.fixedHeight = true;
		foldoutStyle.fixedWidth = false;
		foldoutStyle.height = 21;
		foldoutStyle.minWidth = 17;
		foldoutStyle.font = defaultFont;
		foldoutStyle.fontSize = DefaultFontSize;
		foldoutStyle.textHorzAlign = THA_Left;
		foldoutStyle.textVertAlign = TVA_Center;
		foldoutStyle.contentOffset = RectOffset(16, 0, 0, 0);
		foldoutStyle.border.left = 15;
		foldoutStyle.border.right = 2;
		foldoutStyle.border.top = 2;
		foldoutStyle.border.bottom = 4;

		skin->setStyle("Foldout", foldoutStyle);

		/************************************************************************/
		/* 								PROGRESS BAR                      		*/
		/************************************************************************/
		GUIElementStyle progressBarBgStyle;
		progressBarBgStyle.fixedHeight = true;
		progressBarBgStyle.height = 17;
		progressBarBgStyle.normal.texture = getGUITexture(ProgressBarBgTex);
		progressBarBgStyle.border.left = 8;
		progressBarBgStyle.border.right = 8;

		skin->setStyle(GUIProgressBar::getBackgroundStyleType(), progressBarBgStyle);

		GUIElementStyle progressBarFillStyle;
		progressBarFillStyle.fixedHeight = true;
		progressBarFillStyle.height = 16;
		progressBarFillStyle.normal.texture = getGUITexture(ProgressBarFillTex);
		progressBarFillStyle.border.left = 9;
		progressBarFillStyle.border.right = 10;

		skin->setStyle(GUIProgressBar::getBarStyleType(), progressBarFillStyle);

		GUIElementStyle progressBarStyle;
		progressBarStyle.fixedHeight = true;
		progressBarStyle.height = 17;
		progressBarStyle.minWidth = 100;

		progressBarStyle.subStyles[GUIProgressBar::getBarStyleType()] = GUIProgressBar::getBarStyleType();
		progressBarStyle.subStyles[GUIProgressBar::getBackgroundStyleType()] = GUIProgressBar::getBackgroundStyleType();

		skin->setStyle(GUIProgressBar::getGUITypeName(), progressBarStyle);

		/************************************************************************/
		/* 								SLIDER                      			*/
		/************************************************************************/

		GUIElementStyle sliderHandleStyle;
		sliderHandleStyle.fixedHeight = true;
		sliderHandleStyle.fixedWidth = true;
		sliderHandleStyle.width = 12;
		sliderHandleStyle.height = 13;
		sliderHandleStyle.normal.texture = getGUITexture(SliderHandleNormalTex);
		sliderHandleStyle.hover.texture = getGUITexture(SliderHandleHoverTex);
		sliderHandleStyle.active.texture = getGUITexture(SliderHandleActiveTex);

		skin->setStyle(GUISlider::getHandleStyleType(), sliderHandleStyle);

		GUIElementStyle sliderHorizontalBgStyle;
		sliderHorizontalBgStyle.fixedHeight = true;
		sliderHorizontalBgStyle.height = 10;
		sliderHorizontalBgStyle.normal.texture = getGUITexture(SliderHBackgroundTex);
		sliderHorizontalBgStyle.border.left = 4;
		sliderHorizontalBgStyle.border.right = 4;

		skin->setStyle("SliderHorzBg", sliderHorizontalBgStyle);

		GUIElementStyle sliderHorizontalFillStyle;
		sliderHorizontalFillStyle.fixedHeight = true;
		sliderHorizontalFillStyle.height = 10;
		sliderHorizontalFillStyle.normal.texture = getGUITexture(SliderHFillTex);
		sliderHorizontalFillStyle.border.left = 6;
		sliderHorizontalFillStyle.border.right = 4;

		skin->setStyle("SliderHorzFill", sliderHorizontalFillStyle);

		GUIElementStyle sliderHorizontalStyle;
		sliderHorizontalStyle.fixedHeight = true;
		sliderHorizontalStyle.height = 13;
		sliderHorizontalStyle.width = 150;
		sliderHorizontalStyle.minWidth = 10;
		sliderHorizontalStyle.subStyles[GUISlider::getHandleStyleType()] = GUISlider::getHandleStyleType();
		sliderHorizontalStyle.subStyles[GUISlider::getBackgroundStyleType()] = "SliderHorzBg";
		sliderHorizontalStyle.subStyles[GUISlider::getFillStyleType()] = "SliderHorzFill";

		skin->setStyle(GUISliderHorz::getGUITypeName(), sliderHorizontalStyle);

		GUIElementStyle sliderVerticalBgStyle;
		sliderVerticalBgStyle.fixedWidth = true;
		sliderVerticalBgStyle.width = 10;
		sliderVerticalBgStyle.normal.texture = getGUITexture(SliderVBackgroundTex);
		sliderVerticalBgStyle.border.top = 4;
		sliderVerticalBgStyle.border.bottom = 4;

		skin->setStyle("SliderVertBg", sliderVerticalBgStyle);

		GUIElementStyle sliderVerticalFillStyle;
		sliderVerticalFillStyle.fixedWidth = true;
		sliderVerticalFillStyle.width = 10;
		sliderVerticalFillStyle.normal.texture = getGUITexture(SliderVFillTex);
		sliderVerticalFillStyle.border.top = 6;
		sliderVerticalFillStyle.border.bottom = 4;

		skin->setStyle("SliderVertFill", sliderVerticalFillStyle);

		GUIElementStyle sliderVerticalStyle;
		sliderVerticalStyle.fixedWidth = true;
		sliderVerticalStyle.width = 13;
		sliderVerticalStyle.height = 150;
		sliderVerticalStyle.minHeight = 10;
		sliderVerticalStyle.subStyles[GUISlider::getHandleStyleType()] = GUISlider::getHandleStyleType();
		sliderVerticalStyle.subStyles[GUISlider::getBackgroundStyleType()] = "SliderVertBg";
		sliderVerticalStyle.subStyles[GUISlider::getFillStyleType()] = "SliderVertFill";

		skin->setStyle(GUISliderVert::getGUITypeName(), sliderVerticalStyle);

		/************************************************************************/
		/* 							COLOR PICKER SLIDER                      	*/
		/************************************************************************/

		GUIElementStyle colorPickerSliderHorzHandleStyle;
		colorPickerSliderHorzHandleStyle.fixedHeight = true;
		colorPickerSliderHorzHandleStyle.fixedWidth = true;
		colorPickerSliderHorzHandleStyle.height = 20;
		colorPickerSliderHorzHandleStyle.width = 7;
		colorPickerSliderHorzHandleStyle.normal.texture = getGUITexture(ColorPickerSliderHorzHandleTex);
		colorPickerSliderHorzHandleStyle.hover.texture = colorPickerSliderHorzHandleStyle.normal.texture;
		colorPickerSliderHorzHandleStyle.active.texture = colorPickerSliderHorzHandleStyle.normal.texture;

		skin->setStyle("ColorSliderHorzHandle", colorPickerSliderHorzHandleStyle);

		GUIElementStyle colorPickerSliderHorzStyle;
		colorPickerSliderHorzStyle.fixedHeight = true;
		colorPickerSliderHorzStyle.height = 32;
		colorPickerSliderHorzStyle.minWidth = 20;
		colorPickerSliderHorzStyle.subStyles[GUISlider::getHandleStyleType()] = "ColorSliderHorzHandle";

		skin->setStyle("ColorSliderHorz", colorPickerSliderHorzStyle);

		GUIElementStyle colorPickerSliderVertHandleStyle;
		colorPickerSliderVertHandleStyle.fixedHeight = true;
		colorPickerSliderVertHandleStyle.fixedWidth = true;
		colorPickerSliderVertHandleStyle.height = 7;
		colorPickerSliderVertHandleStyle.width = 45;
		colorPickerSliderVertHandleStyle.normal.texture = getGUITexture(ColorPickerSliderVertHandleTex);
		colorPickerSliderVertHandleStyle.hover.texture = colorPickerSliderVertHandleStyle.normal.texture;
		colorPickerSliderVertHandleStyle.active.texture = colorPickerSliderVertHandleStyle.normal.texture;

		skin->setStyle("ColorSliderVertHandle", colorPickerSliderVertHandleStyle);

		GUIElementStyle colorPickerSliderVertStyle;
		colorPickerSliderVertStyle.fixedWidth = true;
		colorPickerSliderVertStyle.width = 30;
		colorPickerSliderVertStyle.minHeight = 20;
		colorPickerSliderVertStyle.subStyles[GUISlider::getHandleStyleType()] = "ColorSliderVertHandle";

		skin->setStyle("ColorSliderVert", colorPickerSliderVertStyle);

		GUIElementStyle colorPickerSlider2DHandleStyle;
		colorPickerSlider2DHandleStyle.fixedHeight = true;
		colorPickerSlider2DHandleStyle.fixedWidth = true;
		colorPickerSlider2DHandleStyle.height = 7;
		colorPickerSlider2DHandleStyle.width = 7;
		colorPickerSlider2DHandleStyle.normal.texture = getGUITexture(ColorPickerSlider2DHandleTex);
		colorPickerSlider2DHandleStyle.hover.texture = colorPickerSlider2DHandleStyle.normal.texture;
		colorPickerSlider2DHandleStyle.active.texture = colorPickerSlider2DHandleStyle.normal.texture;

		skin->setStyle("ColorSlider2DHandle", colorPickerSlider2DHandleStyle);

		/************************************************************************/
		/* 								STATUS BAR                      		*/
		/************************************************************************/
		GUIElementStyle statusBarBgStyle;
		statusBarBgStyle.height = 16;
		statusBarBgStyle.border.top = 2;
		statusBarBgStyle.normal.texture = getGUITexture(StatusBarBgTex);

		skin->setStyle(GUIStatusBar::getGUIBackgroundTypeName(), statusBarBgStyle);

		GUIElementStyle statusBarMessageBtnStyle;
		statusBarMessageBtnStyle.font = defaultFont;
		statusBarMessageBtnStyle.fontSize = DefaultFontSize;
		statusBarMessageBtnStyle.fixedHeight = true;
		statusBarMessageBtnStyle.height = 16;
		statusBarMessageBtnStyle.minWidth = 10;
		statusBarMessageBtnStyle.textHorzAlign = THA_Left;
		statusBarMessageBtnStyle.textVertAlign = TVA_Center;
		statusBarMessageBtnStyle.imagePosition = GUIImagePosition::Left;

		skin->setStyle(GUIStatusBar::getGUIMessageTypeName(), statusBarMessageBtnStyle);

		GUIElementStyle statusBarStyle;
		statusBarStyle.height = 16;

		statusBarStyle.subStyles[GUIStatusBar::getGUIBackgroundTypeName()] = GUIStatusBar::getGUIBackgroundTypeName();
		statusBarStyle.subStyles[GUIStatusBar::getGUIMessageTypeName()] = GUIStatusBar::getGUIMessageTypeName();

		skin->setStyle(GUIStatusBar::getGUITypeName(), statusBarStyle);

		/************************************************************************/
		/* 									OTHER                      			*/
		/************************************************************************/

		// Centered label
		GUIElementStyle centeredLabelStyle;
		centeredLabelStyle.font = defaultFont;
		centeredLabelStyle.fontSize = DefaultFontSize;
		centeredLabelStyle.fixedWidth = false;
		centeredLabelStyle.fixedHeight = true;
		centeredLabelStyle.height = 11;
		centeredLabelStyle.minWidth = 10;
		centeredLabelStyle.textHorzAlign = THA_Center;
		centeredLabelStyle.normal.textColor = TextNormalColor;

		skin->setStyle("LabelCentered", centeredLabelStyle);

		// Right-aligned label
		GUIElementStyle rightAlignedLabelStyle;
		rightAlignedLabelStyle.font = defaultFont;
		rightAlignedLabelStyle.fontSize = DefaultFontSize;
		rightAlignedLabelStyle.fixedWidth = false;
		rightAlignedLabelStyle.fixedHeight = true;
		rightAlignedLabelStyle.height = 11;
		rightAlignedLabelStyle.minWidth = 10;
		rightAlignedLabelStyle.textHorzAlign = THA_Right;
		rightAlignedLabelStyle.normal.textColor = TextNormalColor;

		skin->setStyle("RightAlignedLabel", rightAlignedLabelStyle);

		// Multi-line label
		GUIElementStyle multiLinelabelStyle;
		multiLinelabelStyle.font = defaultFont;
		multiLinelabelStyle.fontSize = DefaultFontSize;
		multiLinelabelStyle.fixedWidth = false;
		multiLinelabelStyle.fixedHeight = true;
		multiLinelabelStyle.height = 11;
		multiLinelabelStyle.minWidth = 10;
		multiLinelabelStyle.wordWrap = true;
		multiLinelabelStyle.normal.textColor = TextNormalColor;

		skin->setStyle(BuiltinResources::MultiLineLabelStyle, multiLinelabelStyle);

		// Multi-line centered label
		GUIElementStyle multiLineCenteredLabelStyle;
		multiLineCenteredLabelStyle.font = defaultFont;
		multiLineCenteredLabelStyle.fontSize = DefaultFontSize;
		multiLineCenteredLabelStyle.fixedWidth = false;
		multiLineCenteredLabelStyle.fixedHeight = true;
		multiLineCenteredLabelStyle.height = 11;
		multiLineCenteredLabelStyle.minWidth = 10;
		multiLineCenteredLabelStyle.wordWrap = true;
		multiLineCenteredLabelStyle.textHorzAlign = THA_Center;
		multiLineCenteredLabelStyle.normal.textColor = TextNormalColor;

		skin->setStyle("MultiLineLabelCentered", multiLineCenteredLabelStyle);

		// Title label
		GUIElementStyle titleLabel;
		titleLabel.font = defaultAAFont;
		titleLabel.fontSize = TitleFontSize;
		titleLabel.fixedWidth = false;
		titleLabel.fixedHeight = true;
		titleLabel.height = 20;
		titleLabel.minWidth = 10;
		titleLabel.wordWrap = true;
		titleLabel.textHorzAlign = THA_Center;
		titleLabel.normal.textColor = TextNormalColor;

		skin->setStyle("TitleLabel", titleLabel);

		// Selection area
		GUIElementStyle selectionAreaStyle;
		selectionAreaStyle.normal.texture = getGUITexture(SelectionAreaTex);
		selectionAreaStyle.border.left = 1;
		selectionAreaStyle.border.right = 1;
		selectionAreaStyle.border.top = 1;
		selectionAreaStyle.border.bottom = 1;

		skin->setStyle("SelectionArea", selectionAreaStyle);

		// Selectable label
		GUIElementStyle selectableLabelStyle;
		selectableLabelStyle.normalOn.texture = getGUITexture(SelectionBgTex);
		selectableLabelStyle.hoverOn.texture = selectableLabelStyle.normalOn.texture;
		selectableLabelStyle.activeOn.texture = selectableLabelStyle.normalOn.texture;
		selectableLabelStyle.fixedHeight = true;
		selectableLabelStyle.height = 11;
		selectableLabelStyle.minWidth = 10;
		selectableLabelStyle.font = defaultFont;
		selectableLabelStyle.fontSize = DefaultFontSize;
		selectableLabelStyle.textHorzAlign = THA_Left;
		selectableLabelStyle.normal.textColor = TextNormalColor;

		skin->setStyle("SelectableLabel", selectableLabelStyle);

		// Scroll area background
		GUIElementStyle scrollAreaBg;
		scrollAreaBg.normal.texture = getGUITexture(ScrollAreaBgTex);
		scrollAreaBg.minHeight = 6;
		scrollAreaBg.minWidth = 4;
		scrollAreaBg.border.left = 2;
		scrollAreaBg.border.right = 2;
		scrollAreaBg.border.top = 2;
		scrollAreaBg.border.bottom = 4;
		
		skin->setStyle("ScrollAreaBg", scrollAreaBg);

		// Inspector title area background
		GUIElementStyle inspectorTitleBg;
		inspectorTitleBg.normal.texture = getGUITexture(InspectorTitleBgTex);
		inspectorTitleBg.minHeight = 4;
		inspectorTitleBg.border.bottom = 2;

		skin->setStyle("InspectorTitleBg", inspectorTitleBg);

		// Inspector content background
		GUIElementStyle inspectorContentBg;
		inspectorContentBg.normal.texture = getGUITexture(InspectorContentBgTex);
		inspectorContentBg.minWidth = 4;
		inspectorContentBg.minHeight = 6;
		inspectorContentBg.border.left = 2;
		inspectorContentBg.border.right = 2;
		inspectorContentBg.border.top = 2;
		inspectorContentBg.border.bottom = 4;

		skin->setStyle("InspectorContentBg", inspectorContentBg);

		// Inspector content alternate background
		GUIElementStyle inspectorContentBgAlternate;
		inspectorContentBgAlternate.normal.texture = getGUITexture(InspectorContentBgAlternateTex);
		inspectorContentBgAlternate.minWidth = 4;
		inspectorContentBgAlternate.minHeight = 6;
		inspectorContentBgAlternate.border.left = 2;
		inspectorContentBgAlternate.border.right = 2;
		inspectorContentBgAlternate.border.top = 2;
		inspectorContentBgAlternate.border.bottom = 4;

		skin->setStyle("InspectorContentBgAlternate", inspectorContentBgAlternate);

		// Background for multi-element resource entries in the library window
		GUIElementStyle libraryEntryFirstBg;
		libraryEntryFirstBg.normal.texture = getGUITexture(LibraryEntryFirstBgTex);
		libraryEntryFirstBg.minHeight = 7;
		libraryEntryFirstBg.minWidth = 4;
		libraryEntryFirstBg.border.top = 5;
		libraryEntryFirstBg.border.bottom = 2;
		libraryEntryFirstBg.border.left = 2;

		skin->setStyle("LibraryEntryFirstBg", libraryEntryFirstBg);

		GUIElementStyle libraryEntryBg;
		libraryEntryBg.normal.texture = getGUITexture(LibraryEntryBgTex);
		libraryEntryBg.minHeight = 7;
		libraryEntryBg.minWidth = 4;
		libraryEntryBg.border.top = 5;
		libraryEntryBg.border.bottom = 2;

		skin->setStyle("LibraryEntryBg", libraryEntryBg);

		GUIElementStyle libraryEntryLastBg;
		libraryEntryLastBg.normal.texture = getGUITexture(LibraryEntryLastBgTex);
		libraryEntryLastBg.minHeight = 7;
		libraryEntryFirstBg.minWidth = 4;
		libraryEntryLastBg.border.top = 5;
		libraryEntryLastBg.border.bottom = 2;
		libraryEntryLastBg.border.right = 2;

		skin->setStyle("LibraryEntryLastBg", libraryEntryLastBg);

		GUIElementStyle libraryEntryVertFirstBg;
		libraryEntryVertFirstBg.normal.texture = getGUITexture(LibraryEntryVertFirstBgTex);
		libraryEntryVertFirstBg.minHeight = 5;
		libraryEntryVertFirstBg.minWidth = 6;
		libraryEntryVertFirstBg.border.top = 4;
		libraryEntryVertFirstBg.border.left = 2;
		libraryEntryVertFirstBg.border.right = 4;

		skin->setStyle("LibraryEntryVertFirstBg", libraryEntryVertFirstBg);

		GUIElementStyle libraryEntryVertBg;
		libraryEntryVertBg.normal.texture = getGUITexture(LibraryEntryVertBgTex);
		libraryEntryVertBg.minHeight = 4;
		libraryEntryVertBg.minWidth = 6;
		libraryEntryVertBg.border.left = 2;
		libraryEntryVertBg.border.right = 4;

		skin->setStyle("LibraryEntryVertBg", libraryEntryVertBg);

		GUIElementStyle libraryEntryVertLastBg;
		libraryEntryVertLastBg.normal.texture = getGUITexture(LibraryEntryVertLastBgTex);
		libraryEntryVertLastBg.minHeight = 4;
		libraryEntryVertLastBg.minWidth = 6;
		libraryEntryVertLastBg.border.bottom = 2;
		libraryEntryVertLastBg.border.left = 2;
		libraryEntryVertLastBg.border.right = 4;

		skin->setStyle("LibraryEntryVertLastBg", libraryEntryVertLastBg);

		GUIElementStyle canvas;
		skin->setStyle("Canvas", canvas);

		return skin;
	}

	HSpriteTexture BuiltinEditorResources::getGUITexture(const String& name) const
	{
		Path texturePath = EditorSkinSpritesFolder;
		texturePath.append("sprite_" + name + ".asset");

		return gResources().load<SpriteTexture>(texturePath);
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