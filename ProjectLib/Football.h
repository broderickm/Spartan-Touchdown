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
    /// Football holding the score
    int mScore = 0;

    /// Tells if the football is still alive
    bool mIsDead = false;

    /// Tells if the football is on ground
    bool mIsOnSurface = true;

    /// Tells if the football is moving right
    bool mIsGoingRight = false;

    /// Tells if the football is moving right
    bool mIsGoingLeft = false;

    /// Tells if the football is currently stepping.
    bool mIsStepping = false;

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

    /// Gravity member variable
    double mGravity = 0;

    /// Flag saying if football has invincibility
    bool mIsInvulnerable = false;

    /// Invincibility time remaining
    double mInvulnerabilityTimeRemaining = 0.0;

    /// Time double jump power-up has been applied for
    double mDoubleJumpTimer = 0.0;

    /// Flag marking if the football has jumped once
    bool mInitJump = false;

    /// Marker to denote if Double Jump power-up has been collected
    bool mDoubleJump = false;

    /// Flag marking if the football has jumped twice
    bool mHasDoubleJumped = false;

public:
    void ActivateDoubleJump(bool enable, double duration);
    void SetDead(bool dead);
    void AddToScore(int value);

    /**
     * Checks if the football is dead.
     * @return True if dead, false otherwise.
     */
    bool IsDead() const
    {
        return mIsDead;
    }

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

    void VerticalHitTest(std::shared_ptr<Item> collided, Vector& newV, Vector& newP);

    void HorizontalHitTest(std::shared_ptr<Item> collided, Vector& newV, Vector& newP);

    /**
      * Set the velocity of the football.
      * @param x The horizontal velocity component.
      * @param y The vertical velocity component.
      */
    void SetVelocity(double x, double y) { mV = Vector(x, y); }

    void Jump();

    void Step();

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

    /**
     * Set the gravitational acceleration
     * @param gravity the given gravity
     */
    void SetSpecialGravity(double gravity) { mGravity = gravity; }

    void ActivateInvulnerability(double duration);

    /**
    * Check if football is invincible or not
    * @return a bool saying if football has invincibility
    */
    bool IsInvulnerable() const { return mIsInvulnerable; }

    /**
    * Activate double jump
    * @param value saying whether double jump is applied or not
    */
    void ActivateDoubleJump(bool value){mDoubleJump = value;}

    /**
    * Get the spawn time
     * @return the spawn time
     */
    double GetSpawnTime() const { return mSpawnTime; }
};


#endif //PROJECT1_FOOTBALL_H