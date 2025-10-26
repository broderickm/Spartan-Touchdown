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

    /// Timer for how long the coin value text has been displayed
    double mTextDisplayTimer = 0.0;

    /// Timer for the flying animation
    double mFlyingTimer = 0.0;

    /// Flag to track if coin is currently flying away
    bool mIsFlying = false;

    /// Upward velocity for flying animation (pixels per second)
    static constexpr double FLYING_SPEED = -300.0;

    /// How long to display the text (seconds)
    static constexpr double TEXT_DISPLAY_DURATION = 1.0;

    /// Position where coin was collected (for text display)
    double mCollectionX = 0.0;
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

    bool IsSolid() const override { return false; }

};




#endif //COIN_H
