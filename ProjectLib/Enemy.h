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


public:
    /// default constructor disabled
    Enemy() = delete;
    /// default copy constructor disabled
    Enemy(const Enemy &) = delete;
    /// = copy operator disabled
    void operator=(const Enemy &) = delete;

    /// note: this might be a protected member, for now I am making it public
    Enemy(Game * game, const std::wstring& filename);
};


#endif //PROJECT1_ENEMY_H