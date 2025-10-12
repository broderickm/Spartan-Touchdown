/**
 * @file GoalPost.cpp
 * @author Venkata Pandiri
 * code by sanika
 */

#include"pch.h"
#include "GoalPost.h"
#include "Game.h"

/**
 * Construct a goalpost using the provided image.
 */
GoalPost::GoalPost(Level *level, const std::wstring& image)
        : Item(level, image),
          mGoalpostImage(image, wxBITMAP_TYPE_ANY)
{
}

/**
 * Draw the goalpost image centered at its position.
 */
void GoalPost::Draw(wxGraphicsContext* graphics)
{
    if (graphics == nullptr)
    {
        return; // nothing to draw on
    }

    double drawX = GetX() - mGoalpostWidth / 2.0;
    double drawY = GetY() - mGoalpostHeight / 2.0;

    graphics->DrawBitmap(mGoalpostImage, drawX, drawY,
                         mGoalpostWidth, mGoalpostHeight);
}

/**
 * Set the goalpost’s size.
 */
void GoalPost::SetGoalpostSize(double width, double height)
{
    mGoalpostWidth = width;
    mGoalpostHeight = height;
}