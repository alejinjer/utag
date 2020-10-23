cmake_minimum_required(VERSION 3.17)

set(SOURCES mainwindow.cpp
        MainTableModel.cpp
        EditTableController.cpp
        TagEditor.cpp
        Logger.cpp)

set(HEADERS mainwindow.h
        MainTableModel.h
        EditTableController.h
        TagEditor.h
        Logger.h)

set(UI mainwindow.ui)

link_directories(../../build/3dparty/taglib/)


add_library(src ${SOURCES} ${HEADERS} ${UI})

target_link_libraries(src PRIVATE Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Multimedia
        tag
)
