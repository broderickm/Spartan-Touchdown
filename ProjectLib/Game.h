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
class Football;

/**
 * Class that describes game
 */
class Game
{
private:
    bool mNextLevelPending = false;
    std::wstring mNextLevelPath;
    ///flag to show if message already shown
    bool mDeathMessageShown = false;

    ///Elapsed time since the level started
    double mTimeElapsedSinceGameStarted=0.0;

    ///score aquired by yhte player
    int mPlayerScore = 0;

    ///timer element that tracks decreasing of the score
    double mTimerDecrease = 0.0;


    /// Game area height in virtual pixels
    const static int Height = 1024;

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

public:
    /**
     * Get the next level file path
     * @param currentLevelPath Current level file path
     * @return Next level file path if available, else empty string
     */
    std::wstring GetNextLevelPath(const std::wstring& currentLevelPath);



    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Update the game state each frame.
     * Handles level updates, collision detection, camera movement,
     * and score/time tracking.
     * @param elapsed Time elapsed since the last update, in seconds.
     */
    void Update(double elapsed);

    /**
     * Initializes the game
     */
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

    /**
     * Add points to the player’s score.
     * Called when the player collects coins.
     * @param points The number of points to add to the player's score.
     */
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

    /**
     * Test for a collision between the given item and other items in the level.
     * @param item The item to test for collisions (usually the football).
     * @return The first item that collides with the given one, or nullptr if none.
     */
    std::shared_ptr<Item> CollisionTest(Item* item);
};


#endif //PROJECT1_GAME_H