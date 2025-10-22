/**
 * @file Game.cpp
 * @author Shlok
 */

#include "pch.h"
#include "Coin.h"

#include "Game.h"
#include "Level.h"
#include "Football.h"
#include "Enemy.h"
#include "UMichEnemy.h"
#include "NDEnemy.h"
#include "GoalPost.h"
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

    if (mFootball != nullptr && mFootball->IsDead())
    {
        mDeathMessageShown = true;

        mFootball->SetLocation(mLevel->GetInitialX(), mLevel->GetInitialY());
        mFootball->SetDead(false);
        mFootball->SetSpawnTime(0);
    }

    if (mDeathMessageShown)
    {
        wxFont font(wxSize(0, 60), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, wxColour(255, 0, 0)); // red color use

        wxString deathText = L"YOU LOSE!";
        wxDouble textWidth, textHeight;
        graphics->GetTextExtent(deathText, &textWidth, &textHeight);

        // center horizontally and vertically
        double x = (mScreenWidth / mScale - textWidth) / 2;
        double y = (mScreenHeight / mScale - textHeight) / 2;

        graphics->DrawText(deathText, x, y);
    }


}


/**
 *Helper function to get the next level like if on 1 , go to 2, if on 2 go to 3 etc
 */

std::wstring Game::GetNextLevelPath(const std:: wstring& currentLevelPath)
{
    ///wxLogMessage("DEBUG: Parsing level path in GetNextLevelPath(): %ls", currentLevelPath.c_str());

    int currentLevel = -1;

    size_t pos = currentLevelPath.rfind(L"level");
    if (pos != std::wstring::npos)
    {
        size_t start = pos +5;
        size_t end = start;
        while (end < currentLevelPath.size() && iswdigit(currentLevelPath[end]))
        {
            end++;
        }

        if (end > start)
        {
            std::wstring numberPart = currentLevelPath.substr(start, end - start);
            try
            {
                currentLevel = std::stoi(numberPart);
            }
            catch (...)
            {
                currentLevel = -1;
            }
        }

    }
    if (currentLevel == -1)
    {
        wxLogMessage("Could not determine current level from path: %ls", currentLevelPath.c_str());
        return L"";
    }

    int nextLevel = currentLevel + 1;
    ///wxLogMessage("DEBUG: Detected current level = %d, next = %d", currentLevel, nextLevel);


    if (nextLevel>3)
    {
        wxLogMessage("All levels completed");
        return L"";
    }

    std::wstring nextLevelPath = L"levels/level" + std::to_wstring(nextLevel) + L".xml";
    ///wxLogMessage("DEBUG: Next level path resolved = %ls", nextLevelPath.c_str());
    return nextLevelPath;
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

        for (auto& item : items)
            {
                item->OnCollide(mFootball.get());
            }
    }

    if (mFootball != nullptr && mLevel != nullptr)
    {
        if (mFootball->GetY() > mLevel->GetHeight())
        {
            mFootball->SetDead(true);
        }

        if (mFootball->IsDead() && !mDeathMessageShown)
        {
            mDeathMessageShown = true;
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

    if (mDeathMessageShown)
    {
        mdeathTimer += elapsed;
    }
    if (mdeathTimer >= 0.6)
    {
        mdeathTimer = 0.0;
        mDeathMessageShown = false;
    }




    if (mNextLevelPending)
    {
        wxLogMessage("Loading next level!");

        mLevel->Load(mNextLevelPath);

        ///wxLogMessage("DEBUG: mNextLevelPath actually loaded: %ls", mNextLevelPath.c_str());

        mFootball->SetDead(false);
        mFootball->SetLocation(mLevel->GetInitialX(), mLevel->GetInitialY());
        mCameraOffsetX = 0;
        mDeathMessageShown = false;

        wxLogMessage("Next level loaded successfully!");
        mNextLevelPending = false;

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


void Game::ShowDeathMessage()
{
    mDeathMessageShown = true;
}

void Game::LoadNextLevel(const std::wstring& nextLevelPath)
{
    mNextLevelPath = nextLevelPath;
    mNextLevelPending = true;
}
