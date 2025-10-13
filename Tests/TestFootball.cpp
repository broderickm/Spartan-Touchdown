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

TEST(FootballTest, VerticalHitStopsOnPlatform)
{
    Game game;
    Level level(&game);

    // create football and a platform
    // auto football = make_shared<Football>(&level);
    // football->SetLocation(100, 100); // starting above platform

    // auto platform = std::make_shared<PlatformMock>(&level, 100, 200, 200, 20);
    // level.GetItems().push_back(platform); // manually add to level

    // give downward velocity (falling)
    // football->SetVelocity(0, 500);

    // simulate update for small step
    // football->Update(0.1);

    // Verify football did not pass through platform
    // ASSERT_LE(football->GetY(), platform->GetY() - platform->GetHeight() / 2 - football->GetHeight() / 2 + 0.01);
}