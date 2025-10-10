/**
* @file PowerUp.cpp
 * @author Sanika Kapre
 *
 * Class that describes power up
 */

using namespace std;

#include "pch.h"
#include "PowerUp.h"

const wstring PowerUpImageName = L"Images/sparty.png";


PowerUp::PowerUp(Game* game): Item(game, PowerUpImageName)
{

}
