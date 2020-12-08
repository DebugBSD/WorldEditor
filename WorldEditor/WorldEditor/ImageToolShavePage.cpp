#include "stdafx.h"
#include "MainFrame.h"
#include "ImageToolShavePage.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>

wxBEGIN_EVENT_TABLE(ImageToolShavePage, wxPanel)
EVT_BUTTON(ID_BUTTON_SHAVE, ImageToolShavePage::OnShaveChanged)
wxEND_EVENT_TABLE()


ImageToolShavePage::ImageToolShavePage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) :
	wxPanel(parent, id, pos, size, style),
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) }
{
    wxIntegerValidator<unsigned int>
        shaveWidthval(&m_ShaveWidth, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        shaveHeightval(&m_ShaveHeight, wxNUM_VAL_THOUSANDS_SEPARATOR);


    wxBoxSizer* shaveImageSizer = new wxBoxSizer(wxHORIZONTAL);
    shaveImageSizer->Add(
        new wxStaticText(this, -1, "Width:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pShaveWidthTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, shaveWidthval);
    shaveImageSizer->Add(
        m_pShaveWidthTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    shaveImageSizer->Add(
        new wxStaticText(this, -1, "Height:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pShaveHeightTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, shaveHeightval);
    shaveImageSizer->Add(
        m_pShaveHeightTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    shaveImageSizer->Add(
        new wxButton(this, ID_BUTTON_SHAVE, "Shave"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1

    SetSizerAndFit(shaveImageSizer);
}

void ImageToolShavePage::OnShaveChanged(wxCommandEvent& event)
{
    wxString strWidth = m_pShaveWidthTextCtrl->GetValue();
    wxString strHeight = m_pShaveHeightTextCtrl->GetValue();

    m_ShaveWidth = wxAtoi(strWidth);
    m_ShaveHeight = wxAtoi(strHeight);

    m_pMainFrame->GetWorldCanvas()->ShaveImage(m_ShaveWidth, m_ShaveHeight);

    m_pMainFrame->UpdateView();
}