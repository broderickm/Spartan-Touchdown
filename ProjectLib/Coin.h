/**
* @file Coin.h
 * @author Sanika Kapre
 *
 * Class that describes coins
 */

#ifndef COIN_H
#define COIN_H
#include "Item.h"
#include <wx/graphics.h>


/**
 * Class that describes coins
 */
class Coin : public Item
{
private:
    /// The image used for this coin
    wxBitmap mCoinImage;

    /// The value of this coin in points
    int mCoinValue = 0;

    /// The display size of the coin in virtual pixels
    static const int COIN_SIZE = 48;


public:
    Coin(Level *level, const std::wstring& image, int value);

    void Draw(wxGraphicsContext* graphics) override;

    /**
     * Get the coin's point value.
     * @return The current value of this coin
     */
    int GetValue() const { return mCoinValue; }

};




#endif //COIN_H
