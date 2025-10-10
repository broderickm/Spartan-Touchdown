/**
 * @file Level.h
 * @author Shlok
 *
 * Class that describes level
 */

#ifndef PROJECT1_LEVEL_H
#define PROJECT1_LEVEL_H
#include "Item.h"

/**
 * Class that describes a level
 */
class Level
{
private:
    /// Background image to use for the level
    std::unique_ptr<wxBitmap> mBackground;

    /// All of the items present in the level
    std::vector<std::shared_ptr<Item>> mItems;

public:
};


#endif //PROJECT1_LEVEL_H