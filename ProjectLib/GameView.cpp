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

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    /**
     * this is where the event handlers that initialize the game go, I am not sure
     * about specifically what needs to be added first here and will likely not be able to
     * add anything concrete until we have a mechanism for loading in the xml files
     */


    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    /// commented out the game functions, make sure to add back when the game is ready
    //mGame.Update(elapsed);
    //mGame.OnDraw(&dc);
}

/** timer event function (basically just updates the frame every tick)
 * @param event is just the timer event (ticking)
 */
void GameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}

