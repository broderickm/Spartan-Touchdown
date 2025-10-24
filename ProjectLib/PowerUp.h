/**
* @file PowerUp.h
 * @author Sanika Kapre
 *
 * Class that describes power up
 */

#ifndef POWERUP_H
#define POWERUP_H
#include "Item.h"
#include <wx/graphics.h>

/**
 * Class that describes the power ups
 */
class PowerUp : public Item
{
private:
    /// Keeps track if the powerup has already been collected
    bool mPowerUpCollected = false;

    /// The image used for this powerup
    wxBitmap mPowerUpImage;

    /// The display size of the powerup in virtual pixels
    static const int POWERUP_SIZE = 48;

protected:
    /**
     * Called when this power-up is collected by the football.
     * Derived classes should override this to implement specific effects.
     * @param football The football that collected this power-up
     */
    virtual void ApplyEffect(Football* football) = 0;

public:
    // Disable default constructor
    PowerUp() = delete;

    // Disable default copy assignment
    PowerUp(PowerUp const & powerup) = delete;
    void operator=(PowerUp const & powerup) = delete;

    PowerUp(Level* level, const std::wstring& image);

    void OnCollide(Football* football) override;
    void Draw(wxGraphicsContext* graphics) override;

    bool IsSolid() const override { return false; }

    /**
     * Check if this power-up has been collected
     * @return true if collected, false otherwise
     */
    bool IsCollected() const { return mPowerUpCollected; }

    /**
     * Mark this power-up as collected or uncollected
     * @param collected true if collected, false otherwise
     */
    void SetIsCollected(bool collected) { mPowerUpCollected = collected; }
};



#endif //POWERUP_H
