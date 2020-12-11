#pragma once
#include <wx/wx.h>
#include <vector>

class SplitPanel : public wxPanel
{
public:
    enum
    {
        ID_BUTTON_SPLIT_CREATE_TEXTURE = wxID_HIGHEST + 1
    };

    SplitPanel(wxWindow* parent, wxWindowID id);

    class wxTextCtrl* m_pSplitFilenameTextCtrl;
    class wxTextCtrl* m_pSplitXTextCtrl;
    class wxTextCtrl* m_pSplitYTextCtrl;
    class wxTextCtrl* m_pSplitWidthTextCtrl;
    class wxTextCtrl* m_pSplitHeightTextCtrl;

private:
    // Split
    unsigned int m_SplitX;
    unsigned int m_SplitY;
    unsigned int m_SplitWidth;
    unsigned int m_SplitHeight;

    void OnCreateNewTexture(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

class ImageToolSplitPage :
    public wxScrolledWindow
{
public:
    enum
    {
        ID_BUTTON_SPLIT = wxID_HIGHEST + 1,
        ID_BUTTON_ADD_NEW_IMAGE,
        ID_BUTTON_AUTOSPLIT
    };

    ImageToolSplitPage(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

private:
    class MainFrame* m_pMainFrame;
    class wxBoxSizer* m_pBoxSizer;
    class wxTextCtrl* m_pSplitWidthTextCtrl;
    class wxTextCtrl* m_pSplitHeightTextCtrl;

    std::vector<SplitPanel*> m_Images;

    wxBoxSizer* CreateHeader();

    void OnSplit(wxCommandEvent& event);
    void OnAutoSplit(wxCommandEvent& event);
    void OnNewPanelBtn(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();

};

