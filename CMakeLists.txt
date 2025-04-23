cmake_minimum_required(VERSION 3.31)
project(o4_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_PARALLEL_LEVEL 8)

set(SOURCES
    src/main.cpp
    src/container.cpp
    src/container_model.cpp
    src/main_window.cpp
    src/navigation_window.cpp
    src/container_window.cpp
    src/items_window.cpp
    src/item_info_window.cpp
    src/browse_window.cpp
)

set(HEADERS
    include/o4_project/item.h
    include/o4_project/container.h
    include/o4_project/container_model.h
    include/o4_project/main_window.h
    include/o4_project/navigation_window.h
    include/o4_project/container_window.h
    include/o4_project/items_window.h
    include/o4_project/item_info_window.h
    include/o4_project/mode_frame.h
    include/o4_project/browse_window.h
)

set(TEST_SOURCES
    test/test_main.cpp
    src/container.cpp
    src/container_model.cpp
)

set(TEST_HEADERS
    test/container_tests.h
    test/container_model_tests.h
    include/o4_project/container_model.h
)

set (RESOURCE_FILES
  assets/resources.qrc
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Test Svg)

qt_add_resources(RESOURCE_RESOURCES 
  ${RESOURCE_FILES}
)

add_executable(run_tests
    ${TEST_SOURCES}
    ${TEST_HEADERS}
)

qt_add_executable( ${PROJECT_NAME}
  ${SOURCES}
  ${HEADERS}
  ${RESOURCE_RESOURCES}
)


target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt6::Widgets 
    Qt6::Core
    Qt6::Gui
)

target_link_libraries(run_tests
  PRIVATE
    Qt6::Widgets 
    Qt6::Core
    Qt6::Gui
    Qt6::Test
    Qt6::Svg
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
      ${CMAKE_SOURCE_DIR}/include/o4_project
)

enable_testing()
add_test(NAME ContainerTests COMMAND runTests)
