/**
 * @file SpartyPowerup.h
 * @author Shlok
 *
 * Class for a powerup that doubles coin value
 */

#ifndef PROJECT1_SPARTYPOWERUP_H
#define PROJECT1_SPARTYPOWERUP_H
#include "PowerUp.h"

/**
 * Class that describes the sparty coin doubler power-up
 */
class SpartyPowerup : public PowerUp
{
private:
protected:
    void ApplyEffect(Football* football) override;
public:
    /// Disable default constructor
    SpartyPowerup() = delete;

    SpartyPowerup(Level* level);
};


#endif //PROJECT1_SPARTYPOWERUP_H