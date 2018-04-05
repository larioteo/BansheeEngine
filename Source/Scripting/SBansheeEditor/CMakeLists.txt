# Source files and their filters
include(CMakeSources.cmake)

source_group("Header Files\\Generated" FILES ${BS_GENERATED_EDITOR_H_FILES})
source_group("Source Files\\Generated" FILES ${BS_GENERATED_EDITOR_CPP_FILES})

# Target
add_library(SBansheeEditor SHARED 
	${BS_SBANSHEEEDITOR_SRC} 
	${BS_GENERATED_EDITOR_H_FILES} 
	${BS_GENERATED_EDITOR_CPP_FILES})

# Includes
set(SBansheeEditor_INC 
	"./"
	"./Generated")

target_include_directories(SBansheeEditor PRIVATE ${SBansheeEditor_INC})
	
# Defines
target_compile_definitions(SBansheeEditor PRIVATE -DBS_SCR_BED_EXPORTS)

# Libraries
## Local libs
target_link_libraries(SBansheeEditor SBansheeEngine bsfMono EditorCore bsf)

# IDE specific
set_property(TARGET SBansheeEditor PROPERTY FOLDER Script)