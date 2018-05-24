cmake_minimum_required (VERSION 3.9.0)
project (Banshee3D)

set (BSF_SOURCE_DIR ${PROJECT_SOURCE_DIR}/Source/bsf/Source)
set (APP_ROOT_DIR ${PROJECT_SOURCE_DIR})
set (BS_IS_BANSHEE3D 1)

# Grab BSF
find_path(SUBMODULE_SOURCES "Source/Foundation/bsfEngine/BsApplication.h" "Source/bsf/")
if(NOT SUBMODULE_SOURCES)
	execute_process(COMMAND git submodule update 
						--init 
						-- Source/bsf
					WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
else()
	execute_process(COMMAND git submodule update
						-- Source/bsf
					WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()
mark_as_advanced(SUBMODULE_SOURCES)

include(${BSF_SOURCE_DIR}/CMake/Properties.cmake)
include(${BSF_SOURCE_DIR}/CMake/FindPackageOrBuild.cmake)
include(${BSF_SOURCE_DIR}/CMake/HelperMethods.cmake)

add_subdirectory(${BSF_SOURCE_DIR})

set (BS_PREBUILT_DEPENDENCIES_VERSION 24)
set (BS_SRC_DEPENDENCIES_VERSION 15)
set (BS_BUILTIN_ASSETS_VERSION 5)

# Options
set(GENERATE_SCRIPT_BINDINGS OFF CACHE BOOL "If true, script binding files will be generated. Script bindings are required for the project to build properly, however they take a while to generate. If you are sure the script bindings are up to date, you can turn off their generation (temporarily) to speed up the build.")

# Ensure dependencies are up to date
## Check prebuilt dependencies that are downloaded in a .zip
check_and_update_binary_deps(Banshee ${PROJECT_SOURCE_DIR}/Dependencies/ ${BS_PREBUILT_DEPENDENCIES_VERSION})

## Check data dependencies
check_and_update_builtin_assets(Banshee ${PROJECT_SOURCE_DIR}/Data ${BS_BUILTIN_ASSETS_VERSION} YES)
	
# Generate script bindings
include(${BSF_SOURCE_DIR}/CMake/GenerateScriptBindings.cmake)
	
# Sub-directories
add_subdirectory(Source/EditorCore)

## Script interop
add_subdirectory(${BSF_SOURCE_DIR}/Plugins/bsfMono)
add_subdirectory(Source/Scripting/SBansheeEngine)
add_subdirectory(Source/Scripting/SBansheeEditor)

## Executables
add_subdirectory(Source/Banshee3D)
add_subdirectory(Source/Game)

## Managed projects
set(CS_ENGINE_PROJ ${PROJECT_SOURCE_DIR}/Source/Scripting/MBansheeEngine/MBansheeEngine.csproj)
set(CS_EDITOR_PROJ ${PROJECT_SOURCE_DIR}/Source/Scripting/MBansheeEditor/MBansheeEditor.csproj)

if(MSVC)
	include_external_msproject(MBansheeEngine ${CS_ENGINE_PROJ})
	include_external_msproject(MBansheeEditor ${CS_EDITOR_PROJ})
	
	set_target_properties(MBansheeEngine PROPERTIES
	  MAP_IMPORTED_CONFIG_RELEASE OptimizedDebug
	)
	set_target_properties(MBansheeEditor PROPERTIES
	  MAP_IMPORTED_CONFIG_RELEASE OptimizedDebug
	)
	
	set_property(TARGET MBansheeEngine PROPERTY FOLDER Script)
	set_property(TARGET MBansheeEditor PROPERTY FOLDER Script)

	add_dependencies(Banshee3D MBansheeEngine MBansheeEditor)
	add_dependencies(Game MBansheeEngine)

	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Banshee3D)
else()
	find_package(mcs)

	if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		set(CS_PROJ_CONFIG Debug)
	else()
		set(CS_PROJ_CONFIG Release)
	endif()

	add_custom_target(BuildManaged
			COMMAND xbuild /p:Configuration=${CS_PROJ_CONFIG} ${CS_EDITOR_PROJ}
			COMMENT "Building managed assemblies")

	add_dependencies(Banshee3D BuildManaged)
	add_dependencies(Game BuildManaged)
endif()