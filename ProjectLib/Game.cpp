/**
 * @file Game.cpp
 * @author Shlok
 */

#include "pch.h"
#include "Coin.h"

#include "Game.h"
#include "Level.h"
#include "Football.h"

#include <wx/graphics.h>

/**
 * Initialize the game
 * Called once when the game starts
 */
void Game::Initialize()
{
    // Create and load the first level
    // Level::Load() will handle all the XML parsing and item creation
    mLevel = std::make_unique<Level>(this);
    mLevel->Load(L"levels/level1.xml");

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



    /// shifts pixels by an certain offset amount
    /// somewhat works, but maybe there is problem somewhere.
    /// note: this is not properly working, so will probably need to work on this
    /// -Venkata

    graphics->PushState();


    graphics->Translate(-mCameraOffsetX, 0);

    //
    // Draw level background first
    //
    if (mLevel != nullptr)
    {
        mLevel->OnDraw(graphics.get());
    }


    graphics->PopState();

    ///new logic for scireboard
    wxFont bigFont (wxSize(0,48), wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD);

    ///font and color setting it up
    graphics->SetFont(bigFont, wxColour(40,80,200));

    ///calculate total seconds and minutes
    int totalSeconds = static_cast<int>(mTimeElapsedSinceGameStarted);
    int minutes = totalSeconds/60;
    int seconds = totalSeconds % 60;

    ///drawing tmer and draw score
    wxString timerText = wxString::Format("%02d:%02d", minutes, seconds);

    graphics->DrawText(timerText, 20, 20);

    wxString scoreText = wxString::Format("%d", mPlayerScore);

    wxDouble textWidth, textHeight;
    graphics->GetTextExtent(scoreText, &textWidth, &textHeight);

    graphics->DrawText(scoreText,mScreenWidth/mScale- textWidth-40,20);


}

/**
 * Update the game state each frame.
 * Handles level updates, collision detection, camera movement,
 * and score/time tracking.
 * @param elapsed Time elapsed since the last update, in seconds.
 */
void Game::Update(double elapsed)
{
    if (mLevel != nullptr)
    {
        mLevel->Update(elapsed);
    }

    ///check for collisions between coin and football
    if (mFootball != nullptr && mLevel != nullptr)
    {
        const auto& items = mLevel->GetItems();

        for (auto& item : items) {
            Coin* coin = dynamic_cast<Coin*>(item.get());

            if (coin != nullptr && !coin ->CoinIsCollected())
            {

                /// calculate the distance between football and coin
                double dx = mFootball->GetX() - coin->GetX();
                double dy = mFootball->GetY() - coin->GetY();
                double distance = sqrt(dx * dx + dy * dy);

                /// if the football is close enough, it collected the coin
                if (distance < 50)  // 50 = approximate hit radius
                {
                    /// mark the coin as collected
                    coin->SetIsCollected(true);

                    /// add the coin’s value to the player score
                    AddToPlayerScore(coin->GetTheValue());
                }
            }
        }
    }


    // Update camera to follow football
    if (mFootball != nullptr && mScreenWidth > 0)
    {
        double virtualWidth = mScreenWidth / mScale;

        // Center camera on football's X position
        mCameraOffsetX = mFootball->GetX() - (virtualWidth / 2.0);

        // Clamp camera to level bounds so we don't show empty space
        double maxOffset = mLevel->GetWidth() - virtualWidth;
        mCameraOffsetX = std::max(0.0, std::min(mCameraOffsetX, maxOffset));
    }

    ///logic to update scoreboard
    mTimeElapsedSinceGameStarted += elapsed;

    ///add elapsed time to score secresing timer
    mTimerDecrease += elapsed;

    ///with every second decrease player score by 1
    ///also making sure never goes below 0
    if (mTimerDecrease >= 1.0)
        {
        mPlayerScore -=1;

        ///if score becomes negative , set to 0
        if (mPlayerScore < 0)
            {
            mPlayerScore = 0;
        }

        ///reset the timer
        mTimerDecrease=0.0;


    }
}

/**
 * Add points to the player’s score.
 * Called when the player collects coins.
 * @param points The number of points to add to the player's score.
 */
void Game::AddToPlayerScore(int points)
{
    mPlayerScore += points;

    if (mPlayerScore < 0)
        {
        mPlayerScore = 0;
    }

}

/**
 * Test for a collision between the given item and other items in the level.
 * @param item The item to test for collisions (usually the football).
 * @return The first item that collides with the given one, or nullptr if none.
 */
std::shared_ptr<Item> Game::CollisionTest(Item* item)
{
    if (mLevel == nullptr)
    {
        return nullptr;
    }

    // Ask the level to perform the collision test
    return mLevel->CollisionTest(item);
}
