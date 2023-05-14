QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bird.cpp \
    brick.cpp \
    bullet.cpp \
    cannibal.cpp \
    castle.cpp \
    fire.cpp \
    flag.cpp \
    flagpole.cpp \
    flower.cpp \
    gamehelp.cpp \
    gamepause.cpp \
    gameset.cpp \
    global.cpp \
    kuba.cpp \
    level1.cpp \
    level2.cpp \
    level3.cpp \
    main.cpp \
    mainwindow.cpp \
    mary.cpp \
    master.cpp \
    mushroom.cpp \
    musicplayer.cpp \
    mypushbutton.cpp \
    pipe.cpp \
    rainbow.cpp \
    shell.cpp \
    spikeweed.cpp \
    unknown.cpp

HEADERS += \
    bird.h \
    brick.h \
    bullet.h \
    cannibal.h \
    castle.h \
    fire.h \
    flag.h \
    flagpole.h \
    flower.h \
    gamehelp.h \
    gamepause.h \
    gameset.h \
    global.h \
    kuba.h \
    level1.h \
    level2.h \
    level3.h \
    mainwindow.h \
    mary.h \
    master.h \
    mushroom.h \
    musicplayer.h \
    mypushbutton.h \
    pipe.h \
    rainbow.h \
    shell.h \
    spikeweed.h \
    unknown.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
