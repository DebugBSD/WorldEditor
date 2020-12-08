#include "stdafx.h"
#include "MainFrame.h"
#include "ImageToolCropPage.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>

wxBEGIN_EVENT_TABLE(ImageToolCropPage, wxPanel)
EVT_BUTTON(ID_BUTTON_CROP, ImageToolCropPage::OnCropChanged)
wxEND_EVENT_TABLE()

ImageToolCropPage::ImageToolCropPage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) :
    wxPanel(parent, id, pos, size, style),
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) }
{

    wxIntegerValidator<unsigned int>
        cropXval(&m_CropX, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        cropYval(&m_CropY, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        cropWidthval(&m_CropWidth, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        cropHeightval(&m_CropHeight, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxBoxSizer* pBoxSizer = new wxBoxSizer{ wxVERTICAL };

    wxFlexGridSizer* cropImageSizeSizer = new wxFlexGridSizer(2, 4, 2, 2);
    cropImageSizeSizer->Add(
        new wxStaticText(this, -1, "X:"),
        0,
        wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL,
        2
    );

    m_pCropXTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, cropXval);
    cropImageSizeSizer->Add(
        m_pCropXTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    cropImageSizeSizer->Add(
        new wxStaticText(this, -1, "Y:"),
        0,
        wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL,
        2
    );

    m_pCropYTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, cropYval);
    cropImageSizeSizer->Add(
        m_pCropYTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    cropImageSizeSizer->Add(
        new wxStaticText(this, -1, "Width:"),
        0,
        wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL,
        2
    );

    m_pCropWidthTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, cropWidthval);
    cropImageSizeSizer->Add(
        m_pCropWidthTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    cropImageSizeSizer->Add(
        new wxStaticText(this, -1, "Height:"),
        0,
        wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL,
        2
    );
    m_pCropHeightTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, cropHeightval);
    cropImageSizeSizer->Add(
        m_pCropHeightTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    pBoxSizer->Add(cropImageSizeSizer, 0, wxALL | wxALIGN_CENTER);

    pBoxSizer->Add(
        new wxButton(this, ID_BUTTON_CROP, "Crop"),
        0,                          // make horizontally unstretchable
        wxALL |                     // make border all around (implicit top alignment)
        wxALIGN_RIGHT,              //   and align the button to the right
        2);

    SetSizerAndFit(pBoxSizer);
}

void ImageToolCropPage::OnCropChanged(wxCommandEvent& event)
{
    wxString strX = m_pCropXTextCtrl->GetValue();
    wxString strY = m_pCropYTextCtrl->GetValue();
    wxString strWidth = m_pCropWidthTextCtrl->GetValue();
    wxString strHeight = m_pCropHeightTextCtrl->GetValue();

    m_CropX = wxAtoi(strX);
    m_CropY = wxAtoi(strY);
    m_CropWidth = wxAtoi(strWidth);
    m_CropHeight = wxAtoi(strHeight);

    m_pMainFrame->GetWorldCanvas()->CropImage(m_CropX, m_CropY, m_CropWidth, m_CropHeight);

    m_pMainFrame->UpdateView();
}