cmake_minimum_required(VERSION 3.0)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")

project(fixture)

set( CMAKE_BUILD_TYPE Debug)
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

if( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
      # using clang
      set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Weverything")
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
      # using gcc
      set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -Wextra")
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Intel")
      # using intel c compiler
    elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
      # using visual studio c compiler
    endif()
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    resources/resources.qrc
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
    src/tools/tooloptions/pan_menu.ui
)

add_executable(fixture  ${SOURCES})
target_link_libraries(fixture 
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
)

install(TARGETS fixture DESTINATION bin)

set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT "eyeon@disroot.org")
include(CPack)
