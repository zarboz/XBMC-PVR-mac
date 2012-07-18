# Install script for directory: /Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/plist" TYPE FILE FILES
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/plist.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/plist++.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/Array.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/Boolean.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/Data.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/Date.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/Dictionary.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/Integer.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/Node.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/Real.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/String.h"
    "/Users/bryansmith/XBMC-PVR-mac/tools/darwin/depends/libplist/libplist-1.6/include/plist/Structure.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

