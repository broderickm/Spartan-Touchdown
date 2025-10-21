/**
 * @file Football.h
 * @author Maggie Broderick
 *
 * A class that describes a football
 */

#ifndef PROJECT1_FOOTBALL_H
#define PROJECT1_FOOTBALL_H
#include <memory>
#include "MovingItem.h"
#include "Vector.h"

/**
 *  Class that describes a football
 */
class Football : public MovingItem
{
private:
    int mScore = 0;


    /// Tells if the football is still alive
    bool mIsDead = false;

    /// Tells if the football is on ground
    bool mIsOnSurface = true;

    /// Tells if the football is moving right
    bool mIsGoingRight = false;

    /// Tells if the football is moving right
    bool mIsGoingLeft = false;

    /// Center image
    std::unique_ptr<wxImage> mCenterImage;

    /// Center bitmap
    std::unique_ptr<wxBitmap> mCenterBitmap;

    /// Left image
    std::unique_ptr<wxImage> mLeftImage;

    /// Left bitmap
    std::unique_ptr<wxBitmap> mLeftBitmap;

    /// Right image
    std::unique_ptr<wxImage> mRightImage;

    /// Right bitmap
    std::unique_ptr<wxBitmap> mRightBitmap;

    /// The velocity vector of the football
    Vector mV = Vector(0, 0);

    /// The time since the football has spawned into the level
    double mSpawnTime = 0;

public:
    void AddToScore(int value);


    ///set dead function
    void SetDead(bool dead)
    {
        mIsDead = dead;
    }

    ///is dead function declaration
    bool IsDead() const
    {
        return mIsDead;
    }

    /// constructor for the football
    Football(Level *level);

    /// disable default constructor
    Football() = delete;

    /// disable copy constructor
    Football(Football const & football) = delete;

    /// disable the assignment operator
    void operator=(Football const & football) = delete;

    /**
     * Update the football each frame
     * @param elapsed Time elapsed since last update
     */
    void Update(double elapsed) override;

    /**
     * Handle a vertical collision between the football and another item.
     * @param collided The item the football collided with.
     * @param newV The current velocity vector to adjust after collision.
     * @param newP The current position vector to adjust after collision.
     */
    void VerticalHitTest(std::shared_ptr<Item> collided, Vector& newV, Vector& newP);

    /**
     * Handle a horizontal collision between the football and another item.
     * @param collided The item the football collided with.
     * @param newV The current velocity vector to adjust after collision.
     * @param newP The current position vector to adjust after collision.
     */
    void HorizontalHitTest(std::shared_ptr<Item> collided, Vector& newV, Vector& newP);

    /**
      * Set the velocity of the football.
      * @param x The horizontal velocity component.
      * @param y The vertical velocity component.
      */
    void SetVelocity(double x, double y) { mV = Vector(x, y); }

    /**
     * Make the football jump (only if on a surface)
     */
    void Jump();

    /**
     * Set whether the football is moving left
     * @param goingLeft True if moving left
     */
    void SetGoingLeft(bool goingLeft) { mIsGoingLeft = goingLeft; }

    /**
     * Set whether the football is moving right
     * @param goingRight True if moving right
     */
    void SetGoingRight(bool goingRight) { mIsGoingRight = goingRight; }

    void Draw(wxGraphicsContext* graphics) override;

    /**
     * Set the spawn time
     * @param time the given time
     */
    void SetSpawnTime(double time) { mSpawnTime = time; }
};


#endif //PROJECT1_FOOTBALL_H