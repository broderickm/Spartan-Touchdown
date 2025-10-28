/**
 * @file TeamPowerUp.h
 * @author Annika Valaboju
 *
 *
 */

#ifndef PROJECT1_TEAMPOWERUP_H
#define PROJECT1_TEAMPOWERUP_H

#include "MovingItem.h"

class Football;

/**
 * A power-up that moves around and grants special abilities
 * (invincibility + double jump) when collected.
 */
class TeamPowerUp : public MovingItem
{
private:
    /// speed in X and Y (inherited from MovingItem)
    double mSpeedX = 0;

    /// Vertical movement speed of the team power-up
    double mSpeedY = 0;

    /// flag to track if it’s active (not yet collected)
    bool mActive = true;

    /// Duration (in seconds) of the power-up’s effect
    double mDuration = 20.0;

    /// Internal timer tracking how long since collected
    double mTimer = 0.0;

protected:
    void ApplyEffect(Football* football) ;

public:

    // Disable default constructor
    TeamPowerUp() = delete;
    TeamPowerUp(const TeamPowerUp&) = delete;
    void operator=(const TeamPowerUp&) = delete;

    void Update(double elapsed) override;
    void OnCollide(Football* football) override;

    bool IsSolid() const override { return false; }

    /// Constructor
    TeamPowerUp(Level* level);

    // not fully implemented functions but a start???
    // /// Update position and handle movement bounds
    // void Update(double elapsed) override;

    // /// Make it non-solid (so football can pass through)
    // bool IsSolid() const override { return false; }
    //
    // /// What happens when the football collects it
    // void OnCollect();
    //
    // /// Whether the powerup is still active
    // bool IsActive() const { return mActive; }
};

#endif //PROJECT1_TEAMPOWERUP_H