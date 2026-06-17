cmake_minimum_required(VERSION 3.16)

project(vanet_world_simulator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(vanet_world_simulator
    app/main.cpp
    core/Engine.cpp
    core/TickClock.cpp
    services/MobilityService.cpp
    services/EventService.cpp
    services/RadioService.cpp
    services/PacketService.cpp
    infrastructure/ConfigLoader.cpp
    infrastructure/CsvLogger.cpp
)

target_include_directories(vanet_world_simulator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
