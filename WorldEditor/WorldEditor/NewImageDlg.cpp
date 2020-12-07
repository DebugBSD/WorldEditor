#include "stdafx.h"
#include "NewImageDlg.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/valnum.h>

wxBEGIN_EVENT_TABLE(NewImageDlg, wxDialog)
EVT_BUTTON(wxID_OK, NewImageDlg::OnOK)
EVT_BUTTON(wxID_CANCEL, NewImageDlg::OnCancel)
EVT_TEXT(ID_HEIGHT_TEXTCTRL, NewImageDlg::OnTextHeightChanged)
EVT_TEXT(ID_WIDTH_TEXTCTRL, NewImageDlg::OnTextWidthChanged)
wxEND_EVENT_TABLE()

NewImageDlg::NewImageDlg() :
	wxDialog(NULL, wxID_ANY, "New Image", wxDefaultPosition, wxDefaultSize)
{

    wxIntegerValidator<unsigned int>
        heightVal(&m_Height, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        widthVal(&m_Width, wxNUM_VAL_THOUSANDS_SEPARATOR);

	wxBoxSizer* verticalSizer = new wxBoxSizer{ wxVERTICAL };

    wxBoxSizer* sizeImageSizer = new wxBoxSizer(wxHORIZONTAL);
    sizeImageSizer->Add(
        new wxStaticText(this, -1, "Width:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pWidthTextCtrl = new wxTextCtrl(this, ID_WIDTH_TEXTCTRL, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, widthVal);
    sizeImageSizer->Add(
        m_pWidthTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    sizeImageSizer->Add(
        new wxStaticText(this, -1, "Height:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pHeightTextCtrl = new wxTextCtrl(this, ID_HEIGHT_TEXTCTRL, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, heightVal);
    sizeImageSizer->Add(
        m_pHeightTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    verticalSizer->Add(sizeImageSizer, 0, wxALL | wxALIGN_CENTER);

    wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);

    m_pOKButton = new wxButton(this, wxID_OK, "OK");
    m_pOKButton->Disable();
    buttonsSizer->Add(
        m_pOKButton,
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1

    m_pCancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonsSizer->Add(
        m_pCancelButton,
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1

    verticalSizer->Add(buttonsSizer, 0, wxALL | wxALIGN_RIGHT);

	SetSizerAndFit(verticalSizer);
}

void NewImageDlg::OnOK(wxCommandEvent& event)
{

	EndModal(wxID_OK);
}

void NewImageDlg::OnCancel(wxCommandEvent& event)
{

	EndModal(wxID_CANCEL);
}

void NewImageDlg::OnTextHeightChanged(wxCommandEvent& event)
{
    wxString str = m_pHeightTextCtrl->GetValue();
    m_Height = wxAtoi(str);

    EnableButton();
}

void NewImageDlg::OnTextWidthChanged(wxCommandEvent& event)
{
    wxString str = m_pWidthTextCtrl->GetValue();
    m_Width = wxAtoi(str);

    EnableButton();
}

void NewImageDlg::EnableButton(void)
{
    if (m_Height >= 8 && m_Width >= 8)
    {
        m_pOKButton->Enable();
    }
    else
    {
        m_pOKButton->Disable();
    }
}
