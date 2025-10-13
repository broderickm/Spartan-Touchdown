/**
 * @file Level.cpp
 * @author Shlok
 */

#include "pch.h"
#include "Level.h"
#include "Game.h"
#include "Football.h"

using namespace std;

/**
 * Level Constructor
 */
Level::Level(Game* game) : mGame(game)
{
    // Default of level 1 loaded
    mBackground = make_unique<wxBitmap>(
            L"images/background1.png", wxBITMAP_TYPE_ANY);
}

/**
 * Draw the level area
 * @param dc The device context to draw on
 */
void Level::OnDraw(wxGraphicsContext* graphics)
{
    // Draw the background
    if (mBackground != nullptr && mBackground->IsOk())
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
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load level file");
        return;
    }

    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    root->GetAttribute(L"width", L"0").ToDouble(&mWidth);
    root->GetAttribute(L"height", L"0").ToDouble(&mHeight);

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

    // Create the football at the starting position
    auto football = make_shared<Football>(this);
    football->SetLocation(mInitialX, mInitialY);
    mItems.push_back(football);

    // Tell the game about the football so it can track it for the camera
    mGame->SetFootball(football);
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

        // A pointer for the item we are loading
        shared_ptr<Item> item;

        // We have an item. What id?
        auto id = node->GetAttribute(L"id");

        // Background
        if (id == L"i001")
        {
            //item = make_shared<Item>(this, mObjDeclarations["i001"]);
        }

        // Snow Platform
        if (id == L"i004")
        {
            // Get left, right, and middle images
            //item = make_shared<powerup>(this);
        }

        if (item != nullptr)
        {
            // Get location here
            //item->SetLocation(, );
            mItems.push_back(item);

            item->XmlLoad(node);
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

        // Get special types first
        if (type == L"platform")
        {
            mObjDeclarations[id] = child->GetAttribute(L"image");
        }
        else if (type == L"coin")
        {
            mObjDeclarations[id] = child->GetAttribute(L"image");
        }
        else
        {
            mObjDeclarations[id] = child->GetAttribute(L"image");
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