/**
 * @file BackgroundTest.cpp
 * @author Maggie Broderick
 */

#include <pch.h>
#include <Game.h>
#include <Background.h>
#include "gtest/gtest.h"


// using random background image for testing
static const std::wstring kTestImage = L"Images/background1.png";
static const std::wstring TestFootBallImage = L"Images/footballLeft.png";

/** Mock class for testing the Background class */
class BackgroundMock : public Background {
public:
    BackgroundMock(Level* level) : Background(level, kTestImage) {}
};

/** Mock class for testing the Item class */
class ItemMock : public Item {
public:
    ItemMock(Level* level) : Item(level, TestFootBallImage) {}
};

TEST(BackgroundTest, Construct) {
    Game game;
    Level level(&game);
    ItemMock item(&level);
    BackgroundMock background(&level);
}

TEST(BackgroundTest, HitTest)
{
    Game game;
    Level level(&game);
    ItemMock item(&level);
    BackgroundMock background(&level);

    /// dimensions of the football are: 64 x 96 wid = 64 hit = 96,  32 = wid/2, and 48 = hit/2
    item.SetLocation(150,250);

    /// Hit the item at midpoint
    ASSERT_TRUE(item.HitTest(150,250));

    /// hit football to the left, right, above, and below
    ASSERT_TRUE(item.HitTest(150-25,250));
    ASSERT_TRUE(item.HitTest(150+25,250));
    ASSERT_TRUE(item.HitTest(150,250+5));
    ASSERT_TRUE(item.HitTest(150,250-5));

    /// Background location midpoint set
    background.SetLocation(150,250);

    // Confirm background isn't triggered by a hittest at any point
    ASSERT_FALSE(background.HitTest(150,250));
    ASSERT_FALSE(background.HitTest(150-25,250));
    ASSERT_FALSE(background.HitTest(150+25,250));
    ASSERT_FALSE(background.HitTest(150,250+5));
    ASSERT_FALSE(background.HitTest(150,250-5));

}

