cmake_minimum_required(VERSION 3.16)
project(SSH LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(openCV_DIR C:/opencv/build)

include_directories(
    ${openCV_DIR}/include
)
link_directories(
    ${openCV_DIR}/lib
)
include_directories(
    include
)
include_directories(
    pages
)
include_directories(
    units
)
include_directories(
    include/smtp
)

find_package(mailio CONFIG REQUIRED)
find_package(boost_system CONFIG REQUIRED)
find_package(boost_date_time CONFIG REQUIRED)
find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)



find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(OpenCV REQUIRED)
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
    
    ./units/test.hpp
    ./units/inference.h
    ./units/inference.cpp
    ./units/send_email.hpp

    
    
)

qt_add_executable(SSH
    ${PROJECT_SOURCES}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::date_time)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)
target_link_libraries(${PROJECT_NAME} PRIVATE mailio)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Network
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/ElaWidgetTools.lib
        ${OpenCV_LIBS}
        
)

target_link_options(SSH PRIVATE "/SUBSYSTEM:CONSOLE")

