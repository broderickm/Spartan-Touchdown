/**
 * @file DoubleJumpPowerup.cpp
 * @author Venkata Pandiri
 */
#include "DoubleJumpPowerup.h"

#include "Football.h"
using namespace std;


const wstring ShoePowerupImage = L"Images/powerupshoe.png";


void DoubleJumpPowerup::ApplyEffect(Football* football)
{
    football->ActivateDoubleJump(true);
}

DoubleJumpPowerup::DoubleJumpPowerup(Level * level): PowerUp(level, ShoePowerupImage)
{

}



