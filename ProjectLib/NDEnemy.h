/**
 * @file NDEnemy.h
 * @author Maggie Broderick
 *
 * Class that describes a Notre Dame Enemy
 */

#ifndef PROJECT1_NDENEMY_H
#define PROJECT1_NDENEMY_H

#include "Enemy.h"

/**
 * Class that describes the enemy from Notre Dame
 */
class NDEnemy : public Enemy
{
private:


public:
    // Disable default constructor
    NDEnemy() = delete;

    // Disable default copy constructor
    NDEnemy(NDEnemy const & ndEnemy) = delete;

    // Disable = copy operator
    void operator=(NDEnemy const & ndEnemy) = delete;

    NDEnemy(Level* level);
    void StartMoving() override;
};


#endif //PROJECT1_NDENEMY_H