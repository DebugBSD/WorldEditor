#pragma once
#include <wx/panel.h>
class Logger :
    public wxPanel
{
public:

    Logger(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

private:
    class MainFrame* m_pMainFrame;

    class wxTextCtrl* m_pTextCtrlLogger;
    class wxLogTextCtrl* m_pLogTextControl;
};

