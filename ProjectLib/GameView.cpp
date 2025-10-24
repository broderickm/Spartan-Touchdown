/**
 * @file GameView.cpp
 * @author Venkata Pandiri
 */
#include "pch.h"
#include "GameView.h"

#include <wx/dc.h>
#include <wx/brush.h>
#include <wx/pen.h>
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>

#include <wx/graphics.h>

#include "ids.h"

/**
 * Initialize the game view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundColour(*wxWHITE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    mGame.Initialize();
    Refresh();
    Update();

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelZero, this, IDM_LEVELZERO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOne, this, IDM_LEVELONE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelTwo, this, IDM_LEVELTWO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelThree, this, IDM_LEVELTHREE);

    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mStopWatch.Start();

    Refresh();
}

/**
 * Handle key down events for player control.
 * @param event The wxWidgets key event.
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    auto keyCode = event.GetKeyCode();
    auto football = mGame.GetFootball();

    /// similarly to above, other items will need to be added in (like the ball)
    /// before this function can be made functional

    switch(keyCode)
    {
    case WXK_LEFT:
        // Move football left
        football->SetGoingLeft(true);
        football->Step();
        break;

    case WXK_RIGHT:
        // Move football right
        football->SetGoingRight(true);
        football->Step();
        break;

    case WXK_SPACE:
        // Make football jump/bounce
        football->Jump();
        break;

    default:
        event.Skip();  // Allow other handlers to process unhandled keys
        break;
    }

    Refresh();
    Update();
}

/**
 * Handle key release events.
 * @param event The wxWidgets key event.
 */
void GameView::OnKeyUp(wxKeyEvent& event)
{
    auto keyCode = event.GetKeyCode();
    auto football = mGame.GetFootball();

    if (football == nullptr)
    {
        event.Skip();
        return;
    }

    switch(keyCode)
    {
    case WXK_LEFT:
        football->SetGoingLeft(false);
        break;

    case WXK_RIGHT:
        football->SetGoingRight(false);
        break;

    default:
        event.Skip();
        break;
    }

    Refresh();
    Update();
}

/**
 * Paint event, draws the window contents.
 * @param event The wxWidgets paint event.
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed since the last call to OnPaint
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // Update the game
    mGame.Update(elapsed);

    // Create a graphics context
    auto size = GetClientSize();
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    mGame.OnDraw(graphics, size.GetWidth(), size.GetHeight());
}

/**
 * Handle timer ticks that trigger periodic updates.
 * @param event The wxWidgets timer event.
 */
void GameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}

/**
 * Handle "File > Open" menu command.
 * @param event The menu command event.
 */
void GameView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, L"Load Level file", L"levels", L"level1.xml",
            L"Level Files (*.xml)|*.xml", wxFD_OPEN);

    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    //mGame.GetLevel()->Load(filename);
    Refresh();
}

/**
 * Load and display level 0.
 * @param event The menu command event.
 */
void GameView::OnLevelZero(wxCommandEvent& event)
{
    Level* level = this->GetGame()->GetLevel();
    level->Load(L"levels/level0.xml");

    level->SetWindVelocity(0);
    Refresh();
    Update();
}

/**
 * Load and display level 1.
 * @param event The menu command event.
 */
void GameView::OnLevelOne(wxCommandEvent& event)
{
    Level* level = this->GetGame()->GetLevel();
    level->Load(L"levels/level1.xml");

    // Confirm initial conditions
    level->SetWindVelocity(0);
    mGame.SetPlayerScore(0);

    Refresh();
    Update();
}

/**
 * Load and display level 2.
 * @param event The menu command event.
 */
void GameView::OnLevelTwo(wxCommandEvent& event)
{
    Level* level = this->GetGame()->GetLevel();
    level->Load(L"levels/level2.xml");

    // Set wind for level 2 only
    level->SetWindVelocity(-25);  // Negative = left drift
    mGame.SetPlayerScore(0);

    Refresh();
    Update();
}

/**
 * Load and display level 3.
 * @param event The menu command event.
 */
void GameView::OnLevelThree(wxCommandEvent& event)
{
    Level* level = this->GetGame()->GetLevel();
    level->Load(L"levels/level3.xml");

    level->SetWindVelocity(-10);
    mGame.SetPlayerScore(0);

    Refresh();
    Update();
}