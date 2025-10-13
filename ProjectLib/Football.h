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
    /// Tells if the football is still alive
    bool mIsDead = false;

    /// Tells if the football is on ground
    bool mIsOnSurface = true;

    /// Tells if the football is moving right
    bool mIsGoingRight = false;

    /// Tells if the football is moving right
    bool mIsGoingLeft = false;

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

public:
    /**
     *Venkata here, i've added the constructors and disabled the default copy constructor, constructor
     *and assingment operator, i've done this so i can load the image in for the football.
     *
     *Feel free to make any changes.
     */


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
    void VerticalHitTest(std::shared_ptr<Item> collided, Vector& newV, Vector& newP);
    void HorizontalHitTest(std::shared_ptr<Item> collided, Vector& newV, Vector& newP);
};


#endif //PROJECT1_FOOTBALL_H