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



/**
 * Constructor
 * @param game the game we are adding this football to
 */
Football::Football(Level *level): MovingItem(level, FootballLeftImageName)
{

}
