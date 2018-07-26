# CMakeLists.txt

# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

set(ANTLR4CPP_JAR_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/antlr/antlr-4.7.1-complete.jar)
set(ANTLR4CPP_GENERATED_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR})
#add external build for antlrcpp
include( ExternalAntlr4Cpp )
#add antlr4cpp artifacts to project environment
message(STATUS "ANTLR4CPP_INCLUDE_DIRS = " ${ANTLR4CPP_INCLUDE_DIRS})
include_directories( ${ANTLR4CPP_INCLUDE_DIRS} )

link_directories( ${ANTLR4CPP_LIBS} )
message(STATUS "Found antlr4cpp libs: ${ANTLR4CPP_LIBS} and includes: ${ANTLR4CPP_INCLUDE_DIRS} ")


antlr4cpp_process_grammar(fhicl fhiclcppantlr
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar/fhicl.g4
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar/fhicl.g4
)

include_directories(${antlr4cpp_include_dirs_fhiclcppantlr})

add_executable(fhiclcpp_antlr fhiclMain.cpp ${antlr4cpp_src_files_fhiclcppantlr})
add_dependencies(fhiclcpp_antlr antlr4cpp antlr4cpp_generation_fhiclcppantlr)
target_link_libraries(fhiclcpp_antlr antlr4-runtime)
