#include "stdafx.h"
#include "MainFrame.h"
#include "ImageToolResizePage.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>

wxBEGIN_EVENT_TABLE(ImageToolResizePage, wxPanel)
EVT_BUTTON(ID_BUTTON_RESIZE_TEXTURE, ImageToolResizePage::OnSizeChanged)
wxEND_EVENT_TABLE()

ImageToolResizePage::ImageToolResizePage(wxWindow* parent,
    wxWindowID id,
    const wxPoint& pos,
    const wxSize& size,
    long style) :
	wxPanel(parent, id, pos, size, style),
    m_pMainFrame {static_cast<MainFrame*>(wxTheApp->GetTopWindow())}
{

    wxIntegerValidator<unsigned int>
        val1(&m_Width, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        val2(&m_Height, wxNUM_VAL_THOUSANDS_SEPARATOR);
    wxBoxSizer* imageSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    imageSizeSizer->Add(
        new wxStaticText(this, -1, "Width:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );

    m_pSizeWidthTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, val1);
    imageSizeSizer->Add(
        m_pSizeWidthTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL | wxALIGN_CENTER,                      //   and make border all around
        2);                         // set border width to 1

    imageSizeSizer->Add(
        new wxStaticText(this, -1, "Height:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );

    m_pSizeHeightTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, val2);
    imageSizeSizer->Add(
        m_pSizeHeightTextCtrl,
        0,
        wxALL | wxALIGN_CENTER,
        2);

    imageSizeSizer->Add(
        new wxButton(this, ID_BUTTON_RESIZE_TEXTURE, "Resize"),
        0,                          // make horizontally unstretchable
        wxALL |                     // make border all around (implicit top alignment)
        wxALIGN_CENTER,              //   and align the button to the right
        2);                         // set border width to 1

    SetSizerAndFit(imageSizeSizer);
}

void ImageToolResizePage::UpdateView()
{
    wxSize size = m_pMainFrame->GetWorldCanvas()->ImageSize();
    m_pSizeWidthTextCtrl->SetValue(wxString::FromDouble(size.x));
    m_pSizeHeightTextCtrl->SetValue(wxString::FromDouble(size.y));
}

void ImageToolResizePage::OnSizeChanged(wxCommandEvent& event)
{
    wxString strWidth = m_pSizeWidthTextCtrl->GetValue();
    wxString strHeight = m_pSizeHeightTextCtrl->GetValue();
    m_Width = wxAtoi(strWidth);
    m_Height = wxAtoi(strHeight);

    m_pMainFrame->GetWorldCanvas()->ResizeImage(m_Width, m_Height);
}
