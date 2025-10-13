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

/**
 * Shlok here,
 * there are going to be a lot of headers here, I'll need to import all the objects that show up
 * on screen, so I will add them as needed for the functions to create and then all together
 * at the end
 */

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
    //mGame.GetLevel()->Load(L"levels/level1.xml");

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelZero, this, IDM_LEVELZERO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOne, this, IDM_LEVELONE);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelTwo, this, IDM_LEVELTWO);
    //parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLeveThree, this, IDM_LEVELTHREE);

    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);


    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mStopWatch.Start();
}

/**
 * Handle key down events for player control
 * @param event The key event
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    auto keyCode = event.GetKeyCode();

    /// similarly to above, other items will need to be added in (like the ball)
    /// before this function can be made functional

    switch(keyCode)
    {
    case WXK_LEFT:
        // Move football left
        // mGame.MoveFootballLeft();
        break;

    case WXK_RIGHT:
        // Move football right
        // mGame.MoveFootballRight();
        break;

    case WXK_SPACE:
        // Make football jump/bounce
        // mGame.FootballJump();
        break;

    default:
        event.Skip();  // Allow other handlers to process unhandled keys
        break;
    }
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
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

/** timer event function (basically just updates the frame every tick)
 * @param event is just the timer event (ticking)
 */
void GameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}

/**
 * File>Open menu handler
 * @param event Menu event
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


void GameView::OnLevelZero(wxCommandEvent& event)
{
    Level* level = this->GetGame()->GetLevel();
    level->Load(L"levels/level0.xml");

    Refresh();
    Update();
}

void GameView::OnLevelOne(wxCommandEvent& event)
{
    Level* level = this->GetGame()->GetLevel();
    level->Load(L"levels/level1.xml");

    Refresh();
    Update();
}

void GameView::OnLevelTwo(wxCommandEvent& event)
{
    Level* level = this->GetGame()->GetLevel();
    level->Load(L"levels/level2.xml");

    Refresh();
    Update();
}