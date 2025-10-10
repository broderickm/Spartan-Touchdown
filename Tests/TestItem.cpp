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

/** Mock class for testing the Item class */
class ItemMock : public Item {
public:
    ItemMock(Game* game) : Item(game, kTestImage) {}
};

TEST(ItemTest, Construct) {
    Game game;
    ItemMock item(&game);
}

TEST(ItemTest, GettersSetters) {
    Game game;
    ItemMock item(&game);

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
    ItemMock item(&game);

    item.SetLocation(150,250);
    /// hit the item exactly at its cordinates should return TRUE
    ASSERT_TRUE(item.HitTest(150,250));
    /// will add more to this once items functionality is expanded upon, as we need make sure hit test returns
    /// false when a transparent pixel is hit.
    ///

}