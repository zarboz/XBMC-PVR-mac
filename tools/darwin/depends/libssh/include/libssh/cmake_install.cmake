# Install script for directory: /Users/bryansmith/xbmc/tools/darwin/depends/libssh/libssh/include/libssh

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/libssh/callbacks.h;/usr/local/include/libssh/libssh.h;/usr/local/include/libssh/ssh2.h;/usr/local/include/libssh/legacy.h;/usr/local/include/libssh/sftp.h;/usr/local/include/libssh/server.h")
FILE(INSTALL DESTINATION "/usr/local/include/libssh" TYPE FILE FILES
    "/Users/bryansmith/xbmc/tools/darwin/depends/libssh/libssh/include/libssh/callbacks.h"
    "/Users/bryansmith/xbmc/tools/darwin/depends/libssh/libssh/include/libssh/libssh.h"
    "/Users/bryansmith/xbmc/tools/darwin/depends/libssh/libssh/include/libssh/ssh2.h"
    "/Users/bryansmith/xbmc/tools/darwin/depends/libssh/libssh/include/libssh/legacy.h"
    "/Users/bryansmith/xbmc/tools/darwin/depends/libssh/libssh/include/libssh/sftp.h"
    "/Users/bryansmith/xbmc/tools/darwin/depends/libssh/libssh/include/libssh/server.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")

