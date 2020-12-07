#include "stdafx.h"
#include "ImageToolRotatePage.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>

wxBEGIN_EVENT_TABLE(ImageToolRotatePage, wxPanel)
EVT_BUTTON(ID_BUTTON_ROTATE, ImageToolRotatePage::OnRotationChanged)
wxEND_EVENT_TABLE()

ImageToolRotatePage::ImageToolRotatePage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) :
    wxPanel(parent, id, pos, size, style)
{

    wxFloatingPointValidator<float>
        rot(&m_Angle, wxNUM_VAL_DEFAULT);

    wxBoxSizer* rotateImageSizer = new wxBoxSizer(wxHORIZONTAL);
    rotateImageSizer->Add(
        new wxStaticText(this, -1, "Degrees:"),
        0,
        wxALL,
        2
    );

    m_pRotationTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, rot);
    rotateImageSizer->Add(
        m_pRotationTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    rotateImageSizer->Add(
        new wxButton(this, ID_BUTTON_ROTATE, "Rotate"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1

    SetSizerAndFit(rotateImageSizer);
}


void ImageToolRotatePage::OnRotationChanged(wxCommandEvent& event)
{
    wxString strRotation = m_pRotationTextCtrl->GetValue();
    double value;
    strRotation.ToDouble(&value);

    m_Angle = (float)value;

    //m_pMainFrame->GetWorldCanvas()->RotateImage(m_Angle);

    //UpdateView();
}