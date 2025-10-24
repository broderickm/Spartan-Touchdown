/**
 * @file SpartyPowerup.cpp
 * @author Shlok
 *
 * powerup that doubles score
 */

#include "pch.h"
#include "SpartyPowerup.h"
#include "Game.h"

/**
 *  constructor for the powerup
 *  @param level the level that the powerup belongs to
 */
SpartyPowerup::SpartyPowerup(Level* level): PowerUp(level, L"images/sparty.png")
{
}

/**
 * apply the intended effect when collected
 * @param football the football that collides with the powerup
 */
void SpartyPowerup::ApplyEffect(Football* football)
{
    if (auto game = GetLevel()->GetGame())
    {
        game->AddToPlayerScore(game->GetPlayerScore());
    }
}

