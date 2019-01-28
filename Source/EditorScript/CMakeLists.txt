# Source files and their filters
include(CMakeSources.cmake)

file(GLOB BS_GENERATED_SCRIPT_H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Generated/*.h)
file(GLOB BS_GENERATED_SCRIPT_CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Generated/*.cpp)

# Target
add_library(EditorScript SHARED 
	${BS_EDITORSCRIPT_SRC} 
	${BS_GENERATED_SCRIPT_H_FILES} 
	${BS_GENERATED_SCRIPT_CPP_FILES})

# Common flags
add_common_flags(EditorScript)
	
# Includes
set(EditorScript_INC 
	"./"
	"./Generated")

target_include_directories(EditorScript PRIVATE ${EditorScript_INC})
	
# Defines
target_compile_definitions(EditorScript PRIVATE -DBS_SCR_BED_EXPORTS)

# Libraries
## Local libs
target_link_libraries(EditorScript bsfScript bsfMono EditorCore bsf)

# IDE specific
set_property(TARGET EditorScript PROPERTY FOLDER Script)