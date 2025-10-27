/**
 * @file DoubleJumpPowerup.h
 * @author Venkata Pandiri
 *
 *
 */

#ifndef PROJECT1_DOUBLEJUMPPOWERUP_H
#define PROJECT1_DOUBLEJUMPPOWERUP_H
#include "PowerUp.h"



class DoubleJumpPowerup: public PowerUp
{
private:

public:
    void ApplyEffect(Football* football) override;

    DoubleJumpPowerup(Level * level);

   // disable defualt constructor
    DoubleJumpPowerup() = delete;
    // disable copy constructor
    DoubleJumpPowerup(DoubleJumpPowerup & powerup) = delete;
};


#endif //PROJECT1_DOUBLEJUMPPOWERUP_H