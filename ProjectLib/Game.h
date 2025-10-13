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
    int mScreenHeight = 0;

public:
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Update the game state
     * @param elapsed Time elapsed since last update in seconds
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
    Football* GetFootball() { return mFootball.get(); }

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
};


#endif //PROJECT1_GAME_H