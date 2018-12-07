# Source files and their filters
include(CMakeSources.cmake)

source_group("Header Files\\Generated" FILES ${BS_GENERATED_ENGINE_H_FILES})
source_group("Source Files\\Generated" FILES ${BS_GENERATED_ENGINE_CPP_FILES})

# Target
add_library(SBansheeEngine SHARED 
	${BS_SBANSHEEENGINE_SRC}
	${BS_GENERATED_ENGINE_H_FILES} 
	${BS_GENERATED_ENGINE_CPP_FILES})

# Common flags
add_common_flags(SBansheeEngine)
	
# Includes
set(SBansheeEngine_INC 
	"./"
	"./Generated")

target_include_directories(SBansheeEngine PUBLIC ${SBansheeEngine_INC})
	
# Defines
target_compile_definitions(SBansheeEngine PRIVATE -DBS_SCR_BE_EXPORTS)

# Libraries
## Local libs
target_link_libraries(SBansheeEngine bsfMono bsf)

# IDE specific
set_property(TARGET SBansheeEngine PROPERTY FOLDER Script)