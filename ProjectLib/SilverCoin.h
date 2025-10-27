/**
* @file SilverCoin.h
 * @author Sanika Kapre
 *
 * Class that describes silver coins
 */

#ifndef SILVERCOIN_H
#define SILVERCOIN_H
#include "Coin.h"


/**
 * Class that describes the coin for silver coin
 */
class SilverCoin: public Coin
{
private:

public:
    /// Default constructor disabled
    SilverCoin() = delete;

    SilverCoin(Level* level);


};



#endif //SILVERCOIN_H
