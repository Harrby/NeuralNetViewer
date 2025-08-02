cmake_minimum_required(VERSION 3.5)

project(NeuralNetViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets PrintSupport)



set(PROJECT_SOURCES
        main.cpp

        Widgets/mainwindow.cpp Widgets/mainwindow.h
        Widgets/mainwidget.h Widgets/mainwidget.cpp

        Widgets/BaseWidgets/valuesliderwidget.h Widgets/BaseWidgets/valuesliderwidget.cpp
        Widgets/BaseWidgets/valuecomboboxwidget.h Widgets/BaseWidgets/valuecomboboxwidget.cpp
        Widgets/BaseWidgets/slider.h Widgets/BaseWidgets/slider.cpp
        Widgets/BaseWidgets/checkbox.h Widgets/BaseWidgets/checkbox.cpp
        Widgets/BaseWidgets/lineedit.h Widgets/BaseWidgets/lineedit.cpp
        Widgets/BaseWidgets/combobox.h Widgets/BaseWidgets/combobox.cpp
        Widgets/BaseWidgets/iconbutton.h Widgets/BaseWidgets/iconbutton.cpp
        Widgets/BaseWidgets/valuecheckboxwidget.h Widgets/BaseWidgets/valuecheckboxwidget.cpp
        Widgets/BaseWidgets/statusbar.h Widgets/BaseWidgets/statusbar.cpp
        Widgets/BaseWidgets/logwidget.h Widgets/BaseWidgets/logwidget.cpp

        configParameterDataStructs/neuralnetoptionsdata.h
        configParameterDataStructs/neuralnetoptionsdata.cpp
        configParameterDataStructs/neuralnetlayerdata.h
        configParameterDataStructs/neuralnetlayerdata.cpp

        Widgets/NetworkConfigWidgets/globaloptionswidget.h
        Widgets/NetworkConfigWidgets/globaloptionswidget.cpp
        Widgets/NetworkConfigWidgets/layeroptions.h
        Widgets/NetworkConfigWidgets/layeroptions.cpp
        Widgets/NetworkConfigWidgets/layerscrollarea.h
        Widgets/NetworkConfigWidgets/layerscrollarea.cpp
        Widgets/NetworkConfigWidgets/buttonsframe.h
        Widgets/NetworkConfigWidgets/buttonsframe.cpp
        Widgets/NetworkConfigWidgets/networkconfigwidget.h
        Widgets/NetworkConfigWidgets/networkconfigwidget.cpp






        NeuralNetwork/layer.h NeuralNetwork/layer.cpp

        dataset_classes/datasetcontainer.h dataset_classes/datasetcontainer.cpp
        dataset_classes/datasettype.h

        NeuralNetwork/activation/activation.h NeuralNetwork/activation/activation.cpp
        NeuralNetwork/activation/activation_utils.h

        NeuralNetwork/loss/loss.h NeuralNetwork/loss/loss.cpp
        NeuralNetwork/loss/loss_utils.h

        NeuralNetwork/neuralnetwork.h NeuralNetwork/neuralnetwork.cpp

        NeuralNetwork/optimiser/optimiser.h NeuralNetwork/optimiser/optimiser.cpp
        NeuralNetwork/optimiser/optimiser_utils.h
        NeuralNetwork/initialisation/initialisation_utils.h


        mnistinputwidget.h mnistinputwidget.cpp

        drawarea.h drawarea.cpp

        Widgets/TrainWidgets/trainwidget.h Widgets/TrainWidgets/trainwidget.cpp
        Widgets/TrainWidgets/trainoptionswidget.h Widgets/TrainWidgets/trainoptionswidget.cpp
        Widgets/TrainWidgets/trainstatuswidget.h Widgets/TrainWidgets/trainstatuswidget.cpp
        Widgets/TrainWidgets/graphwidget.h Widgets/TrainWidgets/graphwidget.cpp
        Widgets/TrainWidgets/trainingstatsframe.h Widgets/TrainWidgets/trainingstatsframe.cpp

        metrics/epochstats.h

        metrics/metrics.h



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
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/NeuralNetwork)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/NeuralNetwork/activation)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/NeuralNetwork/initialisation)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/NeuralNetwork/loss)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/NeuralNetwork/optimiser)


    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/TrainWidgets)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Widgets/NetworkConfigWidgets)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/metrics)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dataset_classes)
    target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/qcustomplot/qcustomplot.cpp)
    include_directories(${CMAKE_SOURCE_DIR}/eigen-3.4.0)
    include_directories(${CMAKE_SOURCE_DIR}/qcustomplot)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::PrintSupport)
    set_source_files_properties(
      ${CMAKE_SOURCE_DIR}/qcustomplot/qcustomplot.cpp
      PROPERTIES
        COMPILE_FLAGS "/wd4996"
    )

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
