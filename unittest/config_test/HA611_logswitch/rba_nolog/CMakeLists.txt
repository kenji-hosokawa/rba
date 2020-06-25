#
# Log Off Make
#

cmake_minimum_required(VERSION 3.5.1)
project(rba_nolog)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)	# without compiler extensions like gnu++11
find_package(Threads REQUIRED)

set(TOPDIR ../../../..)

enable_testing()
set(GTEST_DIR ${TOPDIR}/unittest/googletest/googletest)
set(GTEST_INCLUDE_DIRS ${GTEST_DIR}/include)
set(GTEST_LIBRARY_DIRS ${GTEST_DIR})

set(UTPATH ${TOPDIR}/unittest)

include_directories(
  ${TOPDIR}/include/rba
  ${TOPDIR}/include/model
  ${TOPDIR}/src
  ${TOPDIR}/unittest/gen/src
  ${GTEST_INCLUDE_DIRS}
  )
link_directories(${GTEST_LIBRARY_DIRS})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})

file(GLOB rba_files ${TOPDIR}/src/*.cpp)
file(GLOB ut_files
  ${TOPDIR}/unittest/logic_test/*.cpp
  ${TOPDIR}/unittest/api_test/*.cpp
  ${TOPDIR}/unittest/internal_test/*.cpp
  )
add_definitions("-Wall -g")
add_definitions(-DUTPATH="${UTPATH}")
#add_definitions(-DRBA_USE_LOG)
add_library(rba_nolog STATIC ${rba_files})
target_link_libraries(rba_nolog Threads::Threads)
add_executable(ut_nolog main.cpp ${ut_files})
target_link_libraries(ut_nolog rba_nolog)
target_link_libraries(ut_nolog gtest)
target_link_libraries(ut_nolog ${CMAKE_THREAD_LIBS_INIT})

# DEBUG cmake
if(DEBUG_CMAKE)
message(STATUS "*** dump start cmake variables ***")
get_cmake_property(_variableNames VARIABLES)
foreach(_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
message(STATUS "*** dump end ***")
endif(DEBUG_CMAKE)

# end of file
