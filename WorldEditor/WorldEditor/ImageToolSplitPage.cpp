#include "stdafx.h"
#include "MainFrame.h"
#include "ImageToolSplitPage.h"

wxBEGIN_EVENT_TABLE(SplitPanel, wxPanel)
	EVT_BUTTON(ID_BUTTON_SPLIT_CREATE_TEXTURE, SplitPanel::OnCreateNewTexture)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(ImageToolSplitPage, wxScrolledWindow)
	EVT_BUTTON(ID_BUTTON_SPLIT, ImageToolSplitPage::OnSplit)
	EVT_BUTTON(ID_BUTTON_AUTOSPLIT, ImageToolSplitPage::OnAutoSplit)
	EVT_BUTTON(ID_BUTTON_ADD_NEW_IMAGE, ImageToolSplitPage::OnNewPanelBtn)
wxEND_EVENT_TABLE()

SplitPanel::SplitPanel(wxWindow* parent, wxWindowID id):
	wxPanel{parent, id},
	m_pSplitFilenameTextCtrl{nullptr},
	m_pSplitXTextCtrl{nullptr},
	m_pSplitYTextCtrl{nullptr},
	m_pSplitWidthTextCtrl{nullptr},
	m_pSplitHeightTextCtrl{nullptr},
	m_SplitX{0},
	m_SplitY{0},
	m_SplitHeight{0},
	m_SplitWidth{0}
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(new wxStaticText(this, -1, "File:"), 0, wxALL | wxALIGN_CENTER, 2);
	m_pSplitFilenameTextCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize{ 100, -1 }, 0);
	sizer->Add(m_pSplitFilenameTextCtrl, 0, wxALL | wxEXPAND, 2);

	sizer->Add(new wxStaticText(this, -1, "X:"), 0, wxALL | wxALIGN_CENTER, 2);
	m_pSplitXTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
	sizer->Add(m_pSplitXTextCtrl, 0, wxALL, 2);

	sizer->Add(new wxStaticText(this, -1, "Y:"), 0, wxALL | wxALIGN_CENTER, 2);
	m_pSplitYTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
	sizer->Add(m_pSplitYTextCtrl, 0, wxALL, 2);

	sizer->Add(new wxStaticText(this, -1, "Width:"), 0, wxALL | wxALIGN_CENTER, 2);
	m_pSplitWidthTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
	sizer->Add(m_pSplitWidthTextCtrl, 0, wxALL, 2);

	sizer->Add(new wxStaticText(this, -1, "Height:"), 0, wxALL | wxALIGN_CENTER, 2);
	m_pSplitHeightTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
	sizer->Add(m_pSplitHeightTextCtrl, 0, wxALL, 2);

	sizer->Add(new wxButton(this, ID_BUTTON_SPLIT_CREATE_TEXTURE, "...", wxDefaultPosition, wxSize{ 20,-1 }), 0, wxALL, 2);
	sizer->Add(new wxButton(this, wxID_ANY, "Remove", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT), 0, wxALL, 2);

	SetSizer(sizer);
}

void SplitPanel::OnCreateNewTexture(wxCommandEvent& event)
{
	wxFileDialog
		saveFileDialog(this, _("Save Image file"), "", "",
			"Image files (*.png;*.jpg)|*.png;*.jpg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	m_pSplitFilenameTextCtrl->SetValue(saveFileDialog.GetPath());
}

ImageToolSplitPage::ImageToolSplitPage(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
	wxScrolledWindow(parent, id, pos, size, style),
	m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) }
{
	m_pBoxSizer = new wxBoxSizer(wxVERTICAL);

	m_pBoxSizer->Add(CreateHeader(), 1, wxALL | wxEXPAND, 2);

	SplitPanel* b = new SplitPanel(this, wxID_ANY);
	m_Images.push_back(b);
	m_pBoxSizer->Add(b, 0, wxALL, 3);

	SetSizer(m_pBoxSizer);

	// this part makes the scrollbars show up
	FitInside(); // ask the sizer about the needed size
	SetScrollRate(5, 5);
}

wxBoxSizer* ImageToolSplitPage::CreateHeader()
{
	wxBoxSizer* pHorizontalSizer = new wxBoxSizer{ wxHORIZONTAL };
	pHorizontalSizer->Add(new wxButton(this, ID_BUTTON_SPLIT, "Split"), 0, wxALL | wxALIGN_CENTER, 2);
	pHorizontalSizer->Add(new wxButton(this, ID_BUTTON_ADD_NEW_IMAGE, "Add new image"), 0, wxALL | wxALIGN_CENTER, 2);
	pHorizontalSizer->Add(new wxButton(this, ID_BUTTON_AUTOSPLIT, "Autosplit image"), 0, wxALL | wxALIGN_CENTER, 2);
	pHorizontalSizer->Add(new wxStaticText(this, -1, "Width:"), 0, wxALL | wxALIGN_CENTER, 2);
	m_pSplitWidthTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
	pHorizontalSizer->Add(m_pSplitWidthTextCtrl, 0, wxALL | wxALIGN_CENTER, 2);

	pHorizontalSizer->Add(new wxStaticText(this, -1, "Height:"), 0, wxALL | wxALIGN_CENTER, 2);
	m_pSplitHeightTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 50, -1 }, 0);
	pHorizontalSizer->Add(m_pSplitHeightTextCtrl, 0, wxALL | wxALIGN_CENTER, 2);
	return pHorizontalSizer;
}

void ImageToolSplitPage::OnSplit(wxCommandEvent& event)
{
	std::vector<TSplitImage> textures;

	TSplitImage tempTexture;

	for (SplitPanel* pCompImage : m_Images)
	{
		tempTexture.m_File = pCompImage->m_pSplitFilenameTextCtrl->GetValue();
		tempTexture.m_Rect.x = wxAtoi(pCompImage->m_pSplitXTextCtrl->GetValue());
		tempTexture.m_Rect.y = wxAtoi(pCompImage->m_pSplitYTextCtrl->GetValue());
		tempTexture.m_Rect.SetWidth(wxAtoi(pCompImage->m_pSplitWidthTextCtrl->GetValue()));
		tempTexture.m_Rect.SetHeight(wxAtoi(pCompImage->m_pSplitHeightTextCtrl->GetValue()));
		textures.push_back(tempTexture);
	}

	m_pMainFrame->GetWorldCanvas()->SplitImage(textures);

	m_pMainFrame->UpdateView();
}

void ImageToolSplitPage::OnAutoSplit(wxCommandEvent& event)
{
	if (m_pMainFrame->GetWorldCanvas() == nullptr) return;

	wxSize imgSize = m_pMainFrame->GetWorldCanvas()->ImageSize();
	wxFileName filename = m_pMainFrame->GetWorldCanvas()->getImage()->getFileName();
	int width = wxAtoi(m_pSplitWidthTextCtrl->GetValue());
	int height = wxAtoi(m_pSplitHeightTextCtrl->GetValue());

	if (width > 0 && height > 0)
	{
		m_pBoxSizer->Clear(true);
		m_Images.clear();

		m_pBoxSizer->Add(CreateHeader(), 1, wxALL | wxEXPAND, 2);

		SetSizer(m_pBoxSizer);

		int columns = imgSize.x / width;
		if ((columns * width) < imgSize.x)
			columns++;
		int rows = imgSize.y / height;
		if ((rows * height) < imgSize.y)
			rows++;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				int w = width;
				int h = height;

				if (((j+1) * width) > imgSize.x)
				{
					w = imgSize.x - (j * width);
				}

				if (((i+1) * height) > imgSize.y)
				{
					h = imgSize.y - (i * height);
				}

				// We split the texture into slices.
				SplitPanel* p = new SplitPanel(this, wxID_ANY);
				wxString path, name, extension;
				wxFileName::SplitPath(filename.GetFullPath(), &path, &name, &extension);
				wxString slice = path + wxFileName::GetPathSeparator() + name + "_" + wxString::FromDouble(i) + "_" + wxString::FromDouble(j) + "." + extension;

				p->m_pSplitFilenameTextCtrl->SetValue(slice);
				p->m_pSplitXTextCtrl->SetValue(wxString::FromDouble(j * width));
				p->m_pSplitYTextCtrl->SetValue(wxString::FromDouble(i * height));
				p->m_pSplitWidthTextCtrl->SetValue(wxString::FromDouble(w));
				p->m_pSplitHeightTextCtrl->SetValue(wxString::FromDouble(h));
				m_Images.push_back(p);
				m_pBoxSizer->Add(p, 0, wxALL, 3);
			}
		}

		// this part makes the scrollbars show up
		FitInside(); // ask the sizer about the needed size
		SetScrollRate(5, 5);
	}
}

void ImageToolSplitPage::OnNewPanelBtn(wxCommandEvent& event)
{
	SplitPanel* b = new SplitPanel(this, wxID_ANY);
	m_Images.push_back(b);
	m_pBoxSizer->Add(b, 0, wxALL, 3);
	//SetSizer(pSizer);

	FitInside();
	//SetScrollRate(5, 5);
}
