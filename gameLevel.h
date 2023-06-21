
#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include "gameElement.h"

class GameLevel
{
public:
    GameLevel();
    ~GameLevel();
    void paint(QPainter &painter);
    void receiveKeyPressEvent(QKeyEvent *event);
    void receiveKeyReleaseEvent(QKeyEvent *event);
    void update();

    void setGameMode(GameMode mode);

    bool missionFailed();
    bool missionSuccessful();

    void setLevel();

public:
    GameMode mode;
    GameMap *gameMap;
    GameTank *gameTank;
    GameEffect *gameEffect;
};

#endif // GAMELEVEL_H
