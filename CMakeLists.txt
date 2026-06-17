cmake_minimum_required(VERSION 3.20)

project(vanet_world_simulator VERSION 0.0.7 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(vanet_world_simulator
    app/main.cpp
    core/Engine.cpp
    core/TickClock.cpp
    services/MobilityService.cpp
)

target_include_directories(vanet_world_simulator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)