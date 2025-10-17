/**
 * @file MovingItem.h
 * @author Shlok
 *
 * Class that describes a moving item
 */

#ifndef PROJECT1_MOVINGITEM_H
#define PROJECT1_MOVINGITEM_H
#include "Item.h"
class Game;
/**
 * Class that describes a moving item
 */
class MovingItem : public Item
{
private:
    /// Speed in the x-direction
    double mSpeedX=0;

    /// Speed in the y-direction
    double mSpeedY=0;

public:

    /**
     *venkata here,
     *I've added the constructors for this class, so we can load in images
     *if there are changes to be made dont hesistate to change the functions
     */

    // Disable default constructor
    MovingItem() = delete;

    // Disable copy constructor
    MovingItem(MovingItem const & movingItem) = delete;
    void operator=(const MovingItem &) = delete;

    // note: this might be protected member, for now i am making it public.
    MovingItem(Level* level, const std::wstring& filename);

    void XmlLoad(wxXmlNode* node) override;

    /**
     * Get the game this moving item belongs to.
     * @return Pointer to the Game object
     */
    Game* GetGame() const;


    /**
     *Setter for the speeds.
     */
    void setSpeed(double x, double y);


    /**
     * Get the current horizontal speed.
     * @return The horizontal velocity component in pixels per second
     */
    double getSpeedX(){return mSpeedX;}

    /**
     * Get the current vertical speed.
     * @return The vertical velocity component in pixels per second
     */
    double getSpeedY(){return mSpeedY;}

};


#endif //PROJECT1_MOVINGITEM_H