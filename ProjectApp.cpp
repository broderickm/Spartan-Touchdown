/**
 * @file ProjectApp.cpp
 * @author Maggie Broderick
 */

#include "pch.h"
#include <MainFrame.h>
#include "ProjectApp.h"

using namespace std;

/**
 * Initialize the application
 *
 * @return boolean saying if the program has been initialized
 */
bool ProjectApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    // Will add code below back in once MainFrame has code
    //auto frame = new MainFrame();
    //frame->Initialize();
    //frame->Show(true);

    return true;
}