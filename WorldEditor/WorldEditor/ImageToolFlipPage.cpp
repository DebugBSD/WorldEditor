#include "stdafx.h"
#include "MainFrame.h"
#include "ImageToolFlipPage.h"

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>
#include <wx/radiobut.h>

wxBEGIN_EVENT_TABLE(ImageToolFlipPage, wxPanel)
    EVT_RADIOBUTTON(ID_RADIO_BUTTON_FLIP_HORIZONTAL, ImageToolFlipPage::OnFlipChanged)
    EVT_RADIOBUTTON(ID_RADIO_BUTTON_FLIP_VERTICAL, ImageToolFlipPage::OnFlipChanged)
wxEND_EVENT_TABLE()


ImageToolFlipPage::ImageToolFlipPage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) :
    wxPanel(parent, id, pos, size, style),
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) }
{
    
    wxBoxSizer* flipImageSizer = new wxBoxSizer(wxVERTICAL);
   
    m_pFlipHorizontal = new wxRadioButton(this, ID_RADIO_BUTTON_FLIP_HORIZONTAL, "Flip Horizontal", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    flipImageSizer->Add(
        m_pFlipHorizontal,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1
    m_pFlipHorizontal->SetValue(true);

    m_pFlipVertical = new wxRadioButton(this, ID_RADIO_BUTTON_FLIP_VERTICAL, "Flip Vertical", wxDefaultPosition, wxDefaultSize);
    flipImageSizer->Add(
        m_pFlipVertical,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    SetSizerAndFit(flipImageSizer);
}

void ImageToolFlipPage::OnFlipChanged(wxCommandEvent& event)
{
    bool isChecked = m_pFlipHorizontal->GetValue();

    if (isChecked) // Flip Horizontal
    {
        m_pMainFrame->GetWorldCanvas()->FlipImage();
        m_pMainFrame->UpdateView();
    }
    else // Flip Vertical
    {
        m_pMainFrame->GetWorldCanvas()->FlipImage();
        m_pMainFrame->UpdateView();
    }
}