QT += testlib
QT -= gui

TARGET = tst_ReferenceImageCorrection

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG   += console
CONFIG   += c++11

CONFIG(release, debug|release): DESTDIR = $$PWD/../../../../../lib
else:CONFIG(debug, debug|release): DESTDIR = $$PWD/../../../../../lib/debug

TEMPLATE = app

unix {
    QMAKE_CXXFLAGS += -fPIC -O2

    unix:!macx {
        INCLUDEPATH += /usr/include/cfitsio/
        QMAKE_CXXFLAGS += -fopenmp
        QMAKE_LFLAGS += -lgomp
        LIBS += -lgomp
    }

    unix:macx {
        INCLUDEPATH += /opt/local/include
        QMAKE_LIBDIR += /opt/local/lib
        LIBS += -L/opt/local/lib
    }

    LIBS +=  -lm -lz -ltiff -lfftw3 -lfftw3f -lcfitsio -larmadillo -llapack -lblas
}

win32 {
    contains(QMAKE_HOST.arch, x86_64):{
    QMAKE_LFLAGS += /MACHINE:X64
    }
    INCLUDEPATH += $$PWD/../../../../external/include $$PWD/../../../../external/include/cfitsio
    QMAKE_LIBDIR += $$PWD/../../../../external/lib64
    QMAKE_CXXFLAGS += /openmp /O2

     LIBS += -llibtiff -lcfitsio -llibfftw3-3 -llibfftw3f-3 -lIphlpapi
     LIBS += -lzlib_a
}

SOURCES +=  tst_referenceimagecorrection.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
CONFIG(debug, debug|release): DEFINES += DEBUG

CONFIG(release, debug|release):    LIBS += -L$$PWD/../../../../../lib/
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../lib/debug/

LIBS += -lkipl -lImagingAlgorithms

INCLUDEPATH += $$PWD/../../ImagingAlgorithms/include
DEPENDPATH += $$PWD/../../ImagingAlgorithms/include

INCLUDEPATH += $$PWD/../../../kipl/kipl/include
DEPENDPATH += $$PWD/../../../kipl/kipl/src