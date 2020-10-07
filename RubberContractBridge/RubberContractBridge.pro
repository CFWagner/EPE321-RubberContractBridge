# The required libraries are added such as core and gui.
QT       += core gui qml
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += no_testcase_installs

#All sources classes of the project is addded below.
SOURCES += \
    game-server/bid.cpp \
    game-server/card.cpp \
    game-server/cardset.cpp \
    game-server/gameserver.cpp \
    game-server/gamestate.cpp \
    game-server/player.cpp \
    game-server/playergamestate.cpp \
    game-server/score.cpp \
    game-server/server.cpp \
    game-server/servergamestate.cpp \
    gui/clientlogin.cpp \
    gui/entrywindow.cpp \
    gui/servergui.cpp \
    gui/serverlobby.cpp \
    hover.cpp \
    main.cpp \
    network/servernetwork.cpp \
    network/playernetwork.cpp \
    network/clientnetwork.cpp \
    unit-tests/game-server/testbid.cpp \
    unit-tests/game-server/testcard.cpp \
    unit-tests/game-server/testcardset.cpp \
    unit-tests/game-server/testplayergamestate.cpp \
    unit-tests/game-server/testservergamestate.cpp \
    unit-tests/gui/testclientlogin.cpp \
    unit-tests/gui/testlobby.cpp \
    unit-tests/gui/testserverlogin.cpp \
    unit-tests/network/testclientnetwork.cpp \
    unit-tests/network/testplayernetwork.cpp \
    unit-tests/network/testservernetwork.cpp

#All header files of the project is addded below.
HEADERS += \
    enumerations/BidCall.h \
    enumerations/CardRank.h \
    enumerations/CardSuit.h \
    enumerations/GameEvent.h \
    enumerations/GamePhase.h \
    enumerations/PlayerPosition.h \
    enumerations/Team.h \
    game-server/bid.h \
    game-server/card.h \
    game-server/cardset.h \
    game-server/gameserver.h \
    game-server/gamestate.h \
    game-server/player.h \
    game-server/playergamestate.h \
    game-server/score.h \
    game-server/server.h \
    game-server/servergamestate.h \
    gui/clientlogin.h \
    gui/entrywindow.h \
    gui/servergui.h \
    gui/serverlobby.h \
    hover.h \
    network/servernetwork.h \
    network/playernetwork.h \
    network/clientnetwork.h \
    unit-tests/game-server/testbid.h \
    unit-tests/game-server/testcard.h \
    unit-tests/game-server/testcardset.h \
    unit-tests/game-server/testplayergamestate.h \
    unit-tests/game-server/testservergamestate.h \
    unit-tests/gui/testclientlogin.h \
    unit-tests/gui/testlobby.h \
    unit-tests/gui/testserverlogin.h \
    unit-tests/network/testclientnetwork.h \
    unit-tests/network/testplayernetwork.h \
    unit-tests/network/testservernetwork.h

#All UI windows are shown below.
FORMS += \
    gui/clientlogin.ui \
    gui/entrywindow.ui \
    gui/servergui.ui \
    gui/serverlobby.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
