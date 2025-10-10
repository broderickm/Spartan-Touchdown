/**
 * @file UMichEnemy.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include "UMichEnemy.h"

using namespace std;

/// UMich filename
const wstring UMichImageName = L"Images/U-M.png";



/**
 * Constructor
 * @param game, the game we are adding this enemy to
 * @param filename Filename for the image we use
 */
UMichEnemy::UMichEnemy(Game* game): Enemy(game, UMichImageName)
{

}
