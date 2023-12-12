cmake_minimum_required(VERSION 3.16)
project(trees LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    MazeUI.ui
    MazeUI.cpp
    MazeUI.h
    Astar.cpp
    maze.cpp
    maze_head.h
)

qt_add_executable(trees ${PROJECT_SOURCES})

set_target_properties(trees
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(trees
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
