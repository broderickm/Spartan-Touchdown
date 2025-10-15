/**
 * @file Enemy.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include "Enemy.h"

#include <set>


using namespace std;

const double verticalSpeed = -80;
const double maxVerticalDistance = 300;


/**
 * Constructor
 * @param level the level we are adding this enemy to
 * @param filename Filename for the image we use
 */
Enemy::Enemy(Level *level, const std::wstring& filename): MovingItem(level,filename)
{

}



/**
 * sets the base position
 * sets the speed
 */
void Enemy::StartMoving()
{
    mBaseX = GetX();
    mBaseY = GetY();
    // set the speed in the final derivative class, if we want each enemy to have different speeds.

    setSpeed(0,verticalSpeed);
}


/**
 * change item position based upon velocity*elapsedtime
 * if the item hasmoved = false set it to true and then proceed
 * function is responsible for the movement of the enemy ( up and down movement )
 * we can change the rate by increasing vertspeed, and the we can change the distance by increase maxdistance
 * @param elapsed
 * @returns none
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
