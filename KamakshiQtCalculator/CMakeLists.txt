cmake_minimum_required(VERSION 3.21)
project(KamakshiCalculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(KamakshiCalculator
    src/main.cpp
)

target_link_libraries(KamakshiCalculator PRIVATE Qt6::Widgets)
