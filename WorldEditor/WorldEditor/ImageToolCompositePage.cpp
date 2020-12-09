#include "stdafx.h"
#include "MainFrame.h"
#include "ImageToolCompositePage.h"
#include "weImage.h"

#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valnum.h>


wxBEGIN_EVENT_TABLE(CompositePanel, wxPanel)
    EVT_BUTTON(ID_BUTTON_COMPOSITE_FIND_TEXTURE, CompositePanel::OnFindTexture)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(ImageToolCompositePage, wxScrolledWindow)
    EVT_BUTTON(ID_BUTTON_COMPOSITE, ImageToolCompositePage::OnCompositeChanged)
    EVT_BUTTON(ID_BUTTON_ADD_NEW_IMAGE, ImageToolCompositePage::OnNewPanelBtn)
wxEND_EVENT_TABLE()

ImageToolCompositePage::ImageToolCompositePage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
    wxScrolledWindow(parent, id, pos, size, style),
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) }
{

    m_pBoxSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* pHorizontalSizer = new wxBoxSizer{ wxHORIZONTAL };
    pHorizontalSizer->Add(new wxButton(this, ID_BUTTON_COMPOSITE, "Composite"), 0, wxALL, 2);
    pHorizontalSizer->Add(new wxButton(this, ID_BUTTON_ADD_NEW_IMAGE, "Add new image"), 0, wxALL, 2);
    m_pBoxSizer->Add(pHorizontalSizer, 1, wxALL | wxEXPAND, 2);

    // add a series of widgets
    for (int w = 1; w <= 4; w++)
    {
        CompositePanel* b = new CompositePanel(this, wxID_ANY); 
        m_Images.push_back(b);
        m_pBoxSizer->Add(b, 0, wxALL, 3);
    }

    this->SetSizer(m_pBoxSizer);

    // this part makes the scrollbars show up
    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(5, 5);
}

void ImageToolCompositePage::OnCompositeChanged(wxCommandEvent& event)
{
    std::vector<TCompositeImage> textures;

    TCompositeImage tempTexture;

    for (CompositePanel* pCompImage : m_Images)
    {
        tempTexture.m_File = pCompImage->m_pCompositeFilenameTextCtrl->GetValue();
        tempTexture.m_Point.x = wxAtoi(pCompImage->m_pCompisteXTextCtrl->GetValue());
        tempTexture.m_Point.y = wxAtoi(pCompImage->m_pCompisteYTextCtrl->GetValue());
        textures.push_back(tempTexture);
    }

    m_pMainFrame->GetWorldCanvas()->CompositeImage(textures);

    m_pMainFrame->UpdateView();
}

void ImageToolCompositePage::OnNewPanelBtn(wxCommandEvent& event)
{
    CompositePanel* b = new CompositePanel(this, wxID_ANY);
    m_Images.push_back(b);
    m_pBoxSizer->Add(b, 0, wxALL, 3);
    //SetSizer(pSizer);

    FitInside();
    //SetScrollRate(5, 5);
}

CompositePanel::CompositePanel(wxWindow* parent, wxWindowID id) :
    wxPanel(parent, id)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(new wxStaticText(this, -1, "File:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompositeFilenameTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize{ 100, -1 }, 0);
    sizer->Add(m_pCompositeFilenameTextCtrl, 0, wxALL | wxEXPAND, 2);

    sizer->Add(new wxStaticText(this, -1, "X:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompisteXTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    sizer->Add(m_pCompisteXTextCtrl, 0, wxALL, 2);

    sizer->Add(new wxStaticText(this, -1, "Y:"), 0, wxALL | wxALIGN_CENTER, 2);
    m_pCompisteYTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
    sizer->Add(m_pCompisteYTextCtrl, 0, wxALL, 2);

    sizer->Add(new wxButton(this, ID_BUTTON_COMPOSITE_FIND_TEXTURE, "...", wxDefaultPosition, wxSize{ 20,-1 }), 0, wxALL, 2);
    sizer->Add(new wxButton(this, wxID_ANY, "Remove", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT), 0, wxALL, 2);

    SetSizer(sizer);
}

void CompositePanel::OnFindTexture(wxCommandEvent& event)
{
    wxFileDialog
        openFileDialog(this, _("Open Image file"), "", "",
            "Image files (*.png;*.jpg)|*.png;*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;     // the user changed idea...

    m_pCompositeFilenameTextCtrl->SetValue(openFileDialog.GetPath());
}
