cmake_minimum_required(VERSION 3.16)

project(vanet_world_simulator VERSION 0.0.16 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(vanet_world_simulator
    app/main.cpp
    core/Engine.cpp
    services/ClientRegistry.cpp
    services/AssignmentService.cpp
    services/StateReportService.cpp
    services/TrafficLightService.cpp
    services/ReadinessService.cpp
    services/VirtualClientPlanner.cpp
    services/StateValidationService.cpp
    services/ExperimentLogService.cpp
    services/ScenarioConstraintService.cpp
    services/TrafficLightControlService.cpp
    services/ClientHealthService.cpp
    services/MissionProgressService.cpp
    services/PacketLedgerService.cpp
    services/SessionLifecycleService.cpp
    services/SpeedPolicyService.cpp
)

target_include_directories(vanet_world_simulator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
