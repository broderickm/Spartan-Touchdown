/**
 * @file Game.cpp
 * @author Shlok
 */

#include "pch.h"
#include "Game.h"

#include <wx/graphics.h>


/**
 * Initialize the game
 * Called once when the game starts
 */
void Game::Initialize()
{
    // Create and load the first level
    // Level::Load() will handle all the XML parsing and item creation
    //mLevel = std::make_unique<Level>(this);
    //mLevel->Load(L"levels/level1.xml");
}

/**
 * Add an item to the game
 * Called by Level when loading items from XML
 * @param item Item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Draw the game area
 * @param graphics The wxWidgets graphics context on which to draw
 * @param width Width of the client window
 * @param height Height of the client window
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    mScreenWidth = width;
    mScreenHeight = height;

    //
    // Automatic Scaling
    //
    mScale = double(height) / double(Height);
    graphics->Scale(mScale, mScale);
    auto virtualWidth = (double)width/mScale;

    graphics->PushState();
    graphics->Translate(-mCameraOffsetX, 0);

    //
    // Draw level background first
    //
    if (mLevel != nullptr)
    {
        //mLevel->DrawBackground(graphics.get());
    }

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

    // Update camera to follow football
    if (mFootball != nullptr && mScreenWidth > 0)
    {
        double virtualWidth = mScreenWidth / mScale;

        // Center camera on football's X position
        mCameraOffsetX = mFootball->GetX() - (virtualWidth / 2.0);

        // Clamp camera to level bounds so we don't show empty space
        if (mLevel != nullptr)
        {
            //double maxOffset = mLevel->GetWidth() - virtualWidth;
            //mCameraOffsetX = std::max(0.0, std::min(mCameraOffsetX, maxOffset));
        }
    }
}

/**
 * Set the current level
 * Called by Level after it loads from XML
 * (might not be necessary but it's here in case it is)
 * @param level The loaded level
 */
void Game::SetLevel(std::shared_ptr<Level> level)
{
    //mLevel = level;
}