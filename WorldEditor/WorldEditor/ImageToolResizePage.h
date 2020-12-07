#pragma once
#include <wx/panel.h>
class ImageToolResizePage :
    public wxPanel
{
public:
    enum {
        ID_BUTTON_RESIZE_TEXTURE = wxID_HIGHEST + 1
    };

    ImageToolResizePage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

private:

    // Size properties
    unsigned int m_Width;
    unsigned int m_Height;

    class wxTextCtrl* m_pSizeWidthTextCtrl;
    class wxTextCtrl* m_pSizeHeightTextCtrl;

    void OnSizeChanged(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

