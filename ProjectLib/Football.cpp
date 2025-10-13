/**
 * @file Football.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include <string>
#include "Football.h"

using namespace std;

/// Football filename Left
const wstring FootballLeftImageName = L"Images/footballLeft.png";

/// Football filename Right
const wstring FootballRightImageName = L"Images/footballRight.png";

/// Football filename Mid
const wstring FootballMidImageName = L"Images/footballMid.png";

/// Gravity in virtual pixels per second per second
const double Gravity = 1000.0;

/// Horizontal speed in pixels per second
const double HorizontalSpeed = 500.0;

/// Upwards vertical speed for bouncing
const double BounceSpeed = -800;

/// Small value to prevent getting stuck in collision
const double Epsilon = 0.01;


/**
 * Constructor
 * @param game the game we are adding this football to
 */
Football::Football(Level *level): MovingItem(level, FootballMidImageName)
{

}
