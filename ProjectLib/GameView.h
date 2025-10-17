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
    void OnFileOpen(wxCommandEvent& event);

    /**
     * Handle key down events for player control.
     * @param event The wxWidgets key event.
     */
    void OnKeyDown(wxKeyEvent& event);

    /**
     * Handle key release events.
     * @param event The wxWidgets key event.
     */
    void OnKeyUp(wxKeyEvent& event);

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

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}

    /**
     * Load and display level 0.
     * @param event The menu command event.
     */
    void OnLevelZero(wxCommandEvent& event);

    /**
     * Load and display level 1.
     * @param event The menu command event.
     */
    void OnLevelOne(wxCommandEvent& event);

    /**
     * Load and display level 2.
     * @param event The menu command event.
     */
    void OnLevelTwo(wxCommandEvent& event);

    /**
     * Load and display level 3.
     * @param event The menu command event.
     */
    void OnLevelThree(wxCommandEvent& event);
};


#endif //PROJECT1_GAMEVIEW_H