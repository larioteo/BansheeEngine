# Source files and their filters
include(CMakeSources.cmake)
	
# Target
if(WIN32)
	add_executable(Banshee3D WIN32 ${BS_BANSHEE3D_SRC})
else()
	add_executable(Banshee3D ${BS_BANSHEE3D_SRC})
endif()

# Common flags
add_common_flags(Banshee3D)

# Includes
target_include_directories(Banshee3D PRIVATE "./")

# Libraries
## Local libs
target_link_libraries(Banshee3D EditorCore bsf)

# IDE specific
set_property(TARGET Banshee3D PROPERTY FOLDER Executable)

# Plugin dependencies
add_engine_dependencies(Banshee3D)
add_dependencies(Banshee3D bsfFBXImporter bsfFontImporter bsfFreeImgImporter EditorScript MonoExec)

# Compiler flags
if(MSVC)
	target_compile_options(Banshee3D PUBLIC /wd4509)
endif()

# Make sure `bsf` dlls are copied to our folders
install_dll_on_build(Banshee3D ${BSF_DIRECTORY})