/**
* @file GoldCoin.h
 * @author Sanika Kapre
 *
 * Class that describes gold coins
 */

#include "Coin.h"
#ifndef GOLDCOIN_H
#define GOLDCOIN_H


/**
 * Class that describes the coin for goldcoin
 */
class GoldCoin: public Coin
{
private:
    /// Value from a gold coin
    int mValue = 100;

public:

};


#endif //GOLDCOIN_H
