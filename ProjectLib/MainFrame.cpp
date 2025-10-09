/**
 * @file MainFrame.cpp
 * @author Shlok
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"

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

    // Initialize Menu Here
}





/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}