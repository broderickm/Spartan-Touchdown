/**
 * @file Football.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include <string>
#include "Football.h"

#include "Coin.h"
#include "Game.h"
#include "InvulnerabilityPowerup.h"
#include "PowerUp.h"
#include "SpartyPowerup.h"

using namespace std;

/// Football filename Left
const wstring FootballLeftImageName = L"Images/footballLeft.png";

/// Football filename Right
const wstring FootballRightImageName = L"Images/footballRight.png";

/// Football filename Mid
const wstring FootballMidImageName = L"Images/footballMid.png";

/// Gravity in virtual pixels per second per second
const double Gravity = 1000.0;

/// Horizontal speed in pixels per second
const double HorizontalSpeed = 500.0;

/// Upwards vertical speed for bouncing
const double BounceSpeed = -800;

/// upwards step speed for bouncing ( tweak if necessary )
const double StepSpeed = -250;

/// Small value to prevent getting stuck in collision
const double Epsilon = 0.01;

/// value for maximum time in between our jumps ( when double jump is active ).
const double maxTimeInBetweenJumps = 1.7;


/**
 * Constructor
 * construct a football object
 * the game level we are adding this football to
 */
Football::Football(Level *level): MovingItem(level, FootballMidImageName)
{
    // Center
    mCenterImage = std::make_unique<wxImage>(FootballMidImageName, wxBITMAP_TYPE_ANY);
    mCenterBitmap =  std::make_unique<wxBitmap>(*mCenterImage);

    // Left
    mLeftImage = std::make_unique<wxImage>(FootballLeftImageName, wxBITMAP_TYPE_ANY);
    mLeftBitmap = std::make_unique<wxBitmap>(*mLeftImage);

    // Right
    mRightImage = std::make_unique<wxImage>(FootballRightImageName, wxBITMAP_TYPE_ANY);
    mRightBitmap = std::make_unique<wxBitmap>(*mRightImage);

    // Set normal gravity
    mGravity = Gravity;
}


/**
 * Draw the football
 *  the graphics used to draw
 */
void Football::Draw(wxGraphicsContext* graphics)
{

    double xPos, yPos;

    // Not moving
    if ((!mIsGoingLeft && !mIsGoingRight) || (mIsGoingLeft && mIsGoingRight))
    {
        int width = mCenterBitmap->GetWidth();
        int height = mCenterBitmap->GetHeight();

        xPos = GetX() - width / 2;
        yPos = GetY() - height / 2;

        graphics->DrawBitmap(*mCenterBitmap, xPos, yPos, width, height);
    }

    // Going left
    else if (mIsGoingLeft && !mIsGoingRight)
    {
        int width = mLeftBitmap->GetWidth();
        int height = mLeftBitmap->GetHeight();

        xPos = GetX() - width / 2;
        yPos = GetY() - height / 2;
        graphics->DrawBitmap(*mLeftBitmap, xPos, yPos, width, height);
    }

    // Going right
    else if (!mIsGoingLeft && mIsGoingRight)
    {
        int width = mRightBitmap->GetWidth();
        int height = mRightBitmap->GetHeight();

        xPos = GetX() - width / 2;
        yPos = GetY() - height / 2;
        graphics->DrawBitmap(*mRightBitmap, xPos, yPos, width, height);
    }
}

/**
 * Update the football each frame
 * param elapsed Time elapsed since last update
 */
void Football::Update(double elapsed)
{
    // current position as a vector
    Vector p(GetX(), GetY());
    Vector newV;

    if (mSpawnTime < 1 || mIsDead)
    {
        newV.SetX(0);
        newV.SetY(0);
    }
    else
    {
        // compute new velocity with gravity
        newV.SetX(mV.X());
        newV.SetY(mV.Y() + mGravity * elapsed);

        // apply horizontal movement input
        if (mIsGoingLeft && !mIsGoingRight)
        {
            newV.SetX(-HorizontalSpeed);
        }
        else if (mIsGoingRight && !mIsGoingLeft)
        {
            newV.SetX(HorizontalSpeed);
        }
        else
        {
            newV.SetX(0);
        }
    }

    // compute new position using velocity
    Vector newP = p + newV * elapsed;

    auto game = GetGame();
    if (!game)
    {
        /// added thhis check bc of compiler issues
        wxLogError("in update: game pointer is null");
        return; // prevent crash
    }

    // vertical hit test
    SetLocation(p.X(), newP.Y());  // vertical movement only

    auto collided = GetGame()->CollisionTest(this);
    if (collided != nullptr)
    {
        // if we collided wi coin or powerup, collect immediately
        if (dynamic_cast<Coin*>(collided.get()) != nullptr ||
            dynamic_cast<PowerUp*>(collided.get()) != nullptr)
        {
            // do nothing here — handled later
        }
        else
        {
            if (newV.Y() > 0)
            {
                // falling down - land on platform
                newP.SetY(collided->GetY() - collided->GetHeight() / 2 - GetHeight() / 2 - Epsilon);
                mIsOnSurface = true;
                // stop stepping incase of collision
                mIsStepping = false;
            }
            else if (newV.Y() < 0)
            {
                // going up
                newP.SetY(collided->GetY() + collided->GetHeight() / 2 + GetHeight() / 2 + Epsilon);
            }

            // stop vertical motion
            newV.SetY(0);
        }
    }
    else
    {
        mIsOnSurface = false;
    }

    // horizontal hit test
    SetLocation(newP.X(), newP.Y());  // try horizontal movement only

    collided = GetGame()->CollisionTest(this);
    if (collided != nullptr)
    {
        // Skip physics for coins and powerups entirely - they should never block movement
        bool isCollectible = (dynamic_cast<Coin*>(collided.get()) != nullptr ||
                              dynamic_cast<PowerUp*>(collided.get()) != nullptr);

        if (!isCollectible)
        {
            if (newV.X() > 0)
            {
                // moving right; stop at wall
                newP.SetX(collided->GetX() - collided->GetWidth() / 2 - GetWidth() / 2 - Epsilon);
            }
            else if (newV.X() < 0)
            {
                // moving left; stop at wall
                newP.SetX(collided->GetX() + collided->GetWidth() / 2 + GetWidth() / 2 + Epsilon);
            }
        }

        // stop horizontal motion
        newV.SetX(0);
    }
    if (mIsOnSurface && collided == nullptr)
    {
        auto platform = GetGame()->CollisionTest(this);
        if (platform != nullptr)
        {
            newP.SetY(platform->GetY() - platform->GetHeight() / 2 - GetHeight() / 2 - Epsilon);
            newV.SetY(0);
        }
    }

    auto level = GetGame()->GetLevel();
    auto collidedItem = level->CollisionTest(this);

    if (collidedItem != nullptr)
    {
        if (auto coin = std::dynamic_pointer_cast<Coin>(collidedItem))
        {
            /**int value = static_cast<int>((coin->GetTheValue() * GetGame()->GetCoinMultiplier()));
            game->AddToPlayerScore(value); // update football score
            level->RemoveItem(coin); // remove coin when colided
            */
        }
        else if (auto invulnPowerup = std::dynamic_pointer_cast<InvulnerabilityPowerup>(collidedItem))
        {
            // // Apply invulnerability effect
            // ActivateInvulnerability(20.0);  // 20 seconds of invulnerability
            //
            // // Remove powerup from level
            // level->RemoveItem(invulnPowerup);
        }
        else if (auto Sparty = std::dynamic_pointer_cast<SpartyPowerup>(collidedItem))
        {
            // game->SetCoinMultiplier(2.0); // update football score
            // level->RemoveItem(Sparty); // remove powerup when colided
        }
        else if (auto lightning = std::dynamic_pointer_cast<InvulnerabilityPowerup>(collidedItem))
        {
            // game->GetFootball()->ActivateInvulnerability(20.0); // update football score
            // level->RemoveItem(Sparty); // remove powerup when colided
        }

    }
    /// stop the stepping if we performed a full step
    /// this is needed so incase we step off a ledge and free fall for some time we cant keep spamming jump
    /// while free falling
    if (mIsStepping && mV.Y() >= -StepSpeed)
    {
        mIsStepping = false;
    }

    // new position
    mV = newV;
    SetLocation(newP.X(), newP.Y());

    // Increment SpawnTime
    mSpawnTime += elapsed;

    if (mIsInvulnerable)
    {
        mInvulnerabilityTimeRemaining -= elapsed;
        if (mInvulnerabilityTimeRemaining <= 0.0)
        {
            mIsInvulnerable = false;
            mInvulnerabilityTimeRemaining = 0.0;
        }
    }

    if (mDoubleJumpTimeElapsed >= 50)
    {
        mDoubleJump = false;
        mDoubleJumpTimeElapsed = 0.0;
    }

    if (mSpaceKeyElasped >= maxTimeInBetweenJumps)
    {
        mInitJump = false;
        mSpaceKeyElasped = 0.0;
    }

    if (mDoubleJump)
    {
     mDoubleJumpTimeElapsed += elapsed;
    }

    if (mInitJump)
    {
        mSpaceKeyElasped += elapsed;
    }


}

void Football::ActivateInvulnerability(double duration)
{
    mIsInvulnerable = true;
    mInvulnerabilityTimeRemaining = duration;
}

/**
 * Handle a vertical collision between the football and another item.
 * aram collided The item the football collided with.
 * param newV The current velocity vector to adjust after collision.
 * param newP The current position vector to adjust after collision.
 */
void Football::VerticalHitTest(std::shared_ptr<Item> collided, Vector& newV, Vector& newP)
{
    if (newV.Y() > 0) // falling down
    {
        // stop on top of collided item (platform)
        newP.SetY(collided->GetY() - collided->GetHeight() / 2 - GetHeight() / 2 - Epsilon);
        mIsOnSurface = true; // Mark as on surface
        mIsStepping = false;
    }
    else if (newV.Y() < 0) // Moving upward
    {
        // stop just below ceiling
        newP.SetY(collided->GetY() + collided->GetHeight() / 2 + GetHeight() / 2 + Epsilon);
    }

    newV.SetY(0); // stop vertical motion after collision
}

/**
 * Handle a horizontal collision between the football and another item.
 * param collided The item the football collided with.
 * param newV The current velocity vector to adjust after collision.
 * param newP The current position vector to adjust after collision.
 */
void Football::HorizontalHitTest(std::shared_ptr<Item> collided, Vector& newV, Vector& newP)
{
    if (newV.X() > 0) // moving right
    {
        // stop at left side of collided item (wall/platform)
        newP.SetX(collided->GetX() - collided->GetWidth() / 2 - GetWidth() / 2 - Epsilon);
    }
    else if (newV.X() < 0) // Moving left
    {
        // stop at right side of collided item (wall/platform)
        newP.SetX(collided->GetX() + collided->GetWidth() / 2 + GetWidth() / 2 + Epsilon);
    }

    newV.SetX(0); // stop horizontal motion after collision
}

/**
 * Make the football jump if it is currently resting on a surface.
 */
void Football::Jump()
{
    // Only allow jumping if the football is on a surface
    // allow jumping if in the middle of stepping
    if (( mIsOnSurface || (!mIsOnSurface && mIsStepping) ) && !mInitJump)
    {
        mV.SetY(BounceSpeed); // Apply upward velocity (-800)
        mIsOnSurface = false; // No longer on surface after jumping
        mIsStepping = false; // no longer stepping if we jumped
        mInitJump = true; // indicating the first jump, has been performed.
    }else if (!mIsOnSurface && mDoubleJump && mInitJump)
    {
        mV.SetY(BounceSpeed); // Apply upward velocity (-800)
        mIsOnSurface = false;
        mIsStepping = false;
        mInitJump = false;
    }
}

/**
 *params none
 *returns void
 *  function performs a step when moving right or left
 *  simply adds vertical velocity to simulate a very slight upwards movement
 *  make sure we dont step if we are in the middle of stepping
 *
 */
void Football::Step()
{
    if (mIsOnSurface)
    {
        if (!mIsStepping)
        {
            mV.SetY(StepSpeed);
            mIsStepping = true;
        }
    }
}


/**
 * @brief Adds to the football’s internal score counter.
 * param value The amount to increase the score by.
 */
void Football::AddToScore(int value)
{
    mScore += value;
}
