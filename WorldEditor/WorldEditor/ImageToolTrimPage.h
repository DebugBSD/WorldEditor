#pragma once
#include <wx/panel.h>

class ImageToolTrimPage :
    public wxPanel
{
public:
    enum
    {
        ID_BUTTON_TRIM = wxID_HIGHEST + 1
    };
    ImageToolTrimPage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);
private:

    class wxTextCtrl* m_pFuzzTextCtrl;

    void OnTrimChanged(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();

};

