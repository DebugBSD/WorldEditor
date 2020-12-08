#pragma once
#include <wx/panel.h>
class ImageToolShavePage :
    public wxPanel
{
public:
    enum
    {
        ID_BUTTON_SHAVE = wxID_HIGHEST + 1
    };

    ImageToolShavePage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

private:
    class MainFrame* m_pMainFrame;
    // Shave
    unsigned int m_ShaveWidth;
    unsigned int m_ShaveHeight;

    class wxTextCtrl* m_pShaveWidthTextCtrl;
    class wxTextCtrl* m_pShaveHeightTextCtrl;

    void OnShaveChanged(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

