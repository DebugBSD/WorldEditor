#pragma once
#include <wx/wx.h>
#include <vector>

class CompositePanel : public wxPanel
{
public:
    enum
    {
        ID_BUTTON_COMPOSITE_FIND_TEXTURE = wxID_HIGHEST + 1
    };

    CompositePanel(wxWindow* parent, wxWindowID id);

    class wxTextCtrl* m_pCompositeFilenameTextCtrl;
    class wxTextCtrl* m_pCompisteXTextCtrl;
    class wxTextCtrl* m_pCompisteYTextCtrl;

private:

    void OnFindTexture(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

class ImageToolCompositePage :
    public wxScrolledWindow
{
public:
    enum
    {
        ID_BUTTON_COMPOSITE = wxID_HIGHEST + 1,
        ID_BUTTON_ADD_NEW_IMAGE
    };

    ImageToolCompositePage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

private:
    class MainFrame* m_pMainFrame;
    class wxBoxSizer* m_pBoxSizer;

    std::vector<CompositePanel*> m_Images;

    void OnCompositeChanged(wxCommandEvent& event);
    void OnNewPanelBtn(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();

};

