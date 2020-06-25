#
# rba unit test
#

cmake_minimum_required(VERSION 3.1)
project(unittest_rba)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)	# without compiler extensions like gnu++11
find_package(Threads REQUIRED)

set(TOPDIR ${CMAKE_HOME_DIRECTORY}/..)

set(GTEST_DIR ${TOPDIR}/unittest/googletest/googletest)
set(GTEST_INCLUDE_DIRS ${GTEST_DIR}/include)
set(GTEST_LIBRARY_DIRS ${GTEST_DIR})

include_directories(
  ${TOPDIR}/include/rba
  ${TOPDIR}/include/model
  ${TOPDIR}/src/core/logic
  ${TOPDIR}/src/core/model
  ${TOPDIR}/src/core/expression
  ${TOPDIR}/src/factory
  ${TOPDIR}/src/log
  ${TOPDIR}/src/optimize
  ${TOPDIR}/src/public
  ${TOPDIR}/src/sound
  ${TOPDIR}/src/view
  ${TOPDIR}/src/animation
  ${GTEST_INCLUDE_DIRS}
  )

link_directories(
  ${GTEST_LIBRARY_DIRS}
  ${TOPDIR}/lib
  )

file(GLOB UT_FILES
  ${TOPDIR}/unittest/logic_test/*.cpp
  ${TOPDIR}/unittest/api_test/*.cpp
  ${TOPDIR}/unittest/internal_test/*.cpp
  )

if(USE_GCOV)
  set(EXEC_NAME ${PROJECT_NAME}_gcov)
  add_definitions(-fprofile-arcs -ftest-coverage)
  set(CMAKE_EXE_LINKER_FLAGS "--coverage")
else()
  set(EXEC_NAME ${PROJECT_NAME})
endif(USE_GCOV)

if(WIN32)
  add_definitions(/source-charset:utf-8)
  add_definitions(/MP9)
  set(CompilerFlags
    CMAKE_CXX_FLAGS
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_C_FLAGS
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_RELEASE
    )
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
else()
  add_definitions("-Wall -g -pthread")
  if(NOLOG)
  else()
    add_definitions(-DRBA_USE_LOG)
  endif(NOLOG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY})
endif(WIN32)

add_executable(${EXEC_NAME} main.cpp ${UT_FILES})
if(WIN32)
  target_link_libraries(${EXEC_NAME} gtest rba)
else()
  if(USE_GCOV)
    target_link_libraries(${EXEC_NAME} gtest rba_gcov pthread)
  else()
    target_link_libraries(${EXEC_NAME} gtest rba pthread)
  endif(USE_GCOV)
endif(WIN32)

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
