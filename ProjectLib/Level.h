/**
 * @file Level.h
 * @author Shlok
 *
 * Class that describes level
 */

#ifndef PROJECT1_LEVEL_H
#define PROJECT1_LEVEL_H
#include <map>
#include "Item.h"

class Item;

/**
 * Class that describes a level
 */
class Level
{
private:
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
    std::map<wxString, wxString> mObjDeclarations;

    /// All of the items present in the level
    std::vector<std::shared_ptr<Item>> mItems;

public:
    Level();
    void OnDraw(wxDC *dc, std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Load(const wxString& filename);
    void XmlDeclarations(wxXmlNode* node);
    void XmlItems(wxXmlNode* node);
    void Clear();

    std::shared_ptr<Item> HitTest(int x, int y);
};


#endif //PROJECT1_LEVEL_H