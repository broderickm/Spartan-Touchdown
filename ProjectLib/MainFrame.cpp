/**
 * @file MainFrame.cpp
 * @author Shlok
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

/**
 * Initialize the main frame of view of the app
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"SpartanTouchdown",
           wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL);

    // Create the gameview class object as a child of MainFrame
    auto gameView = new GameView();
    mGameView = gameView;
    gameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(gameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    // Initialize Menu
    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File");
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");

    SetMenuBar(menuBar);

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    levelMenu->Append(IDM_LEVELZERO, L"&Level Zero");
    levelMenu->Append(IDM_LEVELONE, L"&Level One");
    levelMenu->Append(IDM_LEVELTWO, L"&Level Two");
    levelMenu->Append(IDM_LEVELTHREE, L"&Level Three");

    helpMenu->Append(wxID_ABOUT, "&About\tF1");

    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelZero, this, IDM_LEVELZERO);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelOne, this, IDM_LEVELONE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelTwo, this, IDM_LEVELTWO);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLevelThree, this, IDM_LEVELTHREE);


    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);


}

/**
* About menu option handlers -> Dialogue box
 * @param event
*/
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"SpartanTouchdown",
            L"About Spartan Touchdown",
            wxOK,
            this);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    mGameView->Stop();
    Close(true);
}

/**
 * Handler for selecting Level Zero from the menu
 * @param event selection event
 */
void MainFrame::OnLevelZero(wxCommandEvent& event)
{
    auto game = mGameView->GetGame();
    game->GetLevel()->Load(L"levels/level0.xml");
    game->ResetTimer();
}

/**
 * Handler for selecting Level One from the menu
 * @param event selection event
 */
void MainFrame::OnLevelOne(wxCommandEvent& event)
{
    auto game = mGameView->GetGame();
    game->GetLevel()->Load(L"levels/level1.xml");
    game->SetLevelStartMessage(L"levels/level1.xml");
    game->ResetTimer();
}

/**
 * Handler for selecting Level Two from the menu
 * @param event selection event
 */
void MainFrame::OnLevelTwo(wxCommandEvent& event)
{
    auto game = mGameView->GetGame();
    game->GetLevel()->Load(L"levels/level2.xml");
    game->ResetTimer();
}

/**
 * Handler for selecting Level Three from the menu
 * @param event selection event
 */
void MainFrame::OnLevelThree(wxCommandEvent& event)
{
    auto game = mGameView->GetGame();
    game->GetLevel()->Load(L"levels/level3.xml");
    game->ResetTimer();
}
