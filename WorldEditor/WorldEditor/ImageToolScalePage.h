#pragma once
#include <wx/panel.h>
class ImageToolScalePage :
    public wxPanel
{
public:
    enum
    {
        ID_BUTTON_SCALE = wxID_HIGHEST + 1
    };
    ImageToolScalePage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

private:
    class MainFrame* m_pMainFrame;

    // Scale 
    float m_ScaleWidth;
    float m_ScaleHeight;

    class wxTextCtrl* m_pScaleXTextCtrl;
    class wxTextCtrl* m_pScaleYTextCtrl;

    void OnScaleChanged(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

