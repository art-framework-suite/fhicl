
execute_process( COMMAND date
                 OUTPUT_VARIABLE datime
                 OUTPUT_STRIP_TRAILING_WHITESPACE )

process_ups_files()

configure_file ( ${fhicl_SOURCE_DIR}/ups/FhiclCmake-config.cmake.in
                 ${fhicl_BINARY_DIR}/ups/FhiclCmake-config.cmake @ONLY )
configure_file ( ${fhicl_SOURCE_DIR}/ups/FhiclCmake-config-version.cmake.in
                 ${fhicl_BINARY_DIR}/ups/FhiclCmake-config-version.cmake @ONLY )

install (FILES ${fhicl_BINARY_DIR}/ups/FhiclCmake-config.cmake
               ${fhicl_BINARY_DIR}/ups/FhiclCmake-config-version.cmake
         DESTINATION ${flavorqual_dir}/lib/FhiclCmake-${version} )

