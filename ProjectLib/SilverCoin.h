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
    /// Value from a silver coin
    ///int mValue = 10;

public:
    explicit SilverCoin(Game* game);


};



#endif //SILVERCOIN_H
