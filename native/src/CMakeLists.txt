cmake_minimum_required(VERSION 3.5)

project(athanor)
find_package(JNI REQUIRED)

set (SOURCE_ATHANOR_INTERFACE "athanor.cxx")
set (PLATFORM_DEST "install")
#
# This is what is produced by athanor. 
# We want to make sure the operating system is part of the path 
# where there is library is placed, so that there is one for 
# each operating system without clashing. 
# 
set (ATHANOR_CORE athanor4s/objs/Linux/athanor-core.a)
set(CMAKE_CXX_FLAGS "-std=c++11 -w -fPIC -O3 -DUNIX")
include_directories(./include ${JNI_INCLUDE_DIRS}) 

#
# Install library
# Separate for each operating sytem so that we can 
# eventually gather all the dlls into one jar 
#
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./${CMAKE_SYSTEM_NAME})

add_library(athanor SHARED ${SOURCE_ATHANOR_INTERFACE})
target_link_libraries(athanor "-Wl,--whole-archive" /home/joseph/athanor4s/native/objs/Linux/athanor-core.a "-Wl,--no-whole-archive") 

install(TARGETS athanor 
  LIBRARY DESTINATION ${PLATFORM_DEST})


