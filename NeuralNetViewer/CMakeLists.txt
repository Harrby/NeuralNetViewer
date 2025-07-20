cmake_minimum_required(VERSION 3.5)

project(NeuralNetViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES
        main.cpp

        Widgets/mainwindow.cpp
        Widgets/mainwindow.h
        Widgets/valuesliderwidget.h
        Widgets/valuesliderwidget.cpp
        Widgets/valuecomboboxwidget.h
        Widgets/valuecomboboxwidget.cpp
        Widgets/globaloptionswidget.h
        Widgets/globaloptionswidget.cpp
        Widgets/layeroptions.h
        Widgets/layeroptions.cpp

        Widgets/BaseWidgets/slider.h
        Widgets/BaseWidgets/slider.cpp

        Widgets/BaseWidgets/checkbox.h
        Widgets/BaseWidgets/checkbox.cpp

        Widgets/BaseWidgets/lineedit.h
        Widgets/BaseWidgets/lineedit.cpp
        Widgets/BaseWidgets/combobox.h
        Widgets/BaseWidgets/combobox.cpp

        Widgets/BaseWidgets/iconbutton.h
        Widgets/BaseWidgets/iconbutton.cpp

        configParameterDataStructs/neuralnetoptionsdata.h
        configParameterDataStructs/neuralnetoptionsdata.cpp
        configParameterDataStructs/neuralnetlayerdata.h
        configParameterDataStructs/neuralnetlayerdata.cpp
        Widgets/layerscrollarea.h
        Widgets/layerscrollarea.cpp
        Widgets/buttonsframe.h
        Widgets/buttonsframe.cpp
        Widgets/networkconfigwidget.h
        Widgets/networkconfigwidget.cpp

        Widgets/mainwidget.h
        Widgets/mainwidget.cpp

        layer.h layer.cpp

        datasetcontainer.h datasetcontainer.cpp
        activation.h activation.cpp

        loss.h loss.cpp

        neuralnetwork.h neuralnetwork.cpp

)

qt_add_resources(RESOURCES_RCC
    resources.qrc
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NeuralNetViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${RESOURCES_RCC}
    )

    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Widgets)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/BaseWidgets)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/configParameterDataStructs)
    include_directories(${CMAKE_SOURCE_DIR}/eigen-3.4.0)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET NeuralNetViewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(NeuralNetViewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(NeuralNetViewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(NeuralNetViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(NeuralNetViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS NeuralNetViewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NeuralNetViewer)
endif()
