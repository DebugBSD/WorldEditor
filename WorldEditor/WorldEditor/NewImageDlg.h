#pragma once
#include <wx/dialog.h>
class NewImageDlg :
    public wxDialog
{
public:
    enum
    {
        ID_BUTTON_SAVE_COPY_AS = wxID_HIGHEST + 1,
        ID_HEIGHT_TEXTCTRL,
        ID_WIDTH_TEXTCTRL
    };

    NewImageDlg();

    wxSize GetSizeOfCanvas() { return wxSize{(int)m_Width, (int)m_Height}; }

private:

    unsigned int m_Width;
    unsigned int m_Height;

    class wxButton* m_pOKButton;
    class wxButton* m_pCancelButton;

    class wxTextCtrl* m_pWidthTextCtrl;
    class wxTextCtrl* m_pHeightTextCtrl;

    void EnableButton(void);
    void OnOK(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);
    void OnTextHeightChanged(wxCommandEvent &event);
    void OnTextWidthChanged(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

