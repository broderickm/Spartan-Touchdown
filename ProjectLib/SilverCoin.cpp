/**
* @file SilverCoin.cpp
 * @author Sanika Kapre
 *
 * Class that describes silver coins
 */

using namespace std;

#include "pch.h"
#include "SilverCoin.h"

SilverCoin::SilverCoin(Game* game)
        : Coin(game, L"images/coin10.png", 10)
{
}