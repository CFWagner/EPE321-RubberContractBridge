# The required libraries are added such as core and gui.
QT       += core gui qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

#All sources classes of the project is addded below.
SOURCES += \
    clientgui.cpp \
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
    main.cpp \
    mainwindow.cpp \
    playernetwork.cpp \
    servergui.cpp

#All header files of the project is addded below.
HEADERS += \
    clientgui.h \
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
    mainwindow.h \
    playernetwork.h \
    servergui.h

#All UI windows are shown below.
FORMS += \
    clientgui.ui \
    mainwindow.ui \
    servergui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    GUI.qrc
