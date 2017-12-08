# 2015: Written by Vincent Berthier (vincent.berthier@inria.fr)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(ctga)
SET(EXEC_NAME "worker")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

## CONFIG #####################################################################
macro (add_sources)
  file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
  foreach (_src ${ARGN})
    if (_relPath)
      list (APPEND SOURCES "${_relPath}/${_src}")
    else()
      list (APPEND SOURCES "${_src}")
    endif()
  endforeach()
  if (_relPath)
    # propagate SRCS to parent directory
    set (SOURCES ${SOURCES} PARENT_SCOPE)
  endif()
endmacro()
macro (add_headers)
  file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
  #string(REPLACE "src/" "" _docPath ${_relPath})
  foreach (_src ${ARGN})
    if (_relPath)
      list (APPEND HEADERS "${_relPath}/${_src}")
      list (APPEND DOC_HEADERS "${_docPath}/${_src}")
    else()
      list (APPEND HEADERS "${_src}")
      list (APPEND DOC_HEADERS "${_src}")
    endif()
  endforeach()
  if (_relPath)
    # propagate SRCS to parent directory
    set (HEADERS ${HEADERS} PARENT_SCOPE)
    set (DOC_HEADERS ${DOC_HEADERS} PARENT_SCOPE)
  endif()
endmacro()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

MESSAGE(STATUS "----------------------------------------")

###########################################################
##                 Compilation flags                     ##
###########################################################


#option(GENERATE_PROFILE "Generate a profile while running the application" OFF)
#option(USE_PROFILE "Use a generated profile to guide compilation")

define_property(GLOBAL
  PROPERTY DEFINITIONS
  BRIEF_DOCS "Preprocessor definitions"
  FULL_DOCS "Preprocessor definitions used to exclude some functionalities such as testbeds.")

# Check that compiler supports C++17 (required)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTSuu_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

if(COMPILER_SUPPORTS_CXX11)
  message(STATUS "Compiler supports C++17")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
elseif (COMPILER_SUPPORTS_CXX0X)
  message(STATUS "Compiler supports C++11")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  message(FATAL_ERROR "Your compiler doesn't support C++17 nor C++11. Please use a different compiler.")
endif(COMPILER_SUPPORTS_CXX11)

# Set general compilation flags
#set(GENERAL_FLAGS "-Wall -Wno-deprecated")
set(GENERAL_FLAGS "-pedantic -Wall -Wno-deprecated -fno-omit-frame-pointer -Wno-deprecated-declarations")
set(DEBUG_FLAGS "-g")
set(RELEASE_FLAGS "-O3")
set(LINKER_FLAGS "-Wl,--no-as-needed")
set(STATIC_FLAGS "-static -static-libstdc++ -fPIE")

# Set compilation flags based on compiler
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  set(COMPILER_RELEASE_FLAGS "-fast -ansi-alias -wd3180,1478,10237")
  set(COMPILER_STATIC "-static-intel")
  execute_process(COMMAND source compilervars.sh intel64)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(LINKER_FLAGS "${LINKER_FLAGS} -flto")
else()
  set(COMPILER_RELEASE_FLAGS "-Wextra -march=native -pipe -msse3")
  set(COMPILER_STATIC "-static-libgcc")
endif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")

# Static compilation of the libraries & programs
option(STATIC "Enable static compilation" OFF)
if(STATIC)
  define_property(GLOBAL PROPERTY STATIC BRIEF_DOCS "Static Build" FULL_DOCS "ON if static build, off otherwise")
  set(Boost_USE_STATIC_LIBS ON)
  set(BUILD_SHARED_LIBS OFF)
  set(LINKER_FLAGS "${LINKER_FLAGS} ${STATIC_FLAGS} ${COMPILER_STATIC} -Wl,--no-export-dynamic")
  set(GENERAL_FLAGS "${GENERAL_FLAGS} -fPIE")
  set(BUILD_SHARED_LIBS OFF)
else()
  set(LINKER_FLAGS "${LINKER_FLAGS} -fPIC")
  set(GENERAL_FLAGS "${GENERAL_FLAGS} -fPIC")
  add_definitions(-DBOOST_LOG_DYN_LINK)
  set(BUILD_SHARED_LIBS ON)
endif(STATIC)

# Aggregate flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GENERAL_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GENERAL_FLAGS}")
if(${CMAKE_BUILD_TYPE} STREQUAL "RELEASE")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${RELEASE_FLAGS} ${COMPILER_RELEASE_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RELEASE_FLAGS} ${COMPILER_RELEASE_FLAGS}")
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEBUG_FLAGS} ${COMPILER_DEBUG_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_FLAGS} ${COMPILER_DEBUG_FLAGS}")
endif(${CMAKE_BUILD_TYPE} STREQUAL "RELEASE")
set(CMAKE_CXX_FLAGS_DEBUG "${DEBUG_FLAGS} ${COMPILER_DEBUG_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LINKER_FLAGS}")

# Print selected flags
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS=${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "CMAKE_MODULE_LINKER_FLAGS=${CMAKE_MODULE_LINKER_FLAGS}")



###########################################################
##                     Libraries                         ##
###########################################################

# GNU Scientific Library
find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIRS})

# Eigen 3
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Boost
set(Boost_USE_MULTITHREADED TRUE)
find_package(Boost REQUIRED COMPONENTS system thread log filesystem date_time regex program_options)
include_directories(${Boost_INCLUDE_DIRS})

message(STATUS "All libraries were found.")

###########################################################
##                    Compilation                        ##
###########################################################

set(BASEPATH ${CMAKE_SOURCE_DIR})
INCLUDE_DIRECTORIES("${BASEPATH}")

ADD_SUBDIRECTORY(ctga)

# Propagate definitions
get_property(DEFINITIONS_VALUES GLOBAL PROPERTY DEFINITIONS)
add_definitions(${DEFINITIONS_VALUES})

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${GSL_LIBRARIES} pthread rt)

# Multi-threaded binary
add_executable(${EXEC_NAME} "ctga/main.cpp" ${HEADERS})
target_link_libraries(${EXEC_NAME} ${PROJECT_NAME} rt)
