/**
 * @file UMichEnemy.h
 * @author Maggie Broderick
 *
 * Class that describes the UMich Enemy
 */

#ifndef PROJECT1_UMICHENEMY_H
#define PROJECT1_UMICHENEMY_H
#include "Enemy.h"

/**
 * Class that describes the Michigan Wolverine enemy
 */
class UMichEnemy : public Enemy
{
private:

public:
    /// disable default constructor
    UMichEnemy() = delete;
    /// disable default copy constructor
    UMichEnemy(UMichEnemy const & UMichEnemy) = delete;

    /// disable = copy operator
    void operator=(UMichEnemy const & UMichEnemy) = delete;

    UMichEnemy(Game * game);
};


#endif //PROJECT1_UMICHENEMY_H