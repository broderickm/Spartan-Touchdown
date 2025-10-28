/**
 * @file DoubleJumpPowerup.cpp
 * @author Venkata Pandiri
 */

#include "pch.h"
#include "DoubleJumpPowerup.h"
#include "Football.h"

using namespace std;

/// Image filename for double jump
const wstring ShoePowerupImage = L"Images/powerupshoe.png";

/**
 * Applies double jump to football
 * @param football
 */
void DoubleJumpPowerup::ApplyEffect(Football* football)
{
    football->ActivateDoubleJump(true);
}

/**
 * Constructor
 * @param level level that power up is in
 */
DoubleJumpPowerup::DoubleJumpPowerup(Level * level): PowerUp(level, ShoePowerupImage)
{

}



