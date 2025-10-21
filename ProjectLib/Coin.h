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
    /// Keeps track if the coin has already been collected
    bool mCoinCollected = false;

    /// The image used for this coin
    wxBitmap mCoinImage;

    /// The value of this coin in points
    int mCoinValue = 0;

    /// The display size of the coin in virtual pixels
    static const int COIN_SIZE = 48;


public:
    void OnCollide(Football* football) override;

    void Update(double elapsed) override;

    /**
     * Constructor for a coin
    */
    Coin(Level *level, const std::wstring& image, int value);

    void Draw(wxGraphicsContext* graphics) override;

    /**
     * Get the coin's point value.
     * @return The current value of this coin
     */
    int GetTheValue() const { return mCoinValue; }

    /**
     * Check if this coin has been collected
     * @return true if the coin is already collected, false otherwise
     */
    bool CoinIsCollected() const { return mCoinCollected; }

    /**
     * Mark this coin as collected or uncollected
     * @param collected true if collected, false otherwise
     */
    void SetIsCollected(bool collected) { mCoinCollected = collected; }

    bool IsSolid() const override { return false; }

};




#endif //COIN_H
