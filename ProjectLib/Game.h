/**
 * @file Game.h
 * @author Shlok
 *
 * class that describes the game
 */


#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H

#include "Football.h"
#include "Item.h"
#include "Level.h"

/// forward declerations of classes
class Level;

///forward declaration for class football
class Football;

/// Game area height in virtual pixels
const static int Height = 1024;

/**
 * Class that describes game
 */
class Game
{
private:
    /// Flag to say if the next level is being loaded
    bool mNextLevelPending = false;

    /// The wstring path to the next file
    std::wstring mNextLevelPath;

    /// Flag to show if message already shown
    bool mDeathMessageShown = false;

    /// Elapsed time since the level started
    double mTimeElapsedSinceGameStarted=0.0;

    /// Score acquired by the player
    int mPlayerScore = 0;

    /// Timer element that tracks decreasing of the score
    double mTimerDecrease = 0.0;

    /// Scale from virtual pixels to screen pixels
    double mScale = 0;

    /// The current level
    std::unique_ptr<Level> mLevel;

    /// The football (player)
    std::shared_ptr<Football> mFootball;

    /// Camera offset for scrolling
    double mCameraOffsetX = 0;

    /// Screen dimensions (for camera calculations)
    int mScreenWidth = 0;

    /// Height of the playable screen in pixels
    int mScreenHeight = 0;

    /// Coin multiplier applied to coins
    double mCoinMultiplier = 1.0;

    /// Timer to track time since death
    double mDeathTimer =  0.0;

    /// Flag to keep track of if a level has been completed message is shown
    bool mLevelCompleteMessage = false;

    /// Keeps track if level is complete
    bool mLevelComplete = false;

    /// Timer to track time since completion
    double mCompleteTimer =  0.0;

    /// Flag to show level start message
    bool mShowLevelStartMessage = false;

    /// The current level start message text
    std::wstring mLevelStartMessage = L"";

public:

    void LoadNextLevel(const std::wstring& nextLevelPath);

    void ShowDeathMessage();

    std::wstring GetNextLevelPath(const std::wstring& currentLevelPath);

    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Update(double elapsed);

    void UpdateSingleStep(double elapsed);

    void Initialize();

    /**
     * Get pointer to the football
     * @return Pointer to football object
     */
    std::shared_ptr<Football> GetFootball() { return mFootball; }

    /**
     * Set the football (called by Level when creating it)
     * @param football The football object
     */
    void SetFootball(std::shared_ptr<Football> football) { mFootball = football; }

    /**
     * Get pointer to the current level
     * @return Pointer to level object
     */
    Level* GetLevel() { return mLevel.get(); }

    /**
     * Convert screen X coordinate to world X coordinate
     * @param screenX Screen X position
     * @return World X position
     */
    double ScreenToWorldX(int screenX) const { return screenX / mScale + mCameraOffsetX; }

    /**
     * Convert screen Y coordinate to world Y coordinate
     * @param screenY Screen Y position
     * @return World Y position
     */
    double ScreenToWorldY(int screenY) const { return screenY / mScale; }

    void AddToPlayerScore(int points);

    /**
     * Get the current player score.
     * @return The player’s score
     */
    int GetPlayerScore() { return mPlayerScore; }

    /**
     * Get the time elapsed since the game started.
     * @return Elapsed time in seconds.
     */
    double GetTimeElapsedSinceGameStarted() const { return mTimeElapsedSinceGameStarted; }


    std::shared_ptr<Item> CollisionTest(Item* item);

    /**
     * For coin multiplier when using power up
     * @return coin multiplier being applied
     */
    double GetCoinMultiplier() const { return mCoinMultiplier; }

    /**
     * Sets the coin multiplier (used when applying power-ups)
     * @param mult the multiplier being applied
     */
    void SetCoinMultiplier(double mult) { mCoinMultiplier = mult; }

    /**
     * Setter for the level complete
     * @param cond says if level is complete
     */
    void SetLevelComplete(bool cond) {mLevelComplete = cond; }

    /**
     * Setter for score when level is complete
     * @param score to set to
     */
    void SetPlayerScore(int score) {mPlayerScore = score; }

    /**
     * Set the level start message text
     * @param message The message to display
     */
    void SetLevelStartMessage(const std::wstring& message) { mLevelStartMessage = message; }

    /**
     * Reset the game timer when starting or switching levels manually.
     */
    void ResetTimer()
    {
        mTimeElapsedSinceGameStarted = 0.0;
        mTimerDecrease = 0.0;
    }


};


#endif //PROJECT1_GAME_H