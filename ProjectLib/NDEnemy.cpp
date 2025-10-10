/**
 * @file NDEnemy.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include "NDEnemy.h"

using namespace std;

/// UMich filename
const wstring UMichImageName = L"Images/ND.png";

/**
 * Constructor
 * @param game, the game we are adding this enemy to
 * @param filename Filename for the image we use
 */
NDEnemy::NDEnemy(Game* game): Enemy(game, UMichImageName)
{

}
