/**
 * @file TestItem.cpp
 * @author Annika Valaboju
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Item.h>
#include <Game.h>

using namespace std;

// using random background image for testing
static const std::wstring kTestImage = L"Images/background0.png";
static const std::wstring TestFootBallImage = L"Images/footballLeft.png";

/** Mock class for testing the Item class */
class ItemMock : public Item {
public:
    ItemMock(Level* level) : Item(level, kTestImage) {}
};

class ItemMockWithNewImage: public Item
{
public:
    ItemMockWithNewImage(Level* level) : Item(level, TestFootBallImage) {};
};

TEST(ItemTest, Construct) {
    Game game;
    Level level(&game);
    ItemMock item(&level);
}

TEST(ItemTest, GettersSetters) {
    Game game;
    Level level(&game);
    ItemMock item(&level);

    // Test initial values
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(11.5, 18.2);
    ASSERT_NEAR(11.5, item.GetX(), 0.0001);
    ASSERT_NEAR(18.2, item.GetY(), 0.0001);

    // Test a second with with different values
    item.SetLocation(-52, -106);
    ASSERT_NEAR(-52, item.GetX(), 0.0001);
    ASSERT_NEAR(-106, item.GetY(), 0.0001);
}


TEST(ItemTest, HitTest)
{
    Game game;
    Level level(&game);
    ItemMock football(&level);
    
    /// dimensions of the football are: 64 x 96 wid = 64 hit = 96,  32 = wid/2, and 48 = hit/2
    football.SetLocation(150,250);
    /// hit the item exactly at its cordinates should return TRUE
    ASSERT_TRUE(football.HitTest(150,250));
    ///
    /// hit football to the left
    ASSERT_TRUE(football.HitTest(150-25,250));
    /// hit football to the right
    ASSERT_TRUE(football.HitTest(150+25,250));
    /// hit football above
    ASSERT_TRUE(football.HitTest(150,250+5));
    /// hit football below
    ASSERT_TRUE(football.HitTest(150,250-5));

    /// make sure returning false when clicking out of the image
    ASSERT_FALSE(football.HitTest(150+50,250));
    ASSERT_FALSE(football.HitTest(150-50,250));
    ASSERT_FALSE(football.HitTest(150+70,250+70));

    /// make sure to the return false when hitting a transparent pixel(lower left region is a transparent pixel
    ASSERT_FALSE(football.HitTest(150-29, 250+46));



}