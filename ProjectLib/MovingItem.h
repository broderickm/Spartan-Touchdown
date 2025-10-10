/**
 * @file MovingItem.h
 * @author Shlok
 *
 * Class that describes a moving item
 */

#ifndef PROJECT1_MOVINGITEM_H
#define PROJECT1_MOVINGITEM_H
#include "Item.h"

/**
 * Class that describes a moving item
 */
class MovingItem : public Item
{
private:
    /// Speed in the x-direction
    double mSpeedX=0;

    /// Speed in the y-direction
    double mSpeedY=0;

public:
};


#endif //PROJECT1_MOVINGITEM_H