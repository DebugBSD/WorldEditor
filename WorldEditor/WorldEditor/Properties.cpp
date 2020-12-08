#include "stdafx.h"
#include <wx/app.h>
#include "Properties.h"
#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(Properties, wxWindow)
    EVT_BUTTON(ID_BUTTON_SAVE_COPY_AS,      Properties::OnSaveAs)
    EVT_BUTTON(ID_BUTTON_SAVE_CURRENT,      Properties::OnSaveCurrent)
    EVT_BUTTON(ID_BUTTON_FLIP,              Properties::OnFlipChanged)
    EVT_TEXT(ID_TEXT_CONTROL_FILENAME,      Properties::OnFilenameChanged)
wxEND_EVENT_TABLE()

Properties::Properties(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
	wxWindow(parent, id, pos, size, style),
    m_Flip{false},
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) },
    m_FileNameUpdated{false}
{

	wxBoxSizer* boxSizer = new wxBoxSizer{wxVERTICAL};

    m_pFilenameTextCtrl = new wxTextCtrl(this, ID_TEXT_CONTROL_FILENAME, "");
    boxSizer->Add(
        m_pFilenameTextCtrl,
        0,                          // make vertically stretchable
        wxEXPAND |                  // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    m_pSaveCopyAsBtn = new wxButton(this, ID_BUTTON_SAVE_COPY_AS, "Save Copy As");
    buttonsSizer->Add(
        m_pSaveCopyAsBtn,
        0,                          // make horizontally unstretchable
        wxALL,                      //   and align the button to the right
        2);                         // set border width to 1

    m_pSaveBtn = new wxButton(this, ID_BUTTON_SAVE_CURRENT, "Save Current");
    buttonsSizer->Add(
        m_pSaveBtn,
        0,                          // make horizontally unstretchable
        wxALL,                      //   and align the button to the right
        2);                         // set border width to 1

    boxSizer->Add(buttonsSizer, 0, wxALL | wxALIGN_RIGHT);

    m_pSaveCopyAsBtn->Disable();
    m_pSaveBtn->Disable();

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
    m_pFilenameTextCtrl->SetValue(m_FileName);

    m_pMainFrame->UpdateView();

    wxFileName filename{ m_FileName };
    int idx = m_pMainFrame->GetWorldCanvasNotebook()->GetPageIndex(m_pMainFrame->GetWorldCanvas());
    m_pMainFrame->GetWorldCanvasNotebook()->SetPageText(idx, filename.GetName());

    m_pMainFrame->GetStatusBar()->SetStatusText(m_pMainFrame->GetWorldCanvas()->getImage()->getFileName());
}


void Properties::OnSaveAs(wxCommandEvent& event)
{
    if (m_pFilenameTextCtrl->GetValue() != m_FileName)
    {
        // We save a new copy (modified or not) to the new file.
        m_FileName = m_pFilenameTextCtrl->GetValue();
        m_FileNameUpdated = true;

        WorldCanvas* pCurrentCanvas = m_pMainFrame->GetWorldCanvas();
        pCurrentCanvas->SaveImageAs(m_FileName);
        pCurrentCanvas->OpenTexture(m_FileName);
        UpdateView();
    }
    else
    {
        // We show the window and ask for the file which we want to save.
        wxFileDialog
            saveFileDialog(this, _("Save Image file"), "", "",
                "Image files (*.png;*.jpg)|*.png;*.jpg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (saveFileDialog.ShowModal() == wxID_CANCEL)
            return;     // the user changed idea...

        m_FileName = saveFileDialog.GetPath();
        m_FileNameUpdated = true;

        WorldCanvas* pCurrentCanvas = m_pMainFrame->GetWorldCanvas();
        pCurrentCanvas->SaveImageAs(m_FileName);
        pCurrentCanvas->OpenTexture(m_FileName);
        UpdateView();

    }
}

void Properties::OnSaveCurrent(wxCommandEvent& event)
{
    if(m_pMainFrame->GetWorldCanvas() != nullptr)
        m_pMainFrame->GetWorldCanvas()->SaveImage();
}

void Properties::OnFlipChanged(wxCommandEvent& event)
{
    int stop = 1;
}

void Properties::OnFilenameChanged(wxCommandEvent& event)
{
    if (m_pFilenameTextCtrl->GetValue() != "")
    {
        m_pSaveCopyAsBtn->Enable();
        m_pSaveBtn->Enable();
    }
    else
    {
        m_pSaveCopyAsBtn->Disable();
        m_pSaveBtn->Disable();
    }
}

