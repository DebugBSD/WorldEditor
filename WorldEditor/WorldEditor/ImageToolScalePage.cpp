#include "stdafx.h"
#include "ImageToolScalePage.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>

wxBEGIN_EVENT_TABLE(ImageToolScalePage, wxPanel)
EVT_BUTTON(ID_BUTTON_SCALE, ImageToolScalePage::OnScaleChanged)
wxEND_EVENT_TABLE()

ImageToolScalePage::ImageToolScalePage(wxWindow* parent,
    wxWindowID id,
    const wxPoint& pos,
    const wxSize& size,
    long style):
    wxPanel(parent, id, pos, size, style)
{

    wxFloatingPointValidator<float>
        scaleWidthVal(&m_ScaleWidth, wxNUM_VAL_DEFAULT);

    wxFloatingPointValidator<float>
        scaleHeightVal(&m_ScaleHeight, wxNUM_VAL_DEFAULT);

    wxBoxSizer* scaleImageSizer = new wxBoxSizer(wxHORIZONTAL);
    scaleImageSizer->Add(
        new wxStaticText(this, -1, "X:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pScaleXTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, scaleWidthVal);
    scaleImageSizer->Add(
        m_pScaleXTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    scaleImageSizer->Add(
        new wxStaticText(this, -1, "Y:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pScaleYTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, scaleHeightVal);
    scaleImageSizer->Add(
        m_pScaleYTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    scaleImageSizer->Add(
        new wxButton(this, ID_BUTTON_SCALE, "Scale"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1
    SetSizerAndFit(scaleImageSizer);
}


void ImageToolScalePage::OnScaleChanged(wxCommandEvent& event)
{
    wxString strX = m_pScaleXTextCtrl->GetValue();
    wxString strY = m_pScaleYTextCtrl->GetValue();
    double value;
    strX.ToDouble(&value);
    m_ScaleWidth = (float)value;

    strY.ToDouble(&value);
    m_ScaleHeight = (float)value;

    //m_pMainFrame->GetWorldCanvas()->ScaleImage(m_ScaleWidth, m_ScaleHeight);

    //UpdateView();
}