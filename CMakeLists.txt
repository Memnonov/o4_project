cmake_minimum_required(VERSION 3.31)
project(o4_project)

# Set C++ standard and other necessary flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/main.cpp
    src/container.cpp
)

set(HEADERS
    include/o4_project/item.h
)

# Find package
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

# include_directories(${CMAKE_SOURCE_DIR})

add_executable(
  ${PROJECT_NAME}
  ${SOURCES}
  ${HEADERS}
)

# target_link_libraries(o4_project Qt6::Widgets Qt6::Core Qt6::Gui)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt6::Widgets Qt6::Core Qt6::Gui
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
      ${CMAKE_SOURCE_DIR}/include/o4_project
)
