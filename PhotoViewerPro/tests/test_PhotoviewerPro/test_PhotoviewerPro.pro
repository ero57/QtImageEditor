QT += core testlib widgets

CONFIG += c++17 cmdline testcase testlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../../

SOURCES += \
    ../../brightnessfilter.cpp \
    ../../gaussianblurfilter.cpp \
    ../../histogramdata.cpp \
    ../../imageprocessor.cpp \
    ../../imagestore.cpp \
    ../../negativefilter.cpp \
    ../../sepiafilter.cpp \
    tests_all.cpp

HEADERS += \
    ../../brightnessfilter.h \
    ../../gaussianblurfilter.h \
    ../../histogramdata.h \
    ../../imageprocessor.h \
    ../../imagestore.h \
    ../../negativefilter.h \
    ../../sepiafilter.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    test_images.qrc
