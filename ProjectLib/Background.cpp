/**
 * @file Background.cpp
 * @author Maggie Broderick
 */

using namespace std;


#include "pch.h"
#include "Background.h"


/**
 * Constructor
 * @param level the level we are adding this enemy to
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