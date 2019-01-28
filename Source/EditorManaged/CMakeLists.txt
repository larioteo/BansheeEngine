# Generate the CS project file
generate_csharp_project(${PROJECT_SOURCE_DIR}/Source/EditorManaged MBansheeEditor BansheeEditor MBansheeEditor)

# Include the CS project in the build
set(BS_CS_PROJ "MBansheeEditor.csproj")

if(MSVC)
	include_external_msproject(MBansheeEditor ${CMAKE_CURRENT_SOURCE_DIR}/${BS_CS_PROJ})
	set_property(TARGET MBansheeEditor PROPERTY FOLDER Script)
else()
	find_package(mcs)

	if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		set(CS_PROJ_CONFIG Debug)
	else()
		set(CS_PROJ_CONFIG Release)
	endif()

	add_custom_target(MBansheeEditor
			COMMAND xbuild /p:Configuration=${CS_PROJ_CONFIG} ${BS_CS_PROJ}
			COMMENT "Building managed assembly \"MBansheeEditor\"")
endif()