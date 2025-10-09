/**
 * @file GameView.h
 * @author Venkata Pandiri
 *class that describes gameview
 *
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H

#include <wx/timer.h>
#include "wx/frame.h"
#include <wx/window.h>
#include "Game.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;

class GameView : public wxWindow
{
private:
    /// paint and timer functions to update the frame whenever things change
    void OnPaint(wxPaintEvent& event);
    void OnTimer(wxTimerEvent& event);



    /// object for the game/frame itself
    Game mGame;
    /// The timer that allows for animation
    wxTimer mTimer;
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;
    /// The last stopwatch time
    long mTime = 0;
public:
    void Initialize(wxFrame* parent);
};


#endif //PROJECT1_GAMEVIEW_H