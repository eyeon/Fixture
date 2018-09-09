cmake_minimum_required(VERSION 3.0)
project(Fixture)
set( CMAKE_BUILD_TYPE Debug)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

list (APPEND RESOURCES resources/resources.qrc)
qt5_add_resources (RCC_SOURCES ${RESOURCES})

set(SOURCES
    src/dialogs/newdialog.cpp 
    src/widgets/paintwidget.cpp 
    src/main.cpp 
    src/mainwindow.cpp 
    src/widgets/layermanager.cpp 
    src/model/canvas.cpp 
    src/tools/tool.cpp 
    src/tools/transform.cpp 
    src/tools/pan.cpp 
    src/layers/rasterlayer.cpp 
    src/layers/layer.cpp 
    src/model/drawing.cpp 
    src/tools/abstractselection.cpp 
    src/tools/abstractperception.cpp 
    src/tools/components/boundingrectitem.cpp 
    src/tools/tooloptions/transform_menu.cpp 
    src/tools/tooloptions/toolmenu.cpp
    src/tools/tooloptions/pan_menu.cpp
    src/model/document.cpp
    src/mainwindow.ui 
    src/dialogs/newdialog.ui 
    src/tools/tooloptions/transform_menu.ui 
    src/tools/tooloptions/pan_menu.ui
)

add_executable(Fixture ${RESOURCES} ${SOURCES})
target_link_libraries(Fixture 
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
)
