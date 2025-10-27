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


/**
 * Initialize enemy movement by setting its
 * base position and vertical speed.
 */
void NDEnemy::StartMoving()
{
    Enemy::StartMoving();

    // Set a different speed for ND Enemy
    setSpeed(0,-60);
}