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

#include <DoubleJumpPowerup.h>
#include <UMichEnemy.h>


using namespace std;

/// UMich filename
const wstring UMichImageName = L"Images/U-M.png";


/**
 * Test fixture for team feature tests
 */
class TeamFeatureTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Any setup code can go here
    }
};

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

/** Mock double jump power-up class for testing*/
class JumpMock : public DoubleJumpPowerup
{
public:
    JumpMock(Level* level) : DoubleJumpPowerup(level) {}

    void Draw(wxDC *dc) {}
};

TEST_F(TeamFeatureTest, Constructor)
{
    Game game;
    Level level(&game);
    InvincibleMock power(&level);
    JumpMock jump(&level);
}

TEST_F(TeamFeatureTest, InvulnerabilityPowerupConstructor)
{
    Game game;
    Level level(&game);

    // Test that we can construct an invulnerability powerup
    auto invincPowerup = make_shared<InvulnerabilityPowerup>(&level);
    ASSERT_NE(invincPowerup, nullptr);
}

TEST_F(TeamFeatureTest, DoubleJumpPowerupConstructor)
{
    Game game;
    Level level(&game);

    // Test that we can construct a double jump powerup
    auto doubleJumpPowerup = make_shared<DoubleJumpPowerup>(&level);
    ASSERT_NE(doubleJumpPowerup, nullptr);
}

TEST_F(TeamFeatureTest, PowerupCollisionDetection)
{
    Game game;
    Level level(&game);

    // Create football
    auto football = make_shared<Football>(&level);
    football->SetLocation(100, 100);
    football->SetSpawnTime(2.0);
    level.GetItems().push_back(football);
    game.SetFootball(football);

    // Create powerup at exact same location
    auto invincPowerup = make_shared<InvulnerabilityPowerup>(&level);
    invincPowerup->SetLocation(100, 100);
    level.GetItems().push_back(invincPowerup);

    // Before collision
    ASSERT_FALSE(invincPowerup->IsCollected());

    // Trigger collision
    invincPowerup->OnCollide(football.get());

    // After collision - powerup should be collected
    ASSERT_TRUE(invincPowerup->IsCollected());
}

TEST_F(TeamFeatureTest, InvulnerabilityProtectsFromEnemy)
{
    Game game;
    Level level(&game);

    // Create football
    auto football = make_shared<Football>(&level);
    football->SetLocation(100, 100);
    football->SetSpawnTime(2.0); // Make sure football is fully spawned
    level.GetItems().push_back(football);
    game.SetFootball(football);

    // Create invulnerability powerup
    auto invincPowerup = make_shared<InvulnerabilityPowerup>(&level);
    invincPowerup->SetLocation(100, 100); // Same location as football
    level.GetItems().push_back(invincPowerup);

    // Before collecting powerup, football should not be invulnerable
    ASSERT_FALSE(football->IsInvulnerable());

    // Simulate collision with powerup
    invincPowerup->OnCollide(football.get());

    // After collecting powerup, football should be invulnerable
    ASSERT_TRUE(football->IsInvulnerable());
    ASSERT_FALSE(football->IsDead());

    // Create enemy
    auto enemy = make_shared<UMichEnemy>(&level);
    enemy->SetLocation(100, 100); // Same location as football
    level.GetItems().push_back(enemy);

    // Simulate collision with enemy while invulnerable
    enemy->OnCollide(football.get());

    // Football should still be alive because it's invulnerable
    ASSERT_FALSE(football->IsDead());
    ASSERT_TRUE(football->IsInvulnerable());
}

TEST_F(TeamFeatureTest, InvulnerabilityExpiresAfterDuration)
{
    Game game;
    Level level(&game);

    // Create football
    auto football = make_shared<Football>(&level);
    football->SetLocation(100, 100);
    football->SetSpawnTime(2.0);
    level.GetItems().push_back(football);
    game.SetFootball(football);

    // Activate invulnerability for 5 seconds
    football->ActivateInvulnerability(5.0);
    ASSERT_TRUE(football->IsInvulnerable());

    // Update for 3 seconds - should still be invulnerable
    football->Update(3.0);
    ASSERT_TRUE(football->IsInvulnerable());

    // Update for another 2.5 seconds (total 5.5) - should expire
    football->Update(2.5);
    ASSERT_FALSE(football->IsInvulnerable());
}

TEST_F(TeamFeatureTest, EnemyKillsFootballWithoutInvulnerability)
{
    Game game;
    Level level(&game);

    // Create football
    auto football = make_shared<Football>(&level);
    football->SetLocation(100, 100);
    football->SetSpawnTime(2.0);
    level.GetItems().push_back(football);
    game.SetFootball(football);

    // Verify football is not invulnerable
    ASSERT_FALSE(football->IsInvulnerable());
    ASSERT_FALSE(football->IsDead());

    // Create enemy
    auto enemy = make_shared<UMichEnemy>(&level);
    enemy->SetLocation(100, 100);
    level.GetItems().push_back(enemy);

    // Simulate collision with enemy
    enemy->OnCollide(football.get());

    // Football should be dead
    ASSERT_TRUE(football->IsDead());
}

TEST_F(TeamFeatureTest, DoubleJumpActivation)
{
    Game game;
    Level level(&game);

    // Create football
    auto football = make_shared<Football>(&level);
    football->SetLocation(100, 100);
    football->SetSpawnTime(2.0);
    level.GetItems().push_back(football);
    game.SetFootball(football);

    // Create double jump powerup
    auto doubleJumpPowerup = make_shared<DoubleJumpPowerup>(&level);
    doubleJumpPowerup->SetLocation(100, 100);
    level.GetItems().push_back(doubleJumpPowerup);

    // Collect the powerup
    doubleJumpPowerup->OnCollide(football.get());

    // Verify powerup was collected
    ASSERT_TRUE(doubleJumpPowerup->IsCollected());
}


