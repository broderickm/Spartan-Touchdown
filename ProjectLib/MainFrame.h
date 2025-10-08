/**
 * @file MainFrame.h
 * @author Shlok
 *
 *
 */

#ifndef PROJECT1_MAINFRAME_H
#define PROJECT1_MAINFRAME_H


class MainFrame :public wxFrame {
private:

public:
    void Initialize();
    void OnExit(wxCommandEvent& event);
    void OnClickAbout(wxCommandEvent& event);
};



#endif //PROJECT1_MAINFRAME_H