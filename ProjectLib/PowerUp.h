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

/// The display size of the powerup in virtual pixels
static const int POWERUP_SIZE = 48;

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


    /// X-coordinate for displaying the "Power Up!" message
    double mPowerDisplayX = 0.0;

    /// Y-coordinate for displaying the "Power Up!" message
    double mPowerDisplayY = 0.0;

    /// The distance that the power-up display message travels
    double mPowerDisplayDist = 0.0;

    /// The current display font size of the "Power Up!" message
    double mPowerDisplaySize = 1.0;

    /// The current width of the shrinking image
    double mNewImageWidth = 0.0;

    /// The current height of the shrinking image
    double mNewImageHeight = 0.0;

    /// Whether the collection animation sequence is finished
    bool mFinishSequence = false;

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

    /**
     * @brief Constructs a PowerUp object.
     * @param level The level that contains this power-up.
     * @param image The image used to represent this power-up.
     */
    PowerUp(Level* level, const std::wstring& image);

    /**
     * Handle collision between the football and the goal post.
     * @param football Pointer to the football object that collided with this goal post.
     */
    void OnCollide(Football* football) override;

    /**
     * Update the powerup each frame.
     * Applies wind force if the level has wind.
     * @param elapsed Time elapsed since last update in seconds
     */
    void Update(double elapsed) override;

    /**
     * Draw the power-up at its current position on the screen.
     * @param graphics The graphics context used to draw
     */
    void Draw(wxGraphicsContext* graphics) override;

    /**
     * Determine if the power-up is a solid object.
     * @return False since power-ups can be collected and do not block movement.
     */
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
