/**
 * @file Enemy.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include "Enemy.h"


using namespace std;



/**
 * Constructor
 * @param game the game we are adding this enemy to
 * @param filename Filename for the image we use
 */
Enemy::Enemy(Game* game, const std::wstring& filename): MovingItem(game,filename)
{

}
