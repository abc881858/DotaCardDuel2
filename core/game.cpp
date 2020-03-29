#include "game.h"

Q_GLOBAL_STATIC(Game, game)

Game *Game::instance()
{
    return game();
}

void Game::initialize()
{

}

void Game::receiveActive(int effectIndex)
{
//    if();
}
