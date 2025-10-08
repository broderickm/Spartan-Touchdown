/**
* @file SilverCoin.h
 * @author Sanika Kapre
 *
 * Class that describes silver coins
 */

#include "Coin.h"
#ifndef SILVERCOIN_H
#define SILVERCOIN_H


/**
 * Class that describes the coin for silver coin
 */
class SilverCoin: public Coin
{
private:
    /// Value from a silver coin
    int mValue = 10;

public:

};



#endif //SILVERCOIN_H
