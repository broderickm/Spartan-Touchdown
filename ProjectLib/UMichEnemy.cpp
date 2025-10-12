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
 * @param level the level we are adding this enemy to
 */
UMichEnemy::UMichEnemy(Level *level): Enemy(level, UMichImageName)
{

}
