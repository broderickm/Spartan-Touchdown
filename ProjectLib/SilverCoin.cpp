/**
* @file SilverCoin.cpp
 * @author Sanika Kapre
 *
 * Class that describes silver coins
 */

using namespace std;

#include "pch.h"
#include "SilverCoin.h"

/**
 * Silver coin constructor
 * @param game the game the coin is in
 */
SilverCoin::SilverCoin(Game* game)
        : Coin(game, L"images/coin10.png", 10)
{
}