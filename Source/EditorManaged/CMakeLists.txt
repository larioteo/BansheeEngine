# Generate the CS project file
generate_csharp_project(${PROJECT_SOURCE_DIR}/Source/EditorManaged MBansheeEditor bs.Editor MBansheeEditor)

# Include the CS project in the build
set(BS_CS_PROJ "MBansheeEditor.csproj")

if(MSVC)
	if(CMAKE_GENERATOR MATCHES "Visual Studio")
		include_external_msproject(MBansheeEditor ${CMAKE_CURRENT_SOURCE_DIR}/${BS_CS_PROJ})
	
		add_dependencies(MBansheeEditor MBansheeEngine)
		set_property(TARGET MBansheeEditor PROPERTY FOLDER Script)
	else()
		# Generator expressions don't support 'A' else 'B', otherwise
		# this could be simplified to 'Debug' else 'Release'.
		# Another possible improvement for this would be if we support
		# all configuration types (e.g. RelWithDebInfo, etc) in MBansheeEditor
		# then we could use $<CONFIG>
		add_custom_target(MBansheeEditor
				COMMAND msbuild /p:Configuration=$<$<CONFIG:Debug>:Debug>$<$<NOT:$<CONFIG:Debug>>:Release> ${CMAKE_CURRENT_SOURCE_DIR}/${BS_CS_PROJ}
				COMMENT "Building managed assembly \"MBansheeEditor\"")
	endif()
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