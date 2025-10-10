/**
 * @file Game.h
 * @author Shlok
 *
 * class that describes the game
 */


#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H
#include "Item.h"

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
    /// All items in the game
    std::vector<std::shared_ptr<Item>> mItems;
public:
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Update the game state
     * @param elapsed Time elapsed since last update in seconds
     */
    void Update(double elapsed);
};


#endif //PROJECT1_GAME_H