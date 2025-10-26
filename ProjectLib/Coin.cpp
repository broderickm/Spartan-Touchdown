/**
* @file Coin.cpp
 * @author Sanika Kapre
 *
 * Class that describes coins
 */

#include "pch.h"
#include "Coin.h"
#include "Game.h"
#include "Item.h"

/**
 * Create a coin with an image and a point value.
 * @param level  The level this coin belongs to
 * @param image The image filename (e.g., L"images/coin10.png" or L"images/coin100.png")
 * @param value The point value (10 for silver coin, 100 for gold coin)
 */
Coin::Coin(Level *level, const std::wstring& image, int value)
        : Item(level, image),
        mCoinImage(image, wxBITMAP_TYPE_ANY),
        mCoinValue(value)
{
}

/**
 * Draw the coin at its current position on the screen.
 * @param graphics The graphics context used to draw
 */
void Coin::Draw(wxGraphicsContext* graphics)
{
    if (!graphics)
    {
        return; // Nothing to draw on
    }

    double drawX = GetX() - COIN_SIZE / 2;
    double drawY = GetY() - COIN_SIZE / 2;

    // Draw the coin if it's flying (not yet fully deleted)
    if (mIsFlying && mCoinImage.IsOk())
    {
        graphics->DrawBitmap(mCoinImage, drawX, drawY, COIN_SIZE, COIN_SIZE);
    }
    else if (!mCoinCollected && mCoinImage.IsOk())
    {
        graphics->DrawBitmap(mCoinImage, drawX, drawY, COIN_SIZE, COIN_SIZE);
    }

    // Draw the point value text for 1 second after collection
    if (mCoinCollected && mTextDisplayTimer < TEXT_DISPLAY_DURATION)
    {
        // Create font for the value text
        wxFont font(wxSize(0, 40), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, wxColour(255, 215, 0)); // Gold color

        // Format the text
        wxString valueText = wxString::Format("+%d", mDisplayValue);

        // Get text dimensions for centering
        wxDouble textWidth, textHeight;
        graphics->GetTextExtent(valueText, &textWidth, &textHeight);

        // Draw text at collection position, centered
        double textX = mCollectionX - textWidth / 2;
        double textY = mCollectionY - textHeight / 2;

        graphics->DrawText(valueText, textX, textY);
    }

}


/**
 * Handle collision between this coin and the football.
 * @param football The football that collided with this coin.
 */
void Coin::OnCollide(Football* football)
{
    if (mCoinCollected || football == nullptr)
    {
        return;
    }

    // Compute the distance between football and coin center
    double dx = football->GetX() - GetX();
    double dy = football->GetY() - GetY();
    double distance = std::sqrt(dx * dx + dy * dy);

    // If within hit radius, collect
    if (distance < 50)
    {
        mCoinCollected = true;
        mIsFlying = true;

        // Store collection position for text display
        mCollectionX = GetX();
        mCollectionY = GetY();

        if (auto game = GetLevel()->GetGame())
        {
            int value = static_cast<int>(mCoinValue * game->GetCoinMultiplier());
            mDisplayValue = value;
            game->AddToPlayerScore(value);
        }

    }
}

/**
 * Update the coin each frame.
 * Applies wind force if the level has wind.
 * @param elapsed Time elapsed since last update in seconds
 */
void Coin::Update(double elapsed)
{
    // If coin is collected and flying
    if (mCoinCollected && mIsFlying)
    {
        // Update timers
        mTextDisplayTimer += elapsed;
        mFlyingTimer += elapsed;

        // Move coin upward
        SetLocation(GetX(), GetY() + FLYING_SPEED * elapsed);

        // After flying off screen (2 seconds), mark for deletion
        if (mFlyingTimer >= 2.0)
        {
            mIsFlying = false;
            // The coin will be removed by the level when it detects mCoinCollected
        }

        return;
    }

    // Don't move collected coins
    if (mCoinCollected)
    {
        return;
    }

    // Apply wind force from the level
    double windVelocity = GetLevel()->GetWindVelocity();
    if (windVelocity != 0.0)
    {
        // Move coin based on wind
        SetLocation(GetX() + windVelocity * elapsed, GetY());
    }
}
