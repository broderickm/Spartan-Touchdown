/**
 * @file TeamPowerUp.cpp
 * @author Annika Valaboju
 */

#include "pch.h"
#include "TeamPowerUp.h"
#include "Game.h"
#include "Football.h"
#include "Level.h"

using namespace std;

/// Image for the moving team power-up
const wstring TeamPowerUpImageName = L"Images/lightning_powerup.png";

/// Horizontal movement bounds and speed
const double BounceSpeed = 150.0;
const double VerticalRange = 100.0;

/**
 * Constructor
 * @param level The level this power-up belongs to
 */
TeamPowerUp::TeamPowerUp(Level* level)
        : MovingItem(level, TeamPowerUpImageName)
{
    // some default speed change later
    setSpeed(BounceSpeed, 0);
}


