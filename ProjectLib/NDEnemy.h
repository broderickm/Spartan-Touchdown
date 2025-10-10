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
    /// disable default constructor
    NDEnemy() = delete;
    /// disable default copy constructor
    NDEnemy(NDEnemy const & ndEnemy) = delete;

    /// disable = copy operator
    void operator=(NDEnemy const & ndEnemy) = delete;

    NDEnemy(Game * game);
};


#endif //PROJECT1_NDENEMY_H