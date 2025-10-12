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
 * @param level the level we are adding this enemy to
 */
NDEnemy::NDEnemy(Level* level): Enemy(level, UMichImageName)
{

}
