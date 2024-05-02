TARGET = SortAlg

QT += core gui widgets

CONFIG += c++14 static

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    ArrayBlock.cpp \
    ArrayView.cpp \
    BubbleSort.cpp \
    HeapSort.cpp \
    InformationWindow.cpp \
    InsertionSort.cpp \
    Instruction.cpp \
    MergeSort.cpp \
    QuickSortHoare.cpp \
    QuickSortLomuto.cpp \
    SelectionSort.cpp \
    SettingsWindow.cpp \
    SortingAlgorithm.cpp \
    SourceCodeView.cpp \
    SourceLine.cpp \
    VariableInformation.cpp \
    VariablesView.cpp \
    VisualizationTaskTab.cpp \
    ExperimentalResearchTaskTab.cpp

HEADERS += \
    MainWindow.hpp \
    ArrayBlock.hpp \
    ArrayView.hpp \
    BubbleSort.hpp \
    HeapSort.hpp \
    InformationWindow.hpp \
    InsertionSort.hpp \
    Instruction.hpp \
    MergeSort.hpp \
    QuickSortHoare.hpp \
    QuickSortLomuto.hpp \
    SelectionSort.hpp \
    Settings.hpp \
    SettingsWindow.hpp \
    SortingAlgorithm.hpp \
    SortingAlgorithms.hpp \
    SortingAlgorithmType.hpp \
    SourceCodeView.hpp \
    SourceLine.hpp \
    VariableInformation.hpp \
    VariablesView.hpp \
    VisualizationTaskTab.hpp \
    ExperimentalResearchTaskTab.hpp

RESOURCES += \
    Resources.qrc

RC_FILE = ico.rc
