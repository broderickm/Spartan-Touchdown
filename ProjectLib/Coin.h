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

    /// Timer for how long the coin value text has been displayed
    double mTextDisplayTimer = 0.0;

    /// Timer for the flying animation
    double mFlyingTimer = 0.0;

    /// Flag to track if coin is currently flying away
    bool mIsFlying = false;

    /// Position where coin was collected (for text display)
    double mCollectionX = 0.0;

    /// The Y position where the coin was collected
    double mCollectionY = 0.0;

    /// The actual value added to score (after multiplier applied)
    int mDisplayValue = 0;

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

    /**
     * Determine if the coin is a solid object that blocks movement.
     * @return False since coins are collectible and not solid.
     */
    bool IsSolid() const override { return false; }

};




#endif //COIN_H
