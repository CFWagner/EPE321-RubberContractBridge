# The required libraries are added such as core and gui.
QT += core gui qml
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
CONFIG += no_testcase_installs
CONFIG += resources_big
CONFIG(release, debug|release):DEFINES += QT_NO_INFO_OUTPUT

# If quick entry is defined, then no passwords will be required to connect to the server.
# QUICK_SERVER_ENTRY will also only be defined if in DEBUG mode.
CONFIG(debug, release|debug):DEFINES += QUICK_SERVER_ENTRY

#All sources classes of the project is addded below.
SOURCES += \
    ai/ai.cpp \
    ai/dumbai.cpp \
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
    gui/bidselect.cpp \
    gui/cardselected.cpp \
    gui/clientlogin.cpp \
    gui/entrywindow.cpp \
    gui/gamewindow.cpp \
    gui/hover.cpp \
    gui/loggerwindow.cpp \
    gui/scorewindow.cpp \
    gui/serverlobby.cpp \
    gui/serverlogin.cpp \
    logger/logger.cpp \
    main.cpp \
    network/servernetwork.cpp \
    network/playernetwork.cpp \
    network/clientnetwork.cpp \
    unit-tests/ai/testai.cpp \
    unit-tests/game-server/stubs/playerstub.cpp \
    unit-tests/game-server/testbid.cpp \
    unit-tests/game-server/testcard.cpp \
    unit-tests/game-server/testcardset.cpp \
    unit-tests/game-server/testgameserver.cpp \
    unit-tests/game-server/testplayergamestate.cpp \
    unit-tests/game-server/testscore.cpp \
    unit-tests/game-server/testserver.cpp \
    unit-tests/game-server/testservergamestate.cpp \
    unit-tests/logger/testlogger.cpp \
    unit-tests/network/testclientnetwork.cpp \
    unit-tests/network/testplayernetwork.cpp \
    unit-tests/network/testservernetwork.cpp

#All header files of the project is addded below.
HEADERS += \
    ai/ai.h \
    ai/dumbai.h \
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
    gui/bidselect.h \
    gui/cardselected.h \
    gui/clientlogin.h \
    gui/entrywindow.h \
    gui/gamewindow.h \
    gui/hover.h \
    gui/loggerwindow.h \
    gui/scorewindow.h \
    gui/serverlobby.h \
    gui/serverlogin.h \
    logger/logger.h \
    network/servernetwork.h \
    network/playernetwork.h \
    network/clientnetwork.h \
    unit-tests/ai/testai.h \
    unit-tests/game-server/stubs/playerstub.h \
    unit-tests/game-server/testbid.h \
    unit-tests/game-server/testcard.h \
    unit-tests/game-server/testcardset.h \
    unit-tests/game-server/testgameserver.h \
    unit-tests/game-server/testplayergamestate.h \
    unit-tests/game-server/testscore.h \
    unit-tests/game-server/testserver.h \
    unit-tests/game-server/testservergamestate.h \
    unit-tests/logger/testlogger.h \
    unit-tests/network/testclientnetwork.h \
    unit-tests/network/testplayernetwork.h \
    unit-tests/network/testservernetwork.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    gui/clientlogin.ui \
    gui/entrywindow.ui \
    gui/gamewindow.ui \
    gui/loggerwindow.ui \
    gui/scorewindow.ui \
    gui/serverlobby.ui \
    gui/serverlogin.ui

DISTFILES += \
    ai_testing.bat \
    guiResources/background/background1.png \
    guiResources/background/background2.png \
    guiResources/background/background3.png \
    guiResources/background/clientButton2.png \
    guiResources/background/green.png \
    guiResources/background/grey.png \
    guiResources/background/login.png \
    guiResources/background/playerBackground.png \
    guiResources/background/qwe.png \
    guiResources/background/robot.png \
    guiResources/background/selectedButton.png \
    guiResources/background/serverButton2.png \
    guiResources/background/unselectedButton.png \
    guiResources/background/userIcon.png \
    guiResources/buttons/add_green.png \
    guiResources/buttons/add_grey.png \
    guiResources/buttons/c_green.png \
    guiResources/buttons/c_grey.png \
    guiResources/buttons/clear_green.png \
    guiResources/buttons/clear_grey.png \
    guiResources/buttons/create_green.png \
    guiResources/buttons/create_grey.png \
    guiResources/buttons/login_green.png \
    guiResources/buttons/login_grey.png \
    guiResources/buttons/s_green.png \
    guiResources/buttons/s_grey.png \
    guiResources/buttons/start_green.png \
    guiResources/buttons/start_grey.png \
    guiResources/cards/ace_clubs.png \
    guiResources/cards/ace_diamonds.png \
    guiResources/cards/ace_hearts.png \
    guiResources/cards/ace_spades.png \
    guiResources/cards/back_card.png \
    guiResources/cards/eight_clubs.png \
    guiResources/cards/eight_diamonds.png \
    guiResources/cards/eight_hearts.png \
    guiResources/cards/eight_spades.png \
    guiResources/cards/five_clubs.png \
    guiResources/cards/five_diamonds.png \
    guiResources/cards/five_hearts.png \
    guiResources/cards/five_spades.png \
    guiResources/cards/four_clubs.png \
    guiResources/cards/four_diamonds.png \
    guiResources/cards/four_hearts.png \
    guiResources/cards/four_spades.png \
    guiResources/cards/jack_clubs.png \
    guiResources/cards/jack_diamonds.png \
    guiResources/cards/jack_hearts.png \
    guiResources/cards/jack_spades.png \
    guiResources/cards/king_clubs.png \
    guiResources/cards/king_diamonds.png \
    guiResources/cards/king_hearts.png \
    guiResources/cards/king_spades.png \
    guiResources/cards/nine_clubs.png \
    guiResources/cards/nine_diamonds.png \
    guiResources/cards/nine_hearts.png \
    guiResources/cards/nine_spades.png \
    guiResources/cards/queen_clubs.png \
    guiResources/cards/queen_diamonds.png \
    guiResources/cards/queen_hearts.png \
    guiResources/cards/queen_spades.png \
    guiResources/cards/seven_clubs.png \
    guiResources/cards/seven_diamonds.png \
    guiResources/cards/seven_hearts.png \
    guiResources/cards/seven_spades.png \
    guiResources/cards/six_clubs.png \
    guiResources/cards/six_diamonds.png \
    guiResources/cards/six_hearts.png \
    guiResources/cards/six_spades.png \
    guiResources/cards/ten_clubs.png \
    guiResources/cards/ten_diamonds.png \
    guiResources/cards/ten_hearts.png \
    guiResources/cards/ten_spades.png \
    guiResources/cards/three_clubs.png \
    guiResources/cards/three_diamonds.png \
    guiResources/cards/three_hearts.png \
    guiResources/cards/three_spades.png \
    guiResources/cards/two_clubs.png \
    guiResources/cards/two_diamonds.png \
    guiResources/cards/two_hearts.png \
    guiResources/cards/two_spades.png \
    swapMains.bat

RESOURCES += \
    resource.qrc
