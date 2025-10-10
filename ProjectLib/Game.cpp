/**
 * @file Game.cpp
 * @author Shlok
 */

#include "pch.h"
#include "Game.h"

#include <wx/graphics.h>

/**
 * Draw the game area
 * @param graphics The wxWidgets graphics context on which to draw
 * @param width Width of the client window
 * @param height Height of the client window
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    /**
     * Add an item to the game
     * @param item Item to add
     */
    void Add(std::shared_ptr<Item> item);

    //
    // Automatic Scaling
    //
    mScale = double(height) / double(Height);
    graphics->Scale(mScale, mScale);

    auto virtualWidth = (double)width/mScale;
    graphics->PushState();

    //
    // Draw in virtual pixels on the graphics context
    //
    for (auto item : mItems)
    {
        item->Draw(graphics.get());
    }

    graphics->PopState();
}

/**
 * Update the game state
 * @param elapsed Time elapsed since last update in seconds
 */
void Game::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}