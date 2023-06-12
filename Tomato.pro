QT       += core gui multimedia widgets

CONFIG += debug
CONFIG += debug_and_release

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


msvc {
    QMAKE_CFLAGS += \utf-8
    QMAKE_CXXFLAGS += \utf-8
}

TEMPLATE = app
TARGET = TomatoTimer

#INCLUDEPATH += inc \

SOURCES += src/main.cpp \
        src/audiolist.cpp \
        src/audioplayer.cpp \
        src/consoleapender.cpp \
        src/fileapender.cpp \
        src/musicform.cpp \
        src/mywidget.cpp \
        src/recordworkdialog.cpp \
        src/setting.cpp \
        src/widget.cpp

HEADERS += \
    inc/apender.h \
    inc/audiolist.h \
    inc/audioplayer.h \
    inc/consoleapender.h \
    inc/fileapender.h \
    inc/musicform.h \
    inc/mywidget.h \
    inc/recordworkdialog.h \
    inc/setting.h \
    inc/widget.h

FORMS += \
    ui/musicform.ui \
    ui/recordworkdialog.ui \
    ui/setting.ui \
    ui/widget.ui

RESOURCES += \
    rc.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
