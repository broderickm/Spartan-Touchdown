/**
 * @file Football.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include <string>
#include "Football.h"
#include "Game.h"

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
 * @param level the game level we are adding this football to
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
}


/**
 * Draw the football
 * @param graphics the graphics used to draw
 */
void Football::Draw(wxGraphicsContext* graphics)
{

    double xPos, yPos;

    // Not moving
    if (!mIsGoingLeft && !mIsGoingRight)
    {
        int width = mCenterBitmap->GetWidth();
        int height = mCenterBitmap->GetHeight();

        xPos = GetX();
        yPos = GetY();

        graphics->DrawBitmap(*mCenterBitmap, xPos, yPos, width, height);
    }

    // Going left
    else if (mIsGoingLeft && !mIsGoingRight)
    {
        int width = mLeftBitmap->GetWidth();
        int height = mLeftBitmap->GetHeight();

        xPos = GetX();
        yPos = GetY();
        graphics->DrawBitmap(*mLeftBitmap, xPos, yPos, width, height);
    }

    // Going right
    else if (!mIsGoingLeft && mIsGoingRight)
    {
        int width = mRightBitmap->GetWidth();
        int height = mRightBitmap->GetHeight();

        xPos = GetX();
        yPos = GetY();
        graphics->DrawBitmap(*mRightBitmap, xPos, yPos, width, height);
    }
}

/**
 * Update the football each frame
 * @param elapsed Time elapsed since last update
 */
void Football::Update(double elapsed)
{
    Item::Update(elapsed);

    // current position as a vector
    Vector p(GetX(), GetY());

    // compute new velocity with gravity
    Vector newV(mV.X(), mV.Y()); // + Gravity * elapsed);

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

    auto game = GetGame();
    if (!game)
    {
        /// added thhis check bc of compiler issues
        wxLogError("in update: game pointer is null");
        return; // prevent crash
    }

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
    SetLocation(newP.X(), newP.Y());  // try horizontal movement only

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
    if (mIsOnSurface && collided == nullptr)
    {
        auto platform = GetGame()->CollisionTest(this);
        if (platform != nullptr)
        {
            newP.SetY(platform->GetY() - platform->GetHeight() / 2 - GetHeight() / 2 - Epsilon);
            newV.SetY(0);
        }
    }

    // new position
    mV = newV;
    SetLocation(newP.X(), newP.Y());
}

/**
 * Vertical collision test
 */
void Football::VerticalHitTest(std::shared_ptr<Item> collided, Vector& newV, Vector& newP)
{
    if (newV.Y() > 0) // falling down
    {
        // stop on top of collided item (platform)
        newP.SetY(collided->GetY() - collided->GetHeight() / 2 - GetHeight() / 2 - Epsilon);
        mIsOnSurface = true; // Mark as on surface
    }
    else if (newV.Y() < 0) // Moving upward
    {
        // stop just below ceiling
        newP.SetY(collided->GetY() + collided->GetHeight() / 2 + GetHeight() / 2 + Epsilon);
    }

    newV.SetY(0); // stop vertical motion after collision
}

/**
 * Horizontal collision test
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

void Football::Jump()
{
    // Only allow jumping if the football is on a surface
    if (mIsOnSurface)
    {
        mV.SetY(BounceSpeed); // Apply upward velocity (-800)
        mIsOnSurface = false; // No longer on surface after jumping
    }
}