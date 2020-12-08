#include "stdafx.h"
#include "MainFrame.h"
#include "ImageToolTrimPage.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>

wxBEGIN_EVENT_TABLE(ImageToolTrimPage, wxPanel)
    EVT_BUTTON(ID_BUTTON_TRIM, ImageToolTrimPage::OnTrimChanged)
wxEND_EVENT_TABLE()

ImageToolTrimPage::ImageToolTrimPage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) :
    wxPanel(parent, id, pos, size, style),
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) }
{
    wxBoxSizer* trimImageSizer = new wxBoxSizer(wxHORIZONTAL);
    trimImageSizer->Add(
        new wxStaticText(this, -1, "Fuzz:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );

    m_pFuzzTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0);
    trimImageSizer->Add(
        m_pFuzzTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    trimImageSizer->Add(
        new wxButton(this, ID_BUTTON_TRIM, "Trim"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1
    SetSizerAndFit(trimImageSizer);
}

void ImageToolTrimPage::OnTrimChanged(wxCommandEvent& event)
{
    wxString strFuzz = m_pFuzzTextCtrl->GetValue();
    double value;
    strFuzz.ToDouble(&value);

    m_pMainFrame->GetWorldCanvas()->TrimImage(value);

    m_pMainFrame->UpdateView();
}
