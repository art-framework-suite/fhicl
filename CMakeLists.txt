cmake_minimum_required (VERSION ${CMAKE_VERSION})

cmake_policy(VERSION 3.4)

project(fhicl CXX)

include_directories(${CMAKE_BINARY_DIR}/locals)

find_package(cetbuildtools REQUIRED)

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS VIGILANT
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic
  EXTRA_CXX_FLAGS -Wnon-virtual-dtor -Wdelete-non-virtual-dtor -Wno-attributes)

enable_testing()

find_ups_product(fhiclcpp)

subdirs(fhicl)

# testing
subdirs(tests/pass tests/fail)

# ups - table and config files
subdirs(ups)

# This step enables building the package tarball
# packaging utility
include(UseCPack)
