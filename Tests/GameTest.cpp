/**
 * @file GameTest.cpp
 * @author Maggie Broderick
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>
#include <Game.h>

using namespace std;

/// Filename for football left
static const std::wstring TestFootBallImage = L"Images/footballLeft.png";

/** Mock class for testing */
class ItemMock : public Item {
public:
    ItemMock(Game* game) : Item(game, TestFootBallImage) {}

    void Draw(wxDC *dc) {}
};

/**
 * Class for testing game and level
 */
class GameTest : public ::testing::Test
{
protected:
    /**
      * Create a path to a place to put temporary files
      */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/game";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
      * Read a file into a wstring and return it.
      * @param filename Name of the file to read
      * @return File contents
      */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;
    }

    /**
* Test to ensure a xml level file is empty
*/
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        wcout << xml << endl;

        // Regular expression for testing
        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<game/>")));

    }
};

TEST_F(GameTest, Construct)
{
    Game game;
    Level level;
}


TEST_F(GameTest, Clear)
{
    Game game;
    Level level;

    ItemMock item(&game);

    level.Clear();


    ASSERT_TRUE(level.HitTest(100, 200) == nullptr);

    ASSERT_TRUE(level.HitTest(400, 400) == nullptr);

    ASSERT_TRUE(level.HitTest(600, 200) == nullptr);
}