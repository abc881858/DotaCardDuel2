#-------------------------------------------------
#
# Project created by QtCreator 2018-01-13T21:57:02
#
#-------------------------------------------------

QT       += core gui websockets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11
#CONFIG += warn_on

TARGET = DotaCard
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    card.cpp \
    carditem.cpp \
    net.cpp \
    engine.cpp \
    introduction.cpp \
    menuscene.cpp \
    pixmap.cpp \
    deckscene.cpp \
    phase.cpp \
    package2.cpp \
    dota.cpp \
    room.cpp \
    card/centaurwarrunner.cpp \
    card/keeperofthelight.cpp \
    card/lion.cpp \
    card/magnus.cpp \
    card/nyxassassin.cpp \
    card/rubick.cpp \
    card/tusk.cpp \
    card/undying.cpp \
    card/vengefulspirit.cpp \
    card/zeus.cpp \
    card/helmofthedominator.cpp \
    card/forcestaff.cpp \
    card/gemoftruesight.cpp \
    card/urnofshadows.cpp \
    equipspellcard.cpp \
    effectmonstercard.cpp \
    structs.cpp

HEADERS += \
    card.h \
    carditem.h \
    net.h \
    engine.h \
    introduction.h \
    menuscene.h \
    pixmap.h \
    deckscene.h \
    phase.h \
    package2.h \
    dota.h \
    room.h \
    card/centaurwarrunner.h \
    card/keeperofthelight.h \
    card/lion.h \
    card/magnus.h \
    card/nyxassassin.h \
    card/rubick.h \
    card/tusk.h \
    card/undying.h \
    card/vengefulspirit.h \
    card/zeus.h \
    card/helmofthedominator.h \
    card/forcestaff.h \
    card/gemoftruesight.h \
    card/urnofshadows.h \
    equipspellcard.h \
    effectmonstercard.h \
    structs.h

RESOURCES += \
    dotacard.qrc

TRANSLATIONS += dc_zh_cn.ts

win32:QMAKE_CXXFLAGS += /wd"4819"
