
QT       += core gui network
TEMPLATE = app

PROJECTNAME = QDownloadManyFiles
DESTDIR     = build/bin
OBJECTS_DIR = build/obj
MOC_DIR     = build/moc
RCC_DIR     = build/rc
UI_DIR      = build/ui

INCLUDEPATH += \
        src \
        src/dialogs/about \
        src/debughelper \
        src/main \
        src/other \
        src/defines \
        src/downloadmanager \
        src/textprogressbar \
        src/common

DEPENDPATH += \
        src \
        src/dialogs/about \
        src/debughelper \
        src/main \
        src/other \
        src/defines \
        src/downloadmanager \
        src/textprogressbar \
        src/common

# Input
HEADERS += \
        mainwindow.h \
        downloadmanager.h \
        textprogressbar.h \
        about.h \
        common.h \
        defines.h \
        debughelper.h

SOURCES += \
        downloadmanager.cpp\
        main.cpp \
        mainwindow.cpp\
        debughelper.cpp\
        common.cpp \
        about.cpp \
        textprogressbar.cpp

FORMS += \
        mainwindow.ui \
        about.ui

        # install
target.path = $$[QT_INSTALL_EXAMPLES]/network/downloadmanager
sources.files = $$SOURCES $$HEADERS $$FORMS $$RESOURCES *.pro *.png
sources.path = $$[QT_INSTALL_EXAMPLES]/network/downloadmanager
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
