/**
 * @file Background.h
 * @author Maggie Broderick
 *
 * Class that describes a Background
 */

#ifndef PROJECT1_BACKGROUND_H
#define PROJECT1_BACKGROUND_H
#include "Item.h"

/**
 * Describes a background item
 */
class Background : public Item
{
private:

public:
    /// Constructor
    Background(Level* level, const std::wstring& filename);
    bool HitTest(int x, int y);
};


#endif //PROJECT1_BACKGROUND_H