#pragma once
#include <wx/panel.h>

class ImageToolRotatePage :
    public wxPanel
{
public:
    enum
    {
        ID_BUTTON_ROTATE = wxID_HIGHEST + 1,
    };

    ImageToolRotatePage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

private:
    class MainFrame* m_pMainFrame;

    class wxTextCtrl* m_pRotationTextCtrl;

    // Rotation
    float m_Angle;

    void OnRotationChanged(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();

};

