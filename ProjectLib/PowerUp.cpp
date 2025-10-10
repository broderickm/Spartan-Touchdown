/**
* @file PowerUp.cpp
 * @author Sanika Kapre
 *
 * Class that describes power up
 */

using namespace std;

#include "pch.h"
#include "PowerUp.h"

/// File image for the powerup
const wstring PowerUpImageName = L"Images/sparty.png";

/**
 * Constructor of the PowerUp
 * @param game the game the powerup is in
 */
PowerUp::PowerUp(Game* game): Item(game, PowerUpImageName)
{

}
