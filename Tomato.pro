QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/audiolist.cpp \
    src/audioplayer.cpp \
    src/consoleapender.cpp \
    src/fileapender.cpp \
    src/main.cpp \
    src/musicform.cpp \
    src/mywidget.cpp \
    src/recordworkdialog.cpp \
    src/setting.cpp \
    src/widget.cpp

HEADERS += \
    include/apender.h \
    include/audiolist.h \
    include/audioplayer.h \
    include/consoleapender.h \
    include/fileapender.h \
    include/musicform.h \
    include/mywidget.h \
    include/recordworkdialog.h \
    include/setting.h \
    include/widget.h


FORMS += \
    ui/musicform.ui \
    ui/recordworkdialog.ui \
    ui/setting.ui \
    ui/widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    hm_out_small.jpg \
    icon.png
