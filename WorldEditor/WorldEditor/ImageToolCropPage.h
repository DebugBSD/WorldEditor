#pragma once
#include <wx/panel.h>

class ImageToolCropPage :
    public wxPanel
{
public:
    enum
    {
        ID_BUTTON_CROP = wxID_HIGHEST + 1
    };

    ImageToolCropPage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);


private:
    // Crop
    unsigned int m_CropX;
    unsigned int m_CropY;
    unsigned int m_CropWidth;
    unsigned int m_CropHeight;

    class wxTextCtrl* m_pCropXTextCtrl;
    class wxTextCtrl* m_pCropYTextCtrl;
    class wxTextCtrl* m_pCropWidthTextCtrl;
    class wxTextCtrl* m_pCropHeightTextCtrl;

    void OnCropChanged(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

