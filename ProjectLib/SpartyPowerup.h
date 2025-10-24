/**
 * @file SpartyPowerup.h
 * @author Shlok
 *
 * powerup that doubles score
 */

#ifndef PROJECT1_SPARTYPOWERUP_H
#define PROJECT1_SPARTYPOWERUP_H
#include "PowerUp.h"

class SpartyPowerup : public PowerUp
{
private:
protected:
    void ApplyEffect(Football* football) override;
public:
    /// Disable default constructor
    SpartyPowerup() = delete;

    /**
     * Construct the powerup given the level
     * @param level the level that contains this powerup
     */
    SpartyPowerup(Level* level);
};


#endif //PROJECT1_SPARTYPOWERUP_H