/**
 * @file TestFootball.cpp
 * @author Annika Valaboju
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Game.h>
#include <Level.h>
#include <Football.h>
#include <Item.h>
using namespace std;

class PlatformMock : public Item
{
public:
    PlatformMock(Level* level, double x, double y, double w, double h)
        : Item(level, L"Images/grassMid.png"), mW(w), mH(h)
    {
        SetLocation(x, y);
    }

    double GetWidth() const override { return mW; }
    double GetHeight() const override { return mH; }

private:
    double mW;
    double mH;
};


class WallMock : public Item
{
public:
    WallMock(Level* level, double x, double y, double w, double h)
        : Item(level, L"Images/wall1.png"), mWidth(w), mHeight(h)
    {
        SetLocation(x, y); // Set the location of the wall
    }

    double GetWidth() const override { return mWidth; }
    double GetHeight() const override { return mHeight; }

private:
    double mWidth;
    double mHeight;
};

TEST(FootballTest, VerticalHitStopsOnPlatform)
{
    Game game;
    Level level(&game);

    auto football = std::make_shared<Football>(&level);
    football->SetVelocity(0, 1000);
    football->SetLocation(100, 80);

    auto platform = std::make_shared<PlatformMock>(&level, 100, 200, 200, 20);
    level.GetItems().push_back(platform);

    // Simulate update -> Spawn time becomes 1
    football->Update(1);

    // Now will actually move, spawn time condition has been reached
    football->Update(0.2);

    // Check that it landed correctly and is above platform
    EXPECT_LE(football->GetY(), platform->GetY() - platform->GetHeight()/2 - football->GetHeight()/2 - 0.01);}

TEST(FootballTest, HorizontalHitStopsAtWall)
{
    Game game;
    Level level(&game);

    auto football = std::make_shared<Football>(&level);
    football->SetLocation(100, 200);

    auto wall = std::make_shared<WallMock>(&level, 160, 200, 20, 200);
    level.GetItems().push_back(wall);

    football->SetVelocity(500, 0); // Move right
    football->Update(0.1);

    ASSERT_LE(football->GetX(), wall->GetX() - wall->GetWidth()/2 - football->GetWidth()/2 + 0.01);
}
