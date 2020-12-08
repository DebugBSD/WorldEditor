#pragma once
#include <wx/panel.h>
class ImageToolFlipPage :
    public wxPanel
{
public:
    enum
    {
        ID_RADIO_BUTTON_FLIP_HORIZONTAL = wxID_HIGHEST + 1,
        ID_RADIO_BUTTON_FLIP_VERTICAL = wxID_HIGHEST + 1
    };

    ImageToolFlipPage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

private:
    class MainFrame* m_pMainFrame;

    class wxRadioButton* m_pFlipHorizontal;
    class wxRadioButton* m_pFlipVertical;

    void OnFlipChanged(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
