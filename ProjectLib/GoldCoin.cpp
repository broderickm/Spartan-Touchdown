/**
* @file GoldCoin.cpp
 * @author Sanika Kapre
 *
 * Class that describes gold coins
 */

using namespace std;


#include "pch.h"
#include "GoldCoin.h"

GoldCoin::GoldCoin(Game* game)
        : Coin(game, L"images/coin100.png", 100)
{
}
