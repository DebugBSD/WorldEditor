#pragma once
#include <wx/panel.h>

class ImageToolCompositePage :
    public wxPanel
{
public:
    enum
    {
        ID_BUTTON_COMPOSITE = wxID_HIGHEST + 1,
        ID_BUTTON_COMPOSITE_FIND_TEXTURE0,
        ID_BUTTON_COMPOSITE_FIND_TEXTURE1,
        ID_BUTTON_COMPOSITE_FIND_TEXTURE2,
        ID_BUTTON_COMPOSITE_FIND_TEXTURE3
    };

    ImageToolCompositePage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);
private:

    // Composite Controls
    class wxTextCtrl* m_pCompositeFilename0TextCtrl;
    class wxTextCtrl* m_pCompositeFilename1TextCtrl;
    class wxTextCtrl* m_pCompositeFilename2TextCtrl;
    class wxTextCtrl* m_pCompositeFilename3TextCtrl;
    class wxTextCtrl* m_pCompisteX0TextCtrl;
    class wxTextCtrl* m_pCompisteY0TextCtrl;
    class wxTextCtrl* m_pCompisteX1TextCtrl;
    class wxTextCtrl* m_pCompisteY1TextCtrl;
    class wxTextCtrl* m_pCompisteX2TextCtrl;
    class wxTextCtrl* m_pCompisteY2TextCtrl;
    class wxTextCtrl* m_pCompisteX3TextCtrl;
    class wxTextCtrl* m_pCompisteY3TextCtrl;

    void OnCompositeChanged(wxCommandEvent& event);
    void OnFindTexture0(wxCommandEvent& event);
    void OnFindTexture1(wxCommandEvent& event);
    void OnFindTexture2(wxCommandEvent& event);
    void OnFindTexture3(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();

};

