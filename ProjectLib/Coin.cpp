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
    if (!graphics || mCoinCollected)
    {
        return; // Nothing to draw on
    }

    double drawX = GetX() - COIN_SIZE / 2;
    double drawY = GetY() - COIN_SIZE / 2;
    if (mCoinImage.IsOk())
    {
        graphics->DrawBitmap(mCoinImage, drawX, drawY, COIN_SIZE, COIN_SIZE);
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
        if (auto game = GetLevel()->GetGame())
        {
            game->AddToPlayerScore(mCoinValue);
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
