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
    /// Background image to use
    std::unique_ptr<wxBitmap> mBackground;

    /// All of the items present in the game
    std::vector<std::shared_ptr<Item>> mItems;

public:
};


#endif //PROJECT1_GAME_H