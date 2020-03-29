QT += core gui network widgets websockets

CONFIG += c++11

TARGET = DotaCard

TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += card core scene ui

SOURCES += \
    card/megameleecreepbad.cpp \
    card/megameleecreepgood.cpp \
    card/megarangedcreepbad.cpp \
    card/megarangedcreepgood.cpp \
    card/meleecreepbad.cpp \
    card/meleecreepgood.cpp \
    card/pugna.cpp \
    card/rangedcreepbad.cpp \
    card/rangedcreepgood.cpp \
    card/siegecreepbad.cpp \
    card/siegecreepgood.cpp \
    card/upgradedmeleecreepbad.cpp \
    card/upgradedmeleecreepgood.cpp \
    card/upgradedrangedcreepbad.cpp \
    card/upgradedrangedcreepgood.cpp \
    card/upgradedsiegecreepbad.cpp \
    card/upgradedsiegecreepgood.cpp \
    core/card.cpp \
    core/carditem.cpp \
    core/client.cpp \
    core/effectmonster.cpp \
    core/engine.cpp \
    core/game.cpp \
    core/main.cpp \
    core/net.cpp \
    scene/exam.cpp \
    scene/examfirst.cpp \
    scene/menu.cpp \
    scene/room.cpp \
    scene/solo.cpp \
    scene/training.cpp \
    scene/view.cpp \
    ui/blackscreen.cpp \
    ui/button.cpp \
    ui/gif.cpp \
    ui/spirit.cpp

HEADERS += \
    card/megameleecreepbad.h \
    card/megameleecreepgood.h \
    card/megarangedcreepbad.h \
    card/megarangedcreepgood.h \
    card/meleecreepbad.h \
    card/meleecreepgood.h \
    card/pugna.h \
    card/rangedcreepbad.h \
    card/rangedcreepgood.h \
    card/siegecreepbad.h \
    card/siegecreepgood.h \
    card/upgradedmeleecreepbad.h \
    card/upgradedmeleecreepgood.h \
    card/upgradedrangedcreepbad.h \
    card/upgradedrangedcreepgood.h \
    card/upgradedsiegecreepbad.h \
    card/upgradedsiegecreepgood.h \
    core/card.h \
    core/carditem.h \
    core/client.h \
    core/effectmonster.h \
    core/engine.h \
    core/game.h \
    core/net.h \
    scene/exam.h \
    scene/examfirst.h \
    scene/menu.h \
    scene/room.h \
    scene/solo.h \
    scene/training.h \
    scene/view.h \
    ui/blackscreen.h \
    ui/button.h \
    ui/gif.h \
    ui/spirit.h

RESOURCES += \
    res.qrc
