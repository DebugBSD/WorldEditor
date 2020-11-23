#include "stdafx.h"
#include "MainFrame.h"
#include "SFML/Graphics.hpp"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_DIRCTRL_FILEACTIVATED(wxID_ANY, MainFrame::SelectedFile)
EVT_SIZE(MainFrame::OnSize)
wxEND_EVENT_TABLE()

MainFrame::MainFrame():
	wxFrame(NULL, wxID_ANY, "WorldEditor", wxDefaultPosition, wxSize(1280, 960)),
	m_pWorldCanvas{nullptr},
	m_pDirCtrl{nullptr}
{
	m_mgr.SetManagedWindow(this);

	m_pDirCtrl = new wxGenericDirCtrl(this, wxID_ANY, "C:\\Users\\debugg\\My Projects\\Videojuegos\\Heroes of Magic Worlds", wxDefaultPosition, wxSize{ 500, 500 });
	m_mgr.AddPane(m_pDirCtrl);
	m_pWorldCanvas = new WorldCanvas(this, wxID_ANY, wxDefaultPosition, wxSize{ 1024, 720 });
	m_mgr.AddPane(m_pWorldCanvas, wxAuiPaneInfo().Name("WorldCanvas").
		CenterPane().PaneBorder(false));


	m_mgr.Update();
}

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
	wxFrame(parent, id, title, pos, size, style)
{
}

MainFrame::~MainFrame()
{
	if (m_pWorldCanvas)
	{
		delete m_pWorldCanvas;
		m_pWorldCanvas = nullptr;
	}
}

wxAuiDockArt* MainFrame::GetDockArt()
{
	return nullptr;
}

void MainFrame::Update()
{
}

void MainFrame::OnSize(wxSizeEvent& event)
{
	Refresh();
}

void MainFrame::SelectedFile(wxTreeEvent& e)
{
	
	wxString filename = m_pDirCtrl->GetPath(e.GetItem());
	m_pWorldCanvas->OpenTexture(filename);
}
