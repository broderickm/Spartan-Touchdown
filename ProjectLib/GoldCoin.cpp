/**
* @file GoldCoin.cpp
 * @author Sanika Kapre
 *
 * Class that describes gold coins
 */

using namespace std;


#include "pch.h"
#include "GoldCoin.h"

GoldCoin::GoldCoin(Level *level)
        : Coin(level, L"images/coin100.png", 100)
{
}
