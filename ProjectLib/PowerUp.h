/**
* @file PowerUp.h
 * @author Sanika Kapre
 *
 * Class that describes power up
 */

#ifndef POWERUP_H
#define POWERUP_H
#include "Item.h"

/**
 * Class that describes the power ups
 */
class PowerUp : public Item
{
private:

public:
    // Disable default constructor
    PowerUp() = delete;

    // Disable default copy assignment
    PowerUp(PowerUp const & powerup) = delete;

    void operator=(PowerUp const & powerup) = delete;

    PowerUp(Level* level);

    bool IsSolid() const override { return false; }

};



#endif //POWERUP_H
