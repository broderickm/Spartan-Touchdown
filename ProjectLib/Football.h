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

    double mDoubleJumpTimer = 0.0;



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

    bool mIsInvulnerable = false;
    double mInvulnerabilityTimeRemaining = 0.0;


    double mDoubleJumpTimeElapsed = 0.0;
    double mSpaceKeyElasped = 0.0;

    bool mInitJump = false;
    bool mDoubleJump = false;

public:

    void ActivateDoubleJump(bool enable, double duration);

    /**
     * @brief Adds a value to the football's score.
     * @param value The number of points to add.
     */
    void AddToScore(int value);


    /**
     * @brief Sets the football's death state.
     * @param dead True if the football is dead, false otherwise.
     */
    void SetDead(bool dead)
    {
        mIsDead = dead;
    }

    /**
     * @brief Checks if the football is dead.
     * @return True if dead, false otherwise.
     */
    bool IsDead() const
    {
        return mIsDead;
    }

    /**
     * @brief Constructor.
     * @param level The level this football belongs to.
     */
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
     * @brief Advances the football’s animation step.
     */
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

    /**
     * @brief Draws the football on the graphics context.
     * @param graphics The wxWidgets graphics context to draw with.
     */
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

    /**
   * activate vulnerability
    */
    void ActivateInvulnerability(double duration);
    /**
       * check ifis vulnerable
        */

    bool IsInvulnerable() const { return mIsInvulnerable; }

    /**
   * activate double jump
    */
    void ActivateDoubleJump(bool value){mDoubleJump = value;}

    /**
    * Get the spawn time
     * @return the spawn time
     */
    double GetSpawnTime() const { return mSpawnTime; }
};


#endif //PROJECT1_FOOTBALL_H