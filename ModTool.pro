QT       += core gui
QT       += webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    csteammanager.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    SteamApiData.h \
    csteammanager.h \
    mainwindow.h \
    ui/overlaywidget.h\

FORMS += \
    mainwindow.ui\
    messagebox.ui \
    ui_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = icons/1x/jyx2.ico

DEFINES += USE_x64

win32
{
    contains(DEFINES, USE_x64){
        LIBS += -L$$PWD/steam/win64 -lsteam_api64
    }else{
        LIBS += -L$$PWD/steam/win32 -lsteam_api
    }

    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
    DLLDESTDIR = bin
}

unix:LIBS += -L$$PWD/steam/osx -lsteam_api


INCLUDEPATH += $$PWD/steam \
               $$PWD/ui
DEPENDPATH += $$PWD/steam

RESOURCES += \
    mainwindow.qrc
