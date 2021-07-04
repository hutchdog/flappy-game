cmake_minimum_required(VERSION 3.10)

project(game)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${JNI_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES game/App.cpp game/AndroidApp.cpp game/AndroidRenderer.cpp game/Level.cpp game/Timer.cpp game/Mesh.cpp game/Block.cpp)

add_library(game SHARED ${SOURCE_FILES})

target_link_libraries(game android log EGL GLESv2)
