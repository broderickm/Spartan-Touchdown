/**
 * @file TeamFeatureTest.cpp
 * @author Maggie Broderick
 *
 * File for testing invicibilty
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Game.h>
#include <Level.h>
#include <Football.h>
#include <Item.h>
#include <InvulnerabilityPowerup.h>
#include <Enemy.h>


using namespace std;

/// UMich filename
const wstring UMichImageName = L"Images/U-M.png";


/** Mock football class for testing */
class FootballMock : public Football
{
public:
    FootballMock(Level* level) : Football(level) {}

    void Draw(wxDC *dc) {}
};

/** Mock enemy class for testing */
class EnemyMock : public Enemy
{
public:
    EnemyMock(Level* level) : Enemy(level, UMichImageName) {}

    void Draw(wxDC *dc) {}
};

/** Mock invincibility power-up class for testing*/
class InvincibleMock : public InvulnerabilityPowerup
{
public:
    InvincibleMock(Level* level) : InvulnerabilityPowerup(level) {}

    void Draw(wxDC *dc) {}
};

TEST(TeamFeatureTest, Constructor)
{
    Game game;
    Level level(&game);
    InvincibleMock power(&level);
}

TEST(TeamFeatureTest, Invincibility)
{
    Game game;
    Level level(&game);
    InvincibleMock power(&level);
    EnemyMock enemy(&level);

    // Pre-Invincibility Hit of Enemy -> Death == True

    // Post-Invincibility Hit of Enemy -> Death == False

}
