/**
 * @file Football.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include <string>
#include "Football.h"

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

/// Small value to prevent getting stuck in collision
const double Epsilon = 0.01;


/**
 * Constructor
 * @param game the game we are adding this football to
 */
Football::Football(Level *level): MovingItem(level, FootballMidImageName)
{

}

void Football::Update(double elapsed)
{
    Item::Update(elapsed);

    // current position as a vector
    Vector p(GetX(), GetY());

    // compute new velocity with gravity
    Vector newV(mV.X(), mV.Y() + Gravity * elapsed);

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

    // compute new position using velocity
    Vector newP = p + newV * elapsed;

    // vertical hit test
    SetLocation(p.X(), newP.Y());  // try vertical movement only

    auto collided = GetGame()->CollisionTest(this);
    if (collided != nullptr)
    {
        if (newV.Y() > 0)
        {
            // falling down; land on platform
            newP.SetY(collided->GetY() - collided->GetHeight() / 2 - GetHeight() / 2 - Epsilon);
            mIsOnSurface = true;
        }
        else if (newV.Y() < 0)
        {
            // going up; hit ceiling
            newP.SetY(collided->GetY() + collided->GetHeight() / 2 + GetHeight() / 2 + Epsilon);
        }

        // stop vertical motion
        newV.SetY(0);
    }
    else
    {
        mIsOnSurface = false;
    }


    // horizontal hit test
    SetLocation(newP.X(), p.Y());  // try horizontal movement only

    collided = GetGame()->CollisionTest(this);
    if (collided != nullptr)
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

        // stop horizontal motion
        newV.SetX(0);
    }

    // new position
    mV = newV;
    SetLocation(newP.X(), newP.Y());
}