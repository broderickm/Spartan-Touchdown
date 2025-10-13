/**
 * @file Game.cpp
 * @author Shlok
 */

#include "pch.h"
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

    // Initialize football in someway?
    //mFootball = std::make_unique<Football>(mLevel.get());
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
        mLevel->OnDraw(graphics.get());
    }

    // Draw football?
    if (mFootball != nullptr)
    {
        mFootball->Draw(graphics.get());
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
 * Update the game state
 * @param elapsed Time elapsed since last update in seconds
 */
void Game::Update(double elapsed)
{
    if (mLevel != nullptr)
    {
        mLevel->Update(elapsed);
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

/**add points to player score
 *when player colets coins called at that time
 *pounts- no of points to add
 *
 */
void Game::AddToPlayerScore(int points)
{
    mPlayerScore += points;

    if (mPlayerScore < 0)
        {
        mPlayerScore = 0;
    }

}
