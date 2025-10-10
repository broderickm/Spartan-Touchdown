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
    /// disable default constructor
    PowerUp() = delete;
    /// disable default copy assingment
    PowerUp(PowerUp const & powerup) = delete;

    void operator=(PowerUp const & powerup) = delete;

    PowerUp(Game* game);

};



#endif //POWERUP_H
