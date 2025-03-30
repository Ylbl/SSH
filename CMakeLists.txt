cmake_minimum_required(VERSION 3.16)
project(SSH LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    include
)
include_directories(
    pages
)


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
    MainWindow.ui
    MainWindow.h
    MainWindow.cpp
    include/ElaWidgetTools.qrc
    ./pages/AIpage.h
    ./pages/AIpage.cpp
    ./pages/BasePage.h
    ./pages/BasePage.cpp
    ./pages/HomePage.h
    ./pages/HomePage.cpp
    ./pages/WQBPage.h
    ./pages/WQBPage.cpp
    
    ./pages/SettingPage.h
    ./pages/SettingPage.cpp
)

qt_add_executable(SSH
    ${PROJECT_SOURCES}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/ElaWidgetTools.lib
)

