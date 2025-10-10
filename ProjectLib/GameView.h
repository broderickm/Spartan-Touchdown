/**
 * @file GameView.h
 * @author Venkata Pandiri
 *
 * Class that describes the game view
 */

#ifndef PROJECT1_GAMEVIEW_H
#define PROJECT1_GAMEVIEW_H

#include <wx/timer.h>
#include "wx/frame.h"
#include <wx/window.h>
#include "Game.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Class that describes the game view
 */
class GameView : public wxWindow
{
private:
    /// Paint and timer functions to update the frame whenever things change
    void OnPaint(wxPaintEvent& event);
    void OnTimer(wxTimerEvent& event);

    /// Key press event handlers
    void OnKeyDown(wxKeyEvent& event);

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

    /**
     * Getter for the game
     * @return pointer to the game object
     */
    Game* GetGame() { return &mGame; }
};


#endif //PROJECT1_GAMEVIEW_H