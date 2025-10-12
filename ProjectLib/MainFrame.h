/**
 * @file MainFrame.h
 * @author Shlok
 *
 * class for the frame that the game is played within
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H
#include <wx/osx/frame.h>
#include "GameView.h"

/**
 *
 * class for the frame that the game is played within
 */
class MainFrame : public wxFrame
{
private:
    GameView* mGameView = nullptr;

public:
    void Initialize();
    void OnExit(wxCommandEvent& event);

    void OnAbout(wxCommandEvent& event);
};



#endif //PROJECT1_MAINFRAME_H