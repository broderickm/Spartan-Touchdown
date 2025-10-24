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

    ///previous logic only worked when venters collined
    ///editied now even if brushes edges triggers you lose

    ///get dimensions
    double enemyWidth = GetWidth();
    double enemyHeight = GetHeight();
    double ballWidth = football->GetWidth();
    double ballHeight = football->GetHeight();

    ///computinf corners for enemy
    double enemyLeft = GetX() - enemyWidth / 2.0;
    double enemyTop = GetY() - enemyHeight / 2.0;
    double enemyRight = enemyLeft + enemyWidth;
    double enemyBottom = enemyTop + enemyHeight;

    ///computing corners for fooyballl
    double ballLeft = football->GetX() - ballWidth / 2.0;
    double ballTop = football->GetY() - ballHeight / 2.0;
    double ballRight = ballLeft + ballWidth;
    double ballBottom = ballTop + ballHeight;


    ///collision not possible case
    bool noOverlap =
        (enemyRight < ballLeft)  ||  // enemy is left of football
        (enemyLeft > ballRight)  ||  // enemy is right of football
        (enemyBottom < ballTop)  ||  // enemy is above football
        (enemyTop > ballBottom);     // enemy is below football

    if (noOverlap)
    {
        return; // skip the rest, no they touch
    }


    wxImage enemyImage = GetBitmap()->ConvertToImage();
    wxImage ballImage = football->GetBitmap()->ConvertToImage();

    ///check pixels
    int overlapLeft = static_cast<int>(std::max(enemyLeft, ballLeft));
    int overlapRight = static_cast<int>(std::min(enemyRight, ballRight));
    int overlapTop = static_cast<int>(std::max(enemyTop, ballTop));
    int overlapBottom = static_cast<int>(std::min(enemyBottom, ballBottom));

    for (int screenX = overlapLeft; screenX < overlapRight; ++screenX) {
        for (int screenY = overlapTop; screenY < overlapBottom; ++screenY)
        {
            int enemyPixelX = static_cast<int>(screenX - enemyLeft);
            int enemyPixelY = static_cast<int>(screenY - enemyTop);

            int ballPixelX = static_cast<int>(screenX - ballLeft);
            int ballPixelY = static_cast<int>(screenY - ballTop);

            bool insideEnemy =
                enemyPixelX >= 0 && enemyPixelX < enemyWidth &&
                enemyPixelY >= 0 && enemyPixelY < enemyHeight;

            bool insideBall =
                ballPixelX >= 0 && ballPixelX < ballWidth &&
                ballPixelY >= 0 && ballPixelY < ballHeight;

            if (insideEnemy && insideBall)
            {
                bool enemyVisible = !enemyImage.IsTransparent(enemyPixelX, enemyPixelY);
                bool ballVisible = !ballImage.IsTransparent(ballPixelX, ballPixelY);

                if (enemyVisible && ballVisible)
                {
                    football->SetDead(true);
                    GetLevel()->GetGame()->ShowDeathMessage();
                    return;
                }
            }
        }
    }


}
