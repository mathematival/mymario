QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brick.cpp \
    castle.cpp \
    fire.cpp \
    gamehelp.cpp \
    gamepause.cpp \
    gamescene.cpp \
    gameset.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    mary.cpp \
    master.cpp \
    mushroom.cpp \
    musicplayer.cpp \
    mypushbutton.cpp \
    pipe.cpp \
    unknown.cpp

HEADERS += \
    brick.h \
    castle.h \
    fire.h \
    gamehelp.h \
    gamepause.h \
    gamescene.h \
    gameset.h \
    global.h \
    mainwindow.h \
    mary.h \
    master.h \
    mushroom.h \
    musicplayer.h \
    mypushbutton.h \
    pipe.h \
    unknown.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
