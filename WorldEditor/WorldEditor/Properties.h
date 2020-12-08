#pragma once
#include <wx/window.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/valnum.h>

class Properties :
    public wxWindow
{
public:
    enum
    {
        ID_BUTTON_SAVE_COPY_AS = wxID_HIGHEST + 1,
        ID_BUTTON_SAVE_CURRENT,
        ID_BUTTON_FLIP,
        ID_TEXT_CONTROL_FILENAME
    };

    Properties(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

    void SetFileName(const wxString& fileName);
private:
    wxString m_FileName;
    class MainFrame* m_pMainFrame;

    bool m_FileNameUpdated;

    // Flip
    bool m_Flip;

    // Filename control
    wxTextCtrl* m_pFilenameTextCtrl;

    // Buttons 
    wxButton *m_pSaveBtn;
    wxButton* m_pSaveCopyAsBtn;

private:

    void UpdateView();
    void OnSaveAs(wxCommandEvent& event);
    void OnSaveCurrent(wxCommandEvent& event);
    void OnFlipChanged(wxCommandEvent& event);
    void OnFilenameChanged(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

