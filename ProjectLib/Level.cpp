/**
 * @file Level.cpp
 * @author Shlok
 */

#include "pch.h"
#include <wx/string.h>
#include "Level.h"

#include "Background.h"
#include "Game.h"
#include "GoalPost.h"
#include "Platform.h"
#include "Wall.h"
#include "GoldCoin.h"
#include "SilverCoin.h"
#include "PowerUp.h"
#include "NDEnemy.h"
#include "UMichEnemy.h"
#include "Football.h"
#include "InvulnerabilityPowerup.h"
#include "SpartyPowerup.h"

using namespace std;

/**
 * Level Constructor
 * @param game the game the level is apart of
 */
Level::Level(Game* game) : mGame(game)
{

}

/**
 * Draw the level area
 * @param graphics The graphics context to draw on
 */
void Level::OnDraw(wxGraphicsContext* graphics)
{
    // Draw the background
    if (mBackground != nullptr)
    {
        int bgWidth = mBackground->GetWidth();
        int bgHeight = mBackground->GetHeight();

        // Tile the background to cover the level width
        int numTiles = (int)(mWidth / bgWidth) + 2;
        for (int i = 0; i < numTiles; i++)
        {
            graphics->DrawBitmap(*mBackground, i * bgWidth, 0, bgWidth, bgHeight);
        }
    }

    //
    // Draw in virtual pixels on the graphics context
    //
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}

/**
 * Update all items in the level
 * @param elapsed Time elapsed since last update in seconds
 */
void Level::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }

    // Remove coins that have finished flying away
    auto it = mItems.begin();
    while (it != mItems.end())
    {
        if (auto coin = std::dynamic_pointer_cast<Coin>(*it))
        {
            // Remove coin if collected and done flying
            if (coin->CoinIsCollected() && coin->GetY() < -100)
            {
                it = mItems.erase(it);
                continue;
            }
        }
        ++it;
    }
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the level.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Level::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}


/**
 * Load the level from a XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the game level from.
 */
void Level::Load(const wxString &filename)
{
    mCurrentLevelFile = std::wstring(filename.wc_str());

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load level file");
        return;
    }

    //mCurrentLevelFile = filename.ToStdWstring();

    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    // Use to set playing area?
    root->GetAttribute(L"width", L"0").ToDouble(&mWidth);
    root->GetAttribute(L"height", L"0").ToDouble(&mHeight);

    // Use to place football originally?
    root->GetAttribute(L"start-x", L"0").ToDouble(&mInitialX);
    root->GetAttribute(L"start-y", L"0").ToDouble(&mInitialY);

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"declarations")
        {
            XmlDeclarations(child);
        }
        if(name == L"items")
        {
            XmlItems(child);
        }
    }


    // Create the football at the starting  position
    shared_ptr<Football> currFootball = mGame->GetFootball();
    if(!currFootball)
    {
        // Create new football, due to lack of init thus far
        shared_ptr<Football> football = make_shared<Football>(this);
        football->SetLocation(mInitialX, mInitialY);
        football->SetSpawnTime(0);

        // Set football in game and pushback into items list
        mGame->SetFootball(football);
        mItems.push_back(football);
    }
    else
    {
        currFootball->SetLocation(mInitialX, mInitialY);
        currFootball->SetSpawnTime(0);

        // Make sure football isn't moving left or right when re-spawning
        currFootball->SetVelocity(0,0);
        currFootball->SetGoingLeft(false);
        currFootball->SetGoingRight(false);


        std::wstring current = this->GetCurrentLevelFile();
        std::wstring next = mGame->GetNextLevelPath(current);

        // Set special level
        std::wstring levelMessage = L"";

        if (filename == L"levels/level1.xml")
        {
            levelMessage = L"Level 1 Start!";
        }
        else if (current == L"levels/level2.xml")
        {
            // Wind Velocity
            this->SetWindVelocity(-25);
        }
        else if (current == L"levels/level3.xml")
        {
            // Wind Velocity
            this->SetWindVelocity(-10);

            // Special Gravitational Acceleration
            currFootball->SetSpecialGravity(850);
        }

        mGame->SetLevelStartMessage(levelMessage);

        mItems.push_back(currFootball);

        mGame->SetPlayerScore(0);

    }

}

/**
 * Handle the items.
 * @param node XML node that is starting
 */
void Level::XmlItems(wxXmlNode *node)
{
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto type = child->GetName();
        auto id = child->GetAttribute(L"id");

        double x = 0;
        double y = 0;
        double cWidth = 0;
        double cHeight = 0;
        child->GetAttribute(L"x").ToDouble(&x);
        child->GetAttribute(L"y").ToDouble(&y);
        // A pointer for the item we are loading
        shared_ptr<Item> item;

        // Backgrounds
        if (id == L"i001" || id == L"i002")
        {
            item = make_shared<Background>(this, mObjDeclarations[id]);
        }

        // Grass Platform
        else if (id == L"i003")
        {

            // Get left, right, and middle images
            item = make_shared<Platform>(this, mObjDeclarations[id],
                L"Images/grassMid.png", L"Images/grassRight.png");
        }

        // Snow Platform
        else if (id == L"i004")
        {
            // Get left, right, and middle images
            item = make_shared<Platform>(this, mObjDeclarations[id],
                L"Images/snowMid.png", L"Images/snowRight.png");
        }

        // Metal Platform
        else if (id == L"i005")
        {
            // Get left, right, and middle images
            item = make_shared<Platform>(this, mObjDeclarations[id],
                L"Images/metalMid.png", L"Images/metalRight.png");
        }

        // Wall 1 or 2
        else if (id == L"i006" || id == L"i007")
        {
            item = make_shared<Wall>(this, mObjDeclarations[id]);
        }

        // Coin 10 -> silver coin
        else if (id == L"i008")
        {
            item = make_shared<SilverCoin>(this);
        }

        // Coin 100 -> gold coin
        else if (id == L"i009")
        {
            item = make_shared<GoldCoin>(this);
        }

        // Power-Up
        else if (id == L"i010")
        {
            item = make_shared<SpartyPowerup>(this);
        }

        // GoalPost
        else if (id == L"i011")
        {
            item = make_shared<GoalPost>(this, mObjDeclarations[id]);
        }

        // UMich Enemy
        else if (id == L"i012")
        {
            item = make_shared<UMichEnemy>(this);
        }

        // ND Enemy
        else if (id == L"i013")
        {
            item = make_shared<NDEnemy>(this);
        }

        else if (id == L"i014")
        {
            item = make_shared<InvulnerabilityPowerup>(this);
        }

        if (id == L"i003" || id == L"i004" || id == L"i005" || id == L"i006" || id == L"i007")
        {
            child->GetAttribute(L"width").ToDouble(&cWidth);
            child->GetAttribute(L"height").ToDouble(&cHeight);
        }

        // Init location and load
        if (item != nullptr)
        {
            // Get location here
            item->SetLocation(x, y);
            item->XmlLoad(child);
            item->SetCustomHeight(cHeight);
            item->SetCustomWidth(cWidth);
            // Add to
            mItems.push_back(item);
        }
    }
}


/**
 * Handle the declarations of the xml
 * @param node XML node that is starting
 */
void Level::XmlDeclarations(wxXmlNode* node)
{
    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto type = child->GetName();
        auto id = child->GetAttribute(L"id");

        // Get type with specific image attribute first
        if (type == L"platform")
        {
            mObjDeclarations[id] = (L"Images/" + child->GetAttribute(L"left-image")).ToStdWstring();
        }
        else
        {
            mObjDeclarations[id] = (L"Images/" + child->GetAttribute(L"image")).ToStdWstring();
        }
    }
}


/**
 * Clear the level data.
 *
 * Deletes all known items in the game level.
 */
void Level::Clear()
{
    mObjDeclarations.clear();
    mItems.clear();
}

void Level::RemoveItem(std::shared_ptr<Item> item)
{
    auto it = std::find(mItems.begin(), mItems.end(), item);
    if (it != mItems.end())
    {
        mItems.erase(it);
    }
}

/**
 * Test for collision between one item and others in this level
 * @param item The item we are testing (usually the football)
 * @return The item it collides with, or nullptr if none
 */
std::shared_ptr<Item> Level::CollisionTest(Item* item)
{

    double leftA = item->GetX() - item->GetWidth() / 2;
    double rightA = item->GetX() + item->GetWidth() / 2;
    double topA = item->GetY() - item->GetHeight() / 2;
    double bottomA = item->GetY() + item->GetHeight() / 2;


    for (auto other : mItems)
    {
        if (other.get() == item)
        {
            continue; // no collision with self
        }

        // Skip non-solid items only for physics checks,
        // but still detect coins and powerups for collection.
        if (!other->IsSolid())
        {
            // Allow collision detection for collectible types
            if (dynamic_cast<Coin*>(other.get()) == nullptr &&
                dynamic_cast<PowerUp*>(other.get()) == nullptr)
            {
                continue;
            }
        }

        // Level checks if football overlaps another item
        // test within bounds of the box:

        double leftB = other->GetX() - other->GetWidth() / 2;
        double rightB = other->GetX() + other->GetWidth() / 2;
        double topB = other->GetY() - other->GetHeight() / 2;
        double bottomB = other->GetY() + other->GetHeight() / 2;

        bool overlapX = rightA >= leftB && leftA <= rightB;
        bool overlapY = bottomA >= topB && topA <= bottomB;

        if (overlapX && overlapY)
        {
            return other;
        }
    }

    // No collision happened
    return nullptr;
}