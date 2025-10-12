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
 * @param level the level the powerup is in
 */
PowerUp::PowerUp(Level* level): Item(level, PowerUpImageName)
{

}
