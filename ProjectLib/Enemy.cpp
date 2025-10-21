/**
 * @file Enemy.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include "Enemy.h"
#include <set>

#include "Game.h"
#include "Level.h"

using namespace std;

/// Vertical Speed Constant
const double verticalSpeed = -80;

/// Vertical Distance Constant
const double maxVerticalDistance = 300;

/**
 * Constructor
 * Construct an enemy object
 * @param level the level we are adding this enemy to
 * @param filename Filename for the image we use
 */
Enemy::Enemy(Level *level, const std::wstring& filename): MovingItem(level,filename)
{
}

/**
 * Initialize enemy movement by setting its
 * base position and vertical speed.
 */
void Enemy::StartMoving()
{
    mBaseX = GetX();
    mBaseY = GetY();
    // set the speed in the final derivative class, if we want each enemy to have different speeds.

    setSpeed(0,verticalSpeed);
}


/**
 * Update the enemy’s position each frame based on its velocity and elapsed time.
 *
 * Handles vertical oscillation motion. The enemy moves up and down between
 * its base position and a maximum distance defined by maxVerticalDistance.
 *
 * @param elapsed The time elapsed since the last update (in seconds).
 */
void Enemy::Update(double elapsed)
{
   if (!hasMoved)
   {
       hasMoved = true;
       StartMoving();
   }
   double newX = GetX() + getSpeedX()*elapsed;
   double newY = GetY() + getSpeedY()*elapsed;
   double vertDistance = mBaseY - newY;

    SetX(newX);
    SetY(newY);

    if (vertDistance > maxVerticalDistance)
    {
        setSpeed(0,-verticalSpeed);
    }else if (vertDistance <= 0)
    {
        setSpeed(0,verticalSpeed);
    }
}

void Enemy::OnCollide(Football* football)
{
    if (football == nullptr)
        return;

    if (football->HitTest((int)GetX(), (int)GetY()))
    {
        football->SetDead(true);
        GetLevel()->GetGame()->ShowDeathMessage();
    }
}
