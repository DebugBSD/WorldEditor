#include "stdafx.h"
#include <wx/app.h>
#include "Properties.h"
#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(Properties, wxWindow)
    EVT_BUTTON(ID_BUTTON_SAVE_COPY_AS,      Properties::OnSaveAs)
    EVT_BUTTON(ID_BUTTON_SAVE_CURRENT,      Properties::OnSaveCurrent)
    EVT_BUTTON(ID_BUTTON_FLIP,              Properties::OnFlipChanged)
wxEND_EVENT_TABLE()

Properties::Properties(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
	wxWindow(parent, id, pos, size, style),
    m_Flip{false},
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) },
    m_FileNameUpdated{false}
{

	wxBoxSizer* boxSizer = new wxBoxSizer{wxVERTICAL};

    m_pFilenameTextCtrl = new wxTextCtrl(this, -1, "");
    boxSizer->Add(
        m_pFilenameTextCtrl,
        0,                          // make vertically stretchable
        wxEXPAND |                  // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonsSizer->Add(
        new wxButton(this, ID_BUTTON_SAVE_COPY_AS, "Save Copy As"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1

    buttonsSizer->Add(
        new wxButton(this, ID_BUTTON_SAVE_CURRENT, "Save Current"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1

    boxSizer->Add(buttonsSizer, 0, wxALL | wxALIGN_RIGHT);

	SetSizerAndFit(boxSizer);
}

void Properties::SetFileName(const wxString& fileName)
{
    m_FileName = fileName; 
    m_FileNameUpdated = true;
    UpdateView();
}

void Properties::UpdateView()
{
    wxSize size = m_pMainFrame->GetWorldCanvas()->ImageSize();

    m_pFilenameTextCtrl->SetValue(m_FileName);

    //m_pSizeWidthTextCtrl->SetValue(wxString::FromDouble(size.x));
    //m_pSizeHeightTextCtrl->SetValue(wxString::FromDouble(size.y));
}


void Properties::OnSaveAs(wxCommandEvent& event)
{
    /* 
     * Verificaciones:
     * - El nombre del fichero debe ser igual que el de la caja de texto.
     * - El fichero actual haya sido modificado.
     */
}

void Properties::OnSaveCurrent(wxCommandEvent& event)
{
    m_pMainFrame->GetWorldCanvas()->SaveImage();
}

void Properties::OnFlipChanged(wxCommandEvent& event)
{
    int stop = 1;
}

