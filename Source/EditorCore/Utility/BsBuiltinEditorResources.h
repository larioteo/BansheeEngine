//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsEditorPrerequisites.h"
#include "GUI/BsGUISkin.h"
#include "Utility/BsModule.h"
#include "GUI/BsGUIContent.h"
#include "BsApplication.h"

namespace bs
{
	/** @addtogroup Utility-Editor
	 *  @{
	 */

	/**	Types of valid icons used when viewing the project library. */
	enum class ProjectIcon
	{
		Folder, Mesh, Font, Texture, PlainText, ScriptCode, SpriteTexture, Shader, ShaderInclude, Material, Prefab, GUISkin,
		PhysicsMaterial, PhysicsMesh, AudioClip, AnimationClip
	};

	/**	Types of icons that may be displayed on the tool bar. */
	enum class ToolbarIcon
	{
		NewCamera, NewRenderable, NewPointLight, NewDirLight, NewSpotLight, NewSceneObject, NewCube, NewSphere, NewCone, 
		NewQuad, NewMat, NewCSScript, NewShader, NewSpriteTex, Pause, Play, Step, Undo, Redo, OpenProject, SaveProject, 
		SaveScene
	};

	/**	Types of icons that may be displayed in the scene window. */
	enum class SceneWindowIcon
	{
		View, Move, Rotate, Scale, Pivot, Center, Local, World, MoveSnap, RotateSnap
	};

	/**	Types of icons that may be displayed in the inspector window. */
	enum class InspectorWindowIcon
	{
		Create, Clone, Clear, Resize, Delete, MoveUp, MoveDown, Edit, Apply, Add, Cancel
	};

	/**	Types of icons that may be displayed in the library window. */
	enum class LibraryWindowIcon
	{
		Home, Up, Clear, Options
	};

	/**	Types of icons that may be displayed in the animation editor window. */
	enum class AnimationWindowIcon
	{
		Play, Record, FrameForward, FrameBack, AddKeyframe, AddEvent, Keyframe, Event
	};

	/**	Types of icons used in various areas throughout the editor. */
	enum class EditorIcon
	{
		X, Component, SceneObject
	};

	/**	Types of icons to be used along with log messages depending on their severity. */
	enum class LogMessageIcon
	{
		Info, Warning, Error
	};

	/**	Contains a set of built-in resources used by the editor. */
	class BS_ED_EXPORT BuiltinEditorResources : public bs::Module<BuiltinEditorResources>
	{
	public:
		BuiltinEditorResources();
		~BuiltinEditorResources();

		/**	Returns the default editor GUI skin. */
		const HGUISkin& getSkin() const { return mSkin; }

		/** Returns the default font used by the editor. */
		const HFont& getDefaultFont() const { return mDefaultFont; }

		/** Returns the default antialiased font used by the editor. */
		const HFont& getDefaultAAFont() const { return mDefaultAAFont; }

		/**	Creates a material used for docking drop overlay used by the editor. */
		HMaterial createDockDropOverlayMaterial() const;

		/**	Creates a material used for rendering the scene grid. */
		HMaterial createSceneGridMaterial() const;

		/**	Creates a material used for picking non-transparent objects in scene view. */
		HMaterial createPicking(CullingMode cullMode) const;

		/**	Creates a material used for picking transparent objects in scene view. */
		HMaterial createPickingAlpha(CullingMode cullMode) const;

		/**	Creates a material used for rendering line gizmos. */
		HMaterial createLineGizmoMat() const;

		/**	Creates a material used for rendering solid gizmos. */
		HMaterial createSolidGizmoMat() const;

		/**	Creates a material used for rendering wireframe gizmos. */
		HMaterial createWireGizmoMat() const;

		/**	Creates a material used for rendering icon gizmos. */
		HMaterial createIconGizmoMat() const;

		/**	Creates a material used for picking non-transparent gizmos. */
		HMaterial createGizmoPickingMat() const;

		/**	Creates a material used for picking transparent gizmos. */
		HMaterial createAlphaGizmoPickingMat() const;

		/**	Creates a material used for rendering line handles. */
		HMaterial createLineHandleMat() const;

		/**	Creates a material used for rendering solid handles. */
		HMaterial createSolidHandleMat() const;

		/** Creates a material used for rendering text for gizmos and handles. */
		HMaterial createTextGizmoMat() const;

		/** Creates a material used for clearing the alpha channel of the handle rendering texture. */
		HMaterial createHandleClearAlphaMat() const;

		/**	Creates a material used for displaying selected objects. */
		HMaterial createSelectionMat() const;

		/**
		 * Retrieves an icon that represents a specific resource type that may be displayed when viewing the project 
		 * library.
		 */
		HSpriteTexture getLibraryIcon(ProjectIcon icon, int size) const;

		/**	Retrieves an icon that may be displayed on the main window's toolbar. */
		HSpriteTexture getToolbarIcon(ToolbarIcon icon) const;

		/**	Retrieves an icon that may be displayed on the scene window. */
		GUIContentImages getSceneWindowIcon(SceneWindowIcon icon) const;

		/**	Retrieves an icon that may be displayed on the library window. */
		HSpriteTexture getLibraryWindowIcon(LibraryWindowIcon icon) const;

		/**	Retrieves an icon that may be displayed on the inspector window. */
		HSpriteTexture getInspectorWindowIcon(InspectorWindowIcon icon) const;

		/**	Retrieves an icon that may be displayed on the animation editor window. */
		GUIContentImages getAnimationWindowIcon(AnimationWindowIcon icon) const;

		/**	Retrieves an icon that represents a specific generic editor icon. */
		HSpriteTexture getIcon(EditorIcon icon) const;

		/**	Retrieves an icon that represents a specific log message type. */
		HSpriteTexture getLogMessageIcon(LogMessageIcon icon, UINT32 size, bool dark) const;

		/**	Returns text contained in the default "empty" shader. */
		String getEmptyShaderCode() const;

		/**	Returns text contained in the default "empty" C# script. */
		String getEmptyCSScriptCode() const;

		/**	Returns image data the Banshee Engine splash screen. */
		static SPtr<PixelData> getSplashScreen();

		/**	Returns absolute path to the builtin shader include folder. */
		static Path getShaderIncludeFolder();

		/**	Returns absolute path to the default widget layout file. */
		static Path getDefaultWidgetLayoutPath();

		static const String ObjectFieldStyleName;
		static const String ObjectFieldLabelStyleName;
		static const String ObjectFieldDropBtnStyleName;
		static const String ObjectFieldClearBtnStyleName;

		static const String TextureFieldStyleName;
		static const String TextureFieldLabelStyleName;
		static const String TextureFieldDropStyleName;
		static const String TextureFieldClearBtnStyleName;

	private:
		/**
		 * Imports all necessary resources and converts them to engine-ready format.
		 *
		 * @note	
		 * Normally you only want to use this during development phase and then ship with engine-ready format only.
		 */
		void preprocess(bool forceImport, time_t lastUpdateTime);

		/**	Generates the default editor skin and all GUI element styles. */
		SPtr<GUISkin> generateGUISkin();

		/**	Loads a GUI skin texture with the specified filename. */
		HSpriteTexture getGUITexture(const String& name) const;

		/**	Loads a GUI icon with the specified filename. */
		HSpriteTexture getGUIIcon(const String& name) const;

		/**	Loads a shader with the specified filename */
		HShader getShader(const String& name) const;

		HShader mShaderDockOverlay;
		HShader mShaderSceneGrid;
		HShader mShaderPicking[3];
		HShader mShaderPickingAlpha[3];
		HShader mShaderGizmoSolid;
		HShader mShaderGizmoWire;
		HShader mShaderGizmoLine;
		HShader mShaderGizmoIcon;
		HShader mShaderGizmoPicking;
		HShader mShaderGizmoAlphaPicking;
		HShader mShaderGizmoText;
		HShader mShaderHandleSolid;
		HShader mShaderHandleLine;
		HShader mShaderHandleClearAlpha;
		HShader mShaderSelection;

		HFont mDefaultFont;
		HFont mDefaultAAFont;
		HGUISkin mSkin;

		SPtr<ResourceManifest> mResourceManifest;

		static const char* DataListFile;
		static const char* ShaderFolder;
		static const char* SkinFolder;
		static const char* IconFolder;
		static const char* ShaderIncludeFolder;
		static const char* SpriteSubFolder;

		Path BuiltinDataFolder;
		Path EditorSkinFolder;
		Path EditorSkinSpritesFolder;
		Path EditorIconFolder;
		Path EditorIconSpritesFolder;
		Path EditorShaderFolder;
		Path EditorShaderIncludeFolder;

		Path BuiltinRawDataFolder;
		Path EditorRawSkinFolder;
		Path EditorRawIconsFolder;
		Path EditorRawShaderIncludeFolder;
		Path EditorRawShaderFolder;

		Path ResourceManifestPath;

		static const String DefaultFontFilename;
		static const String DefaultAAFontFilename;
		static const UINT32 DefaultFontSize;
		static const UINT32 TitleFontSize;

		static const Color TextNormalColor;
		static const Color TextActiveColor;

		static const String GUISkinFile;

		static const String FolderIconTex;
		static const String MeshIconTex;
		static const String TextureIconTex;
		static const String FontIconTex;
		static const String PlainTextIconTex;
		static const String ScriptCodeIconTex;
		static const String ShaderIconTex;
		static const String ShaderIncludeIconTex;
		static const String MaterialIconTex;
		static const String SpriteTextureIconTex;
		static const String PrefabIconTex;
		static const String GUISkinIconTex;
		static const String PhysicsMaterialIconTex;
		static const String PhysicsMeshIconTex;
		static const String AudioClipIconTex;
		static const String AnimationClipIconTex;

		static const String WindowBackgroundTex;

		static const String WindowFrameNormal;
		static const String WindowFrameFocused;

		static const String TabBarBackgroundTex;
		static const String TitleBarBackgroundTex;

		static const String CloseButtonNormalTex;
		static const String CloseButtonHoverTex;
		static const String CloseButtonActiveTex;

		static const String MinButtonNormalTex;
		static const String MinButtonHoverTex;
		static const String MinButtonActiveTex;

		static const String MaxButtonNormalTex;
		static const String MaxButtonHoverTex;
		static const String MaxButtonActiveTex;

		static const String TabButtonNormalTex;
		static const String TabButtonFocusedTex;

		static const String ButtonNormalTex;
		static const String ButtonHoverTex;
		static const String ButtonActiveTex;

		static const String ButtonLeftNormalTex;
		static const String ButtonLeftHoverTex;
		static const String ButtonLeftActiveTex;

		static const String ButtonRightNormalTex;
		static const String ButtonRightHoverTex;
		static const String ButtonRightActiveTex;

		static const String ToggleNormalTex;
		static const String ToggleHoverTex;
		static const String ToggleNormalOnTex;
		static const String ToggleHoverOnTex;

		static const String ObjectDropBtnNormalTex;
		static const String ObjectDropBtnNormalOnTex;
		static const String ObjectClearBtnNormalTex;
		static const String ObjectClearBtnHoverTex;
		static const String ObjectClearBtnActiveTex;

		static const String SliderHBackgroundTex;
		static const String SliderHFillTex;
		static const String SliderVBackgroundTex;
		static const String SliderVFillTex;
		static const String SliderHandleNormalTex;
		static const String SliderHandleHoverTex;
		static const String SliderHandleActiveTex;

		static const String FoldoutOpenNormalTex;
		static const String FoldoutOpenHoverTex;
		static const String FoldoutOpenActiveTex;
		static const String FoldoutClosedNormalTex;
		static const String FoldoutClosedHoverTex;
		static const String FoldoutClosedActiveTex;

		static const String InputBoxNormalTex;
		static const String InputBoxHoverTex;
		static const String InputBoxFocusedTex;

		static const String ScrollBarUpNormalTex;
		static const String ScrollBarUpHoverTex;
		static const String ScrollBarUpActiveTex;

		static const String ScrollBarDownNormalTex;
		static const String ScrollBarDownHoverTex;
		static const String ScrollBarDownActiveTex;

		static const String ScrollBarLeftNormalTex;
		static const String ScrollBarLeftHoverTex;
		static const String ScrollBarLeftActiveTex;

		static const String ScrollBarRightNormalTex;
		static const String ScrollBarRightHoverTex;
		static const String ScrollBarRightActiveTex;

		static const String ScrollBarHandleHorzNormalTex;
		static const String ScrollBarHandleHorzHoverTex;
		static const String ScrollBarHandleHorzActiveTex;

		static const String ScrollBarHandleVertNormalTex;
		static const String ScrollBarHandleVertHoverTex;
		static const String ScrollBarHandleVertActiveTex;

		static const String ScrollBarResizeableHandleHorzNormalTex;
		static const String ScrollBarResizeableHandleHorzHoverTex;
		static const String ScrollBarResizeableHandleHorzActiveTex;

		static const String ScrollBarResizeableHandleVertNormalTex;
		static const String ScrollBarResizeableHandleVertHoverTex;
		static const String ScrollBarResizeableHandleVertActiveTex;

		static const String ScrollBarHBgTex;
		static const String ScrollBarVBgTex;

		static const String DropDownBtnNormalTex;
		static const String DropDownBtnHoverTex;
		static const String DropDownBtnActiveTex;

		static const String DropDownBoxBgTex;
		static const String DropDownBoxSideBgTex;
		static const String DropDownBoxHandleTex;

		static const String DropDownBoxEntryNormalTex;
		static const String DropDownBoxEntryHoverTex;

		static const String DropDownBoxEntryToggleNormalTex;
		static const String DropDownBoxEntryToggleHoverTex;
		static const String DropDownBoxEntryToggleNormalOnTex;
		static const String DropDownBoxEntryToggleHoverOnTex;

		static const String DropDownBoxBtnUpNormalTex;
		static const String DropDownBoxBtnUpHoverTex;

		static const String DropDownBoxBtnDownNormalTex;
		static const String DropDownBoxBtnDownHoverTex;

		static const String DropDownBoxEntryExpNormalTex;
		static const String DropDownBoxEntryExpHoverTex;

		static const String DropDownSeparatorTex;

		static const String MenuBarBgTex;
		static const String MenuBarBansheeLogoTex;

		static const String MenuBarBtnNormalTex;
		static const String MenuBarBtnHoverTex;
		static const String MenuBarBtnActiveTex;

		static const String MenuBarLineNormalTex;
		static const String MenuBarLineActiveTex;

		static const String ToolBarBtnNormalTex;
		static const String ToolBarBtnHoverTex;
		static const String ToolBarBtnActiveTex;

		static const String ToolBarSeparatorTex;

		static const String TreeViewExpandButtonOffNormal;
		static const String TreeViewExpandButtonOffHover;
		static const String TreeViewExpandButtonOnNormal;
		static const String TreeViewExpandButtonOnHover;

		static const String TreeViewHighlightBackground;
		static const String TreeViewEditBox;

		static const String TreeViewElementHighlight;
		static const String TreeViewElementSepHighlight;

		static const String ColorPickerSliderHorzHandleTex;
		static const String ColorPickerSliderVertHandleTex;
		static const String ColorPickerSlider2DHandleTex;

		static const String ProgressBarFillTex;
		static const String ProgressBarBgTex;

		static const String SelectionAreaTex;
		static const String SelectionBgTex;

		static const String TextureDropTex;
		static const String TextureDropOnTex;

		static const String XButtonNormalTex;
		static const String XButtonHoverTex;
		static const String XButtonActiveTex;

		static const String StatusBarBgTex;
		static const String ScrollAreaBgTex;

		static const String InspectorTitleBgTex;
		static const String InspectorContentBgTex;
		static const String InspectorContentBgAlternateTex;

		static const String LibraryEntryFirstBgTex;
		static const String LibraryEntryBgTex;
		static const String LibraryEntryLastBgTex;

		static const String LibraryEntryVertFirstBgTex;
		static const String LibraryEntryVertBgTex;
		static const String LibraryEntryVertLastBgTex;

		static const String ShaderDockOverlayFile;
		static const String ShaderSceneGridFile;
		static const String ShaderPickingCullNoneFile;
		static const String ShaderPickingCullCWFile;
		static const String ShaderPickingCullCCWFile;
		static const String ShaderPickingAlphaCullNoneFile;
		static const String ShaderPickingAlphaCullCWFile;
		static const String ShaderPickingAlphaCullCCWFile;
		static const String ShaderLineGizmoFile;
		static const String ShaderSolidGizmoFile;
		static const String ShaderWireGizmoFile;
		static const String ShaderLineHandleFile;
		static const String ShaderSolidHandleFile;
		static const String ShaderHandleClearAlphaFile;
		static const String ShaderIconGizmoFile;
		static const String ShaderGizmoPickingFile;
		static const String ShaderGizmoPickingAlphaFile;
		static const String ShaderTextGizmoFile;
		static const String ShaderSelectionFile;

		static const String EmptyShaderCodeFile;
		static const String EmptyCSScriptCodeFile;

		static const char* SplashScreenName;
	};

	/** @} */
}