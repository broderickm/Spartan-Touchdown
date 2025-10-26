/**
* @file PowerUp.cpp
 * @author Sanika Kapre
 *
 * Class that describes power up
 */

#include "Football.h"
using namespace std;

#include "pch.h"
#include "PowerUp.h"
#include "Level.h"

/// File image for the powerup
const wstring PowerUpImageName = L"Images/sparty.png";

/**
 * Constructor of the PowerUp
 * @param level the level the powerup is in
 */
PowerUp::PowerUp(Level* level, const std::wstring& image)
    : Item(level, image), mPowerUpImage(image, wxBITMAP_TYPE_ANY)
{
}

/**
 * Draw the power-up at its current position on the screen.
 * @param graphics The graphics context used to draw
 */
void PowerUp::Draw(wxGraphicsContext* graphics)
{
    if (!graphics || mPowerUpCollected)
    {
        return;
    }

    // Use the item's actual width/height instead of fixed POWERUP_SIZE
    double drawX = GetX() - GetWidth() / 2;
    double drawY = GetY() - GetHeight() / 2;

    if (mPowerUpImage.IsOk())
    {
        graphics->DrawBitmap(mPowerUpImage, drawX, drawY, GetWidth(), GetHeight());
    }
}

/**
 * Handle collision between this power-up and the football.
 * @param football The football that collided with this power-up.
 */
void PowerUp::OnCollide(Football* football)
{
    if (mPowerUpCollected || football == nullptr)
    {
        return;
    }

    // Compute the distance between football and power-up center
    double dx = football->GetX() - GetX();
    double dy = football->GetY() - GetY();
    double distance = std::sqrt(dx * dx + dy * dy);

    // If within hit radius, collect
    if (distance < 50)
    {
        mPowerUpCollected = true;
        ApplyEffect(football);
    }
}

/**
 * Update the powerup each frame.
 * Applies wind force if the level has wind.
 * @param elapsed Time elapsed since last update in seconds
 */
void PowerUp::Update(double elapsed)
{
    // stop updating once collected
    if (mPowerUpCollected)
    {
        // Move off of screen if hit here
    }
    else
    {
        return;
    }
}