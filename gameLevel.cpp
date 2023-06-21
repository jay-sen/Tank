
#include "gameLevel.h"

GameLevel::GameLevel()
{
    gameMap = new GameMap();
    gameTank = new GameTank();
    gameEffect = new GameEffect();

    setLevel();
}

GameLevel::~GameLevel()
{
    delete gameMap;
    delete gameTank;
    delete gameEffect;
}

void GameLevel::paint(QPainter &painter)
{
    gameMap->paint(painter);
    gameTank->paint(painter);
    gameEffect->paint(painter);
}

void GameLevel::receiveKeyPressEvent(QKeyEvent *event)
{
    gameTank->keyPressed(event);
}

void GameLevel::receiveKeyReleaseEvent(QKeyEvent *event)
{
    gameTank->KeyReleased(event);
}

void GameLevel::update()
{
    gameTank->update();
}

void GameLevel::setGameMode(GameMode mode)
{
    this->mode = mode;
    switch (this->mode) {
    case GameMode::SIGLEPLAYER:
        gameTank->initSiglePlayer();
        break;
    case GameMode::MULTIPLAYER:
        gameTank->initMultiPlayer();
        break;
    }
}

bool GameLevel::missionFailed()
{
    return gameTank->playerNum() == 1; // 只剩一个 help 坦克
}

bool GameLevel::missionSuccessful()
{
    return gameTank->enemyNum() == 0;
}

void GameLevel::setLevel()
{
    gameMap->setMap1();
    gameTank->setLevel1();
}
