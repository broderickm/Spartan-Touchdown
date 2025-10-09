/**
 * @file MainFrame.cpp
 * @author Shlok
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"SpartanTouchdown",
           wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the gameview class object as a child of MainFrame
    //auto gameView = new GameView();
    //gameView->Initialize(this);

    // Add it to the sizer
    //sizer->Add(gameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    //SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    // Initialize Menu
    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto aboutMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File");
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");
    menuBar->Append(aboutMenu, L"&About");

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    // Right now is no dialogue for showing this!
    aboutMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    levelMenu->Append(IDM_LEVELZERO, L"&Level Zero");
    levelMenu->Append(IDM_LEVELONE, L"&Level One");
    levelMenu->Append(IDM_LEVELTWO, L"&Level Two");
    levelMenu->Append(IDM_LEVELTHREE, L"&Level Three");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);

}





/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}