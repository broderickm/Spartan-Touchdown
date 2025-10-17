/**
 * @file Background.cpp
 * @author Maggie Broderick
 */

using namespace std;


#include "pch.h"
#include "Background.h"


/**
 * Construct a background object.
 * @param level The level that this background belongs to.
 * @param filename The file path of the image to use as the background.
 */
Background::Background(Level *level, const std::wstring& filename): Item(level, filename)
{

}

/**
 * Test to see if we hit this object when given a x,y value
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Background::HitTest(int x, int y)
{
    return false;
}