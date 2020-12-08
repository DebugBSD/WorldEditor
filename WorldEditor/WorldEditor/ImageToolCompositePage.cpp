#include "stdafx.h"
#include "MainFrame.h"
#include "ImageToolCompositePage.h"
#include "weImage.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>

wxBEGIN_EVENT_TABLE(ImageToolCompositePage, wxPanel)
EVT_BUTTON(ID_BUTTON_COMPOSITE, ImageToolCompositePage::OnCompositeChanged)
EVT_BUTTON(ID_BUTTON_COMPOSITE_FIND_TEXTURE0, ImageToolCompositePage::OnFindTexture0)
EVT_BUTTON(ID_BUTTON_COMPOSITE_FIND_TEXTURE1, ImageToolCompositePage::OnFindTexture1)
EVT_BUTTON(ID_BUTTON_COMPOSITE_FIND_TEXTURE2, ImageToolCompositePage::OnFindTexture2)
EVT_BUTTON(ID_BUTTON_COMPOSITE_FIND_TEXTURE3, ImageToolCompositePage::OnFindTexture3)
wxEND_EVENT_TABLE()

ImageToolCompositePage::ImageToolCompositePage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
    wxPanel(parent, id, pos, size, style),
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) }
{

    wxBoxSizer* pBoxSizer = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer* compositeImageSizeSizer = new wxFlexGridSizer(4, 7, 2, 2);

    // Row 0
    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "File:"), 0, wxALL | wxALIGN_CENTER, 2);

    m_pCompositeFilename0TextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize{ 100, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompositeFilename0TextCtrl, 0, wxALL | wxEXPAND, 2);

    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "X:"), 0, wxALL | wxALIGN_CENTER, 2);

    m_pCompisteX0TextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompisteX0TextCtrl, 0, wxALL, 2);

    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "Y:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompisteY0TextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompisteY0TextCtrl, 0, wxALL, 2);

    compositeImageSizeSizer->Add(new wxButton(this, ID_BUTTON_COMPOSITE_FIND_TEXTURE0, "...", wxDefaultPosition, wxSize{ 20,-1 }), 0, wxALL, 2);

    // Row 1
    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "File:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompositeFilename1TextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize{ 100, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompositeFilename1TextCtrl, 0, wxALL | wxEXPAND, 2);

    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "X:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompisteX1TextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompisteX1TextCtrl, 0, wxALL, 2);

    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "Y:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompisteY1TextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompisteY1TextCtrl, 0, wxALL, 2);

    compositeImageSizeSizer->Add(new wxButton(this, ID_BUTTON_COMPOSITE_FIND_TEXTURE1, "...", wxDefaultPosition, wxSize{ 20,-1 }), 0, wxALL, 2);

    // Row 2
    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "File:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompositeFilename2TextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize{ 100, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompositeFilename2TextCtrl, 0, wxALL | wxEXPAND, 2);

    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "X:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompisteX2TextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompisteX2TextCtrl, 0, wxALL, 2);

    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "Y:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompisteY2TextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompisteY2TextCtrl, 0, wxALL, 2);

    compositeImageSizeSizer->Add(new wxButton(this, ID_BUTTON_COMPOSITE_FIND_TEXTURE2, "...", wxDefaultPosition, wxSize{ 20,-1 }), 0, wxALL, 2);

    // Row 3
    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "File:"), 0, wxALL | wxALIGN_CENTER, 2);

    m_pCompositeFilename3TextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize{ 100, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompositeFilename3TextCtrl, 0, wxALL | wxEXPAND, 2);

    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "X:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompisteX3TextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompisteX3TextCtrl, 0, wxALL, 2);

    compositeImageSizeSizer->Add(new wxStaticText(this, -1, "Y:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompisteY3TextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    compositeImageSizeSizer->Add(m_pCompisteY3TextCtrl, 0, wxALL, 2);

    compositeImageSizeSizer->Add(new wxButton(this, ID_BUTTON_COMPOSITE_FIND_TEXTURE3, "...", wxDefaultPosition, wxSize{ 20,-1 }), 0, wxALL, 2);

    pBoxSizer->Add(compositeImageSizeSizer, 0, wxALL | wxEXPAND);

    pBoxSizer->Add(new wxButton(this, ID_BUTTON_COMPOSITE, "Composite"), 0, wxALL, 2);

    SetSizerAndFit(pBoxSizer);
}

void ImageToolCompositePage::OnCompositeChanged(wxCommandEvent& event)
{
    std::vector<TCompositeImage> textures;

    textures.resize(4);
    TCompositeImage tempTexture;

    tempTexture.m_File = m_pCompositeFilename0TextCtrl->GetValue();
    tempTexture.m_Point.x = wxAtoi(m_pCompisteX0TextCtrl->GetValue());
    tempTexture.m_Point.y = wxAtoi(m_pCompisteY0TextCtrl->GetValue());
    textures[0] = tempTexture;

    tempTexture.m_File = m_pCompositeFilename1TextCtrl->GetValue();
    tempTexture.m_Point.x = wxAtoi(m_pCompisteX1TextCtrl->GetValue());
    tempTexture.m_Point.y = wxAtoi(m_pCompisteY1TextCtrl->GetValue());
    textures[1] = tempTexture;

    tempTexture.m_File = m_pCompositeFilename2TextCtrl->GetValue();
    tempTexture.m_Point.x = wxAtoi(m_pCompisteX2TextCtrl->GetValue());
    tempTexture.m_Point.y = wxAtoi(m_pCompisteY2TextCtrl->GetValue());
    textures[2] = tempTexture;

    tempTexture.m_File = m_pCompositeFilename3TextCtrl->GetValue();
    tempTexture.m_Point.x = wxAtoi(m_pCompisteX3TextCtrl->GetValue());
    tempTexture.m_Point.y = wxAtoi(m_pCompisteY3TextCtrl->GetValue());
    textures[3] = tempTexture;

    m_pMainFrame->GetWorldCanvas()->CompositeImage(textures);

    m_pMainFrame->UpdateView();
}


void ImageToolCompositePage::OnFindTexture0(wxCommandEvent& event)
{
    wxFileDialog
        openFileDialog(this, _("Open Image file"), "", "",
            "Image files (*.png;*.jpg)|*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    m_pCompositeFilename0TextCtrl->SetValue(openFileDialog.GetPath());
}

void ImageToolCompositePage::OnFindTexture1(wxCommandEvent& event)
{
    wxFileDialog
        openFileDialog(this, _("Open Image file"), "", "",
            "Image files (*.png;*.jpg)|*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    m_pCompositeFilename1TextCtrl->SetValue(openFileDialog.GetPath());
}

void ImageToolCompositePage::OnFindTexture2(wxCommandEvent& event)
{
    wxFileDialog
        openFileDialog(this, _("Open Image file"), "", "",
            "Image files (*.png;*.jpg)|*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    m_pCompositeFilename2TextCtrl->SetValue(openFileDialog.GetPath());
}

void ImageToolCompositePage::OnFindTexture3(wxCommandEvent& event)
{
    wxFileDialog
        openFileDialog(this, _("Open Image file"), "", "",
            "Image files (*.png;*.jpg)|*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    m_pCompositeFilename3TextCtrl->SetValue(openFileDialog.GetPath());
}