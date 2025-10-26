/**
 * @file GoalPost.h
 * @author Venkata Pandiri
 *
 *class that describes goal post
 */

#ifndef PROJECT1_GOALPOST_H
#define PROJECT1_GOALPOST_H

#include "Item.h"
#include <wx/graphics.h>


/**
 *
 *class that describes goal post
 */

class GoalPost: public Item
{
private:
 /// The image used for the goalpost
 wxBitmap mGoalpostImage;

 /// Default width of the goalpost
 double mGoalpostWidth = 80;

 /// Default height of the goalpost
 double mGoalpostHeight = 160;

public:

 /**
  * Handle collision between the football and the goal post.
  * @param football Pointer to the football object that collided with this goal post.
  */
 void OnCollide(Football* football) override;

 /**
  * Constructor.
  * @param level  The level this goalpost belongs to
  * @param image The filename of the goalpost image
  */
 GoalPost(Level *level, const std::wstring& image);

 /**
  * Draw the goalpost on the screen.
  * @param graphics The graphics context used to draw
  */
 void Draw(wxGraphicsContext* graphics) override;

 /**
  * Set a custom size for the goalpost.
  * @param width  New width
  * @param height New height
  */
 void SetGoalpostSize(double width, double height);

 /**
 * Test for collisions between the goalpost and another item.
 * @param item The other item to test
 * @return True if the goalpost collides with the given item, false otherwise
 */
 bool CollisionTest(Item* item);

};


#endif //PROJECT1_GOALPOST_H