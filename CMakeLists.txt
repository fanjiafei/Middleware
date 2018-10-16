cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)
project( IPC_Serial )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x -O2 -g3 -fPIC")
# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
option(Dus_mode "ON for gdbus or OFF for qdbus" ON)

IF(Dus_mode)#gdbus

add_definitions(-DGDBUS)

message("build with gdbus\n")
FIND_PACKAGE (Threads REQUIRED)
FIND_PACKAGE (PkgConfig REQUIRED)
PKG_CHECK_MODULES (GLIB2 REQUIRED glib-2.0>=2.40)
PKG_CHECK_MODULES (GIO REQUIRED gio-2.0>=2.40)
PKG_CHECK_MODULES (GIO-UNIX REQUIRED gio-unix-2.0>=2.40)
include_directories(${GLIB2_INCLUDE_DIRS})
include_directories(${GIO_INCLUDE_DIRS})
include_directories(${GIO-UNIX_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/ SRC_LIST_1)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/gdbus)# 添加 gdbus 子目录
ADD_EXECUTABLE(IPC_Serial  ${SRC_LIST_1} )
TARGET_LINK_LIBRARIES(IPC_Serial  gdbusLib gio-2.0 gobject-2.0 glib-2.0  pthread )

ELSE(Dus_mode)#qdbus

message("build with qdbus")
set(SYSROOT_DIR /home/fan/Qt5.4.0/5.4/gcc)#your sysroot path
INCLUDE_DIRECTORIES(${SYSROOT_DIR}/include/)
INCLUDE_DIRECTORIES(${SYSROOT_DIR}/include/QtCore)
INCLUDE_DIRECTORIES(${SYSROOT_DIR}/include/QtDBus)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/)
link_directories(${SYSROOT_DIR}/lib/ /usr/lib/)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/ SRC_LIST_1)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/qdbus)# 添加 qdbus 子目录
ADD_EXECUTABLE(IPC_Serial  ${SRC_LIST_1} )
TARGET_LINK_LIBRARIES(IPC_Serial qdbusLib Qt5Core Qt5DBus pthread )

ENDIF(Dus_mode)


INSTALL(TARGETS IPC_Serial  DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")


