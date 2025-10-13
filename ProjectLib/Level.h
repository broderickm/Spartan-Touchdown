/**
 * @file Level.h
 * @author Shlok
 *
 * Class that describes level
 */

#ifndef PROJECT1_LEVEL_H
#define PROJECT1_LEVEL_H
#include <map>
#include <wx/graphics.h>

#include "Item.h"

class Game;
class Item;

/**
 * Class that describes a level
 */
class Level
{
private:
    /// game that the level belongs to
    Game* mGame;

    /// Background image to use for the level
    std::unique_ptr<wxBitmap> mBackground;

    /// Level width
    double mWidth;

    /// Level height
    double mHeight;

    /// Starting X position
    double mInitialX = 0;

    /// Starting Y position
    double mInitialY = 0;

    /// Map holding ids and image filenames
    std::map<wxString, std::wstring> mObjDeclarations;

    /// All of the items present in the level
    std::vector<std::shared_ptr<Item>> mItems;

public:
    Level(Game* game);

    void OnDraw(wxGraphicsContext* graphics);

    void Update(double elapsed);
    void Load(const wxString& filename);
    void XmlDeclarations(wxXmlNode* node);
    void XmlItems(wxXmlNode* node);
    void Clear();

    std::shared_ptr<Item> HitTest(int x, int y);
    std::shared_ptr<Item> CollisionTest(Item* item);

    /**
     * Get the width of the level
     * @return Level width in pixels
     */
    double GetWidth() const { return mWidth; }

    /**
     * Get the height of the level
     * @return Level height in pixels
     */
    double GetHeight() const { return mHeight; }

    /**
     * Get the starting X position
     * @return Starting X position
     */
    double GetInitialX() const { return mInitialX; }

    /**
     * Get the starting Y position
     * @return Starting Y position
     */
    double GetInitialY() const { return mInitialY; }
};


#endif //PROJECT1_LEVEL_H