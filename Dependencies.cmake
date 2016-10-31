# Copyright (c) 2016 Kartik Kumar, Dinamica Srl (me@kartikkumar.com)
# Distributed under the MIT License.
# See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT

# Include script to build external libraries with CMake.
include(ExternalProject)

# -------------------------------

# Catch: https://github.com/philsquared/Catch
# Eigen: http://eigen.tuxfamily.org

if(BUILD_TESTS)
  if(NOT BUILD_DEPENDENCIES)
    find_package(CATCH)
  endif(NOT BUILD_DEPENDENCIES)

  if(NOT CATCH_FOUND)
    message(STATUS "Catch will be downloaded when ${CMAKE_PROJECT_NAME} is built")
    ExternalProject_Add(catch-lib
      PREFIX ${EXTERNAL_PATH}/Catch
      #--Download step--------------
      URL https://github.com/philsquared/Catch/archive/master.zip
      TIMEOUT 30
      #--Update/Patch step----------
      UPDATE_COMMAND ""
      PATCH_COMMAND ""
      #--Configure step-------------
      CONFIGURE_COMMAND ""
      #--Build step-----------------
      BUILD_COMMAND ""
      #--Install step---------------
      INSTALL_COMMAND ""
      #--Output logging-------------
      LOG_DOWNLOAD ON
    )
    ExternalProject_Get_Property(catch-lib source_dir)
    set(CATCH_INCLUDE_DIRS ${source_dir}/include CACHE INTERNAL "Path to include folder for Catch")
  endif(NOT CATCH_FOUND)

  if(NOT APPLE)
    include_directories(SYSTEM AFTER "${CATCH_INCLUDE_DIRS}")
  else(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${CATCH_INCLUDE_DIRS}\"")
  endif(NOT APPLE)

  if(BUILD_TESTS_WITH_EIGEN)
    if(NOT BUILD_DEPENDENCIES)
      find_package(Eigen3)
    endif(NOT BUILD_DEPENDENCIES)

    if(NOT EIGEN3_FOUND)
      message(STATUS "Eigen will be downloaded when ${CMAKE_PROJECT_NAME} is built")
      ExternalProject_Add(eigen-lib
        PREFIX ${EXTERNAL_PATH}/Eigen
        #--Download step--------------
        URL https://bitbucket.org/eigen/eigen/get/3.2.9.zip
        TIMEOUT 60
        #--Update/Patch step----------
        UPDATE_COMMAND ""
        PATCH_COMMAND ""
        #--Configure step-------------
        CONFIGURE_COMMAND ""
        #--Build step-----------------
        BUILD_COMMAND ""
        #--Install step---------------
        INSTALL_COMMAND ""
        #--Output logging-------------
        LOG_DOWNLOAD ON
      )
      ExternalProject_Get_Property(eigen-lib source_dir)
      set(EIGEN3_INCLUDE_DIR ${source_dir} CACHE INTERNAL "Path to include folder for Eigen")
    endif(NOT EIGEN3_FOUND)

    if(NOT APPLE)
      include_directories(SYSTEM AFTER "${EIGEN3_INCLUDE_DIR}")
    else(APPLE)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${EIGEN3_INCLUDE_DIR}\"")
    endif(NOT APPLE)
  endif(BUILD_TESTS_WITH_EIGEN)
endif(BUILD_TESTS)

# -------------------------------

# SML: https://github.com/openastro/sml

if(NOT BUILD_DEPENDENCIES)
  find_package(sml)
endif(NOT BUILD_DEPENDENCIES)

if(NOT SML_FOUND)
  message(STATUS "SML will be downloaded when ${CMAKE_PROJECT_NAME} is built")
  ExternalProject_Add(sml-lib
    PREFIX ${EXTERNAL_PATH}/SML
    #--Download step--------------
    URL https://github.com/openastro/sml/archive/master.zip
    TIMEOUT 30
    #--Update/Patch step----------
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    #--Configure step-------------
    CONFIGURE_COMMAND ""
    #--Build step-----------------
    BUILD_COMMAND ""
    #--Install step---------------
    INSTALL_COMMAND ""
    #--Output logging-------------
    LOG_DOWNLOAD ON
  )
  ExternalProject_Get_Property(sml-lib source_dir)
  set(SML_INCLUDE_DIRS ${source_dir}/include CACHE INTERNAL "Path to include folder for SML")
endif(NOT SML_FOUND)

if(NOT APPLE)
  include_directories(SYSTEM AFTER "${SML_INCLUDE_DIRS}")
else(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${SML_INCLUDE_DIRS}\"")
endif(NOT APPLE)

# -------------------------------

# Astro: https://github.com/openastro/astro

if(NOT BUILD_DEPENDENCIES)
  find_package(astro)
endif(NOT BUILD_DEPENDENCIES)

if(NOT ASTRO_FOUND)
  message(STATUS "Astro will be downloaded when ${CMAKE_PROJECT_NAME} is built")
  ExternalProject_Add(astro-lib
    DEPENDS sml-lib
    PREFIX ${EXTERNAL_PATH}/Astro
    #--Download step--------------
    URL https://github.com/openastro/astro/archive/master.zip
    TIMEOUT 30
    #--Update/Patch step----------
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    #--Configure step-------------
    CONFIGURE_COMMAND ""
    #--Build step-----------------
    BUILD_COMMAND ""
    #--Install step---------------
    INSTALL_COMMAND ""
    #--Output logging-------------
    LOG_DOWNLOAD ON
  )
  ExternalProject_Get_Property(astro-lib source_dir)
  set(ASTRO_INCLUDE_DIRS ${source_dir}/include CACHE INTERNAL "Path to include folder for Astro")
endif(NOT ASTRO_FOUND)

if(NOT APPLE)
  include_directories(SYSTEM AFTER "${ASTRO_INCLUDE_DIRS}")
else(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${ASTRO_INCLUDE_DIRS}\"")
endif(NOT APPLE)

# -------------------------------

# Control: https://github.com/openastro/control

if(NOT BUILD_DEPENDENCIES)
  find_package(control)
endif(NOT BUILD_DEPENDENCIES)

if(NOT CONTROL_FOUND)
  message(STATUS "Control will be downloaded when ${CMAKE_PROJECT_NAME} is built")
  ExternalProject_Add(control-lib
    DEPENDS sml-lib
    PREFIX ${EXTERNAL_PATH}/Control
    #--Download step--------------
    URL https://github.com/openastro/control/archive/master.zip
    TIMEOUT 30
    #--Update/Patch step----------
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    #--Configure step-------------
    CONFIGURE_COMMAND ""
    #--Build step-----------------
    BUILD_COMMAND ""
    #--Install step---------------
    INSTALL_COMMAND ""
    #--Output logging-------------
    LOG_DOWNLOAD ON
  )
  ExternalProject_Get_Property(control-lib source_dir)
  set(CONTROL_INCLUDE_DIRS ${source_dir}/include
      CACHE INTERNAL "Path to include folder for Control")
endif(NOT CONTROL_FOUND)

if(NOT APPLE)
  include_directories(SYSTEM AFTER "${CONTROL_INCLUDE_DIRS}")
else(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${CONTROL_INCLUDE_DIRS}\"")
endif(NOT APPLE)

# -------------------------------

# RapidJSON: https://github.com/miloyip/rapidjson

if(NOT BUILD_DEPENDENCIES)
  find_package(rapidjson)
endif(NOT BUILD_DEPENDENCIES)

if(NOT RAPIDJSON_FOUND)
  message(STATUS "RAPIDJSON will be downloaded when ${CMAKE_PROJECT_NAME} is built")
  ExternalProject_Add(rapidjson-lib
    DEPENDS astro-lib
    PREFIX ${EXTERNAL_PATH}/rapidjson
    #--Download step--------------
    URL https://github.com/miloyip/rapidjson/archive/master.zip
    TIMEOUT 30
    #--Update/Patch step----------
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    #--Configure step-------------
    CONFIGURE_COMMAND ""
    #--Build step-----------------
    BUILD_COMMAND ""
    #--Install step---------------
    INSTALL_COMMAND ""
    #--Output logging-------------
    LOG_DOWNLOAD ON-------------
    LOG_DOWNLOAD ON
  )
  ExternalProject_Get_Property(rapidjson-lib source_dir)
  set(RAPIDJSON_INCLUDE_DIRS ${source_dir}/include
      CACHE INTERNAL "Path to include folder for RapidJSON")
endif(NOT RAPIDJSON_FOUND)

if(NOT APPLE)
  include_directories(SYSTEM AFTER "${RAPIDJSON_INCLUDE_DIRS}")
else(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem \"${RAPIDJSON_INCLUDE_DIRS}\"")
endif(NOT APPLE)

# -------------------------------
