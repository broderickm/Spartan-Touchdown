/**
 * @file Enemy.h
 * @author Maggie Broderick
 *
 * Class that describes enemies
 */

#ifndef PROJECT1_ENEMY_H
#define PROJECT1_ENEMY_H
#include "MovingItem.h"

/**
 * Class that describes enemy
 */
class Enemy : public MovingItem
{
private:
    /// baseX is where the enemies first initial position is
    double mBaseX = 0;
    /// baseY same but for the Y coordinate
    double mBaseY = 0;

    /// bool used to determine if the enemy has started moving.
    bool hasMoved = false;

    /// freeze the enemy
    bool isFrozen = false;


public:
    /**
     * Handle collision with the football.
     * @param football Pointer to the football that collided with this enemy.
     */
    void OnCollide(Football* football) override;

    // Default constructor disabled
    Enemy() = delete;

    // Default copy constructor disabled
    Enemy(const Enemy &) = delete;

    // = copy operator disabled
    void operator=(const Enemy &) = delete;

    // note: this might be a protected member, for now I am making it public
    Enemy(Level *level, const std::wstring& filename);


    /// sets the base position and the speed.
    void StartMoving();



    /// overridden update function to facilitate movement.
    void Update(double elapsed) override;
};


#endif //PROJECT1_ENEMY_H