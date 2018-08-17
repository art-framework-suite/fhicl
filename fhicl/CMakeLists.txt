include(CetMake)

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

set( ANTLR4CPP_JAR_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/antlr/antlr-4.7.1-complete.jar )
set( ANTLR4CPP_GENERATED_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR})
include( ExternalAntlr4Cpp )
message(STATUS "ANTLR4CPP_INCLUDE_DIRS = " ${ANTLR4CPP_INCLUDE_DIRS})

include_directories( ${ANTLR4CPP_INCLUDE_DIRS} )
link_directories( ${ANTLR4CPP_LIBS} )
message(STATUS "ANTLR4CPP_INCLUDE_DIRS = " ${ANTLR4CPP_INLCUDE_DIRS} ) 

antlr4cpp_process_grammar(fhicl fhiclcppantlr
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar/fhicl.g4 #if split, lexer goes here
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar/fhicl.g4 #if split, parser goes here
)

include_directories(${antlr4cpp_include_dirs_fhiclcppantlr})

add_executable(fhiclcpp_antlr fhiclMain.cpp ${antlr4cpp_src_files_fhiclcppantlr})
add_dependencies(fhiclcpp_antlr antlr4cpp antlr4cpp_generation_fhiclcppantlr)
target_link_libraries(fhiclcpp_antlr antlr4-runtime)

cet_make(
  LIBRARIES
  cetlib
  cetlib_except
  hep_concurrency
  ${SQLITE3}
  WITH_STATIC_LIBRARY
  SUBDIRS
  fhiclcpp
  detail
  #types
  #types/detail
  )

install_headers(SUBDIRS detail types types/detail)
install_source(SUBDIRS detail types types/detail)
# Testing
# add_subdirectory(test)

