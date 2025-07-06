QT += core gui multimedia widgets printsupport

CONFIG += c++17


TARGET = PhotoViewerPro
TEMPLATE = app

SOURCES += main.cpp \
           brightnessfilter.cpp \
           gaussianblurfilter.cpp \
           histogramdata.cpp \
           histogramwidget.cpp \
           imageprocessor.cpp \
           imagestore.cpp \
           mainwindow.cpp \
           filterwidget.cpp \
           imagewidget.cpp \
           buttonwidget.cpp \
           negativefilter.cpp \
           qcustomplot.cpp \
           sepiafilter.cpp

HEADERS += mainwindow.h \
           brightnessfilter.h \
           filter.h \
           filtersettings.h \
           gaussianblurfilter.h \
           histogramdata.h \
           histogramwidget.h \
           imageprocessor.h \
           imagestore.h \
           filterwidget.h \
           imagewidget.h \
           buttonwidget.h \
           negativefilter.h \
           qcustomplot.h \
           sepiafilter.h \
    constants.h
