/**
 * @file Enemy.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include "Enemy.h"


using namespace std;



/**
 * Constructor
 * @param level the level we are adding this enemy to
 * @param filename Filename for the image we use
 */
Enemy::Enemy(Level *level, const std::wstring& filename): MovingItem(level,filename)
{

}
