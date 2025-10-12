/**
* @file GoldCoin.h
 * @author Sanika Kapre
 *
 * Class that describes gold coins
 */

#ifndef GOLDCOIN_H
#define GOLDCOIN_H
#include "Coin.h"


/**
 * Class that describes the coin for goldcoin
 */
class GoldCoin: public Coin
{

private:
    /// Value from a gold coin
   /// int mValue = 100;

public:
    /// Disable default constructor
    GoldCoin() = delete;

    GoldCoin(Level* level);


};


#endif //GOLDCOIN_H
