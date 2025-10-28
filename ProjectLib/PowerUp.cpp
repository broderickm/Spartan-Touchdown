/**
* @file PowerUp.cpp
 * @author Sanika Kapre
 *
 * Class that describes power up
 */

#include "pch.h"
#include "Football.h"
#include "PowerUp.h"

#include "Game.h"
#include "Level.h"

using namespace std;

/// File image for the powerup
const wstring PowerUpImageName = L"Images/sparty.png";
const double downspeed = 400;
const double maxsizeofmessage = 70;
const double imageupspeed = 700;
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
    if (!graphics || mFinishSequence)
    {
        return;
    }

    // Use the item's actual width/height instead of fixed POWERUP_SIZE
    double drawX = GetX() - GetWidth() / 2;
    double drawY = GetY() - GetHeight() / 2;

    if (mPowerUpImage.IsOk())
    {
        if (mPowerUpCollected)
        {
            graphics->DrawBitmap(mPowerUpImage, drawX, drawY, mNewImagewWidth, mNewImageHeight);
        }else
        {
            graphics->DrawBitmap(mPowerUpImage, drawX, drawY, GetWidth(), GetHeight());
        }

    }

    if (mPowerUpCollected && mPowerDisplayY >= 0)
    {

        wxFont font(wxSize(0, mPowerDisplaySize), wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, wxColour(128, 0, 128));

        // Format the text
        wxString textValue = L"Power Up!";

        // Get text dimensions for centering
        wxDouble textWidth, textHeight;
        graphics->GetTextExtent(textValue, &textWidth, &textHeight);

        // draw the text centered
        double xVal = mPowerDisplayX - textWidth / 2;
        double yVal = mPowerDisplayY - textHeight / 2;

        graphics->DrawText(textValue, xVal, yVal);
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
        if (!mPowerUpCollected) /// make sure we dont collect the power up after collecting it
        {
            mPowerDisplayX = GetX(); // set the message x cordinate
            mPowerDisplayY = GetY(); // set the message y cordinate
            mPowerDisplayDist = GetY();
            mNewImageHeight = GetHeight(); // set the images inital height
            mNewImagewWidth = GetWidth(); // set the images inital width
            mPowerUpCollected = true;
            ApplyEffect(football);
        }
    }
}

/**
 * Update the powerup each frame.
 * Applies wind force if the level has wind.
 * @param elapsed Time elapsed since last update in seconds
 */
void PowerUp::Update(double elapsed)
{
    // start updating once collected
    if (mPowerUpCollected && !mFinishSequence) // start making the powerup go down and shrink and show message
    {
        double newY = GetY() + imageupspeed * elapsed;
        SetY(newY);

        if (mNewImagewWidth > 0) // prevent image width from going into negatives;
        {
            mNewImageHeight-=5;
        }
        if (mNewImageHeight > 0) // prevent image height from going into negative;
        {
            mNewImagewWidth-=5;
        }

        if (mPowerDisplayY >= 0) // if our message is below the top of the screen
        {
            mPowerDisplayY = mPowerDisplayY - 500 * elapsed; // make the message travel upwards
            if (mPowerDisplaySize < maxsizeofmessage)
            {
                mPowerDisplaySize += 2.5; // increase the text size
            }
        }
        // if the text has gone past the top of the screen and image stop drawing the images.
        if (mPowerDisplayY <= 0 && GetY() >= GetLevel()->GetHeight())
        {
            mFinishSequence = true;
        }
    }
    else
    {
        return;
    }
}