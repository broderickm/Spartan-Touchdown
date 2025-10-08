/**
 *@file main.cpp
 *@author Shlok
 *
 *main file for the project
*/

#include "pch.h"
#include <MainFrame.h>


/**
 * ok so
 * I know someone else was going to do the app, but
 * I needed the app to function in order to be able to add the testing module
 * since the main function ideally just initializes the app from the app class
 * so I took basically what the aquariumapp did and added it as a nested class in main
 * whoever needs to implement app can take the app functions and move them to their own class
 * the only necessary part of this that will need to be kept is the wximplement call in the last line
 */
class GameApp : public wxApp
{
    public:
    bool OnInit() override;
};

bool GameApp::OnInit()
{
#ifdef WIN32
    // Enable memory leak detection in debug mode
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    // Call base class initialization
    if (!wxApp::OnInit())
        return false;

    // Initialize image handlers for loading images
    wxInitAllImageHandlers();

    // Create and show the main frame
    auto frame = new MainFrame();

    // Initialize function will be implemented within the app later
    //frame->Initialize();

    return true;
}

wxIMPLEMENT_APP(GameApp);