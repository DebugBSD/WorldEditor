#include "stdafx.h"
#include "MainFrame.h"
#include "SFML/Graphics.hpp"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_DIRCTRL_FILEACTIVATED(wxID_ANY, MainFrame::SelectedFile)
EVT_SIZE(MainFrame::OnSize)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
wxEND_EVENT_TABLE()

MainFrame::MainFrame():
	wxFrame(NULL, wxID_ANY, "WorldEditor", wxPoint{0,0}, wxSize(1600, 960)),
	m_pWorldCanvas{nullptr},
	m_pProperties{nullptr},
	m_pDirCtrl{nullptr},
	m_pExceptionInfo{nullptr}
{

	m_pExceptionInfo = AcquireExceptionInfo();

	m_mgr.SetManagedWindow(this);

	// set frame icon
	//SetIcon(wxIcon(sample_xpm));
	
	SetMenuBar(CreateMenuBar());

	CreateStatusBar();
	GetStatusBar()->SetStatusText(_("Ready"));

	// Directory control
	m_pDirCtrl = new wxGenericDirCtrl(this, wxID_ANY, "C:\\Users\\debugg\\My Projects\\Videojuegos\\Heroes of Magic Worlds", wxDefaultPosition, wxSize{ 500, 500 }, 128, "Image Files|*.png;*.jpg;*.jpeg");
	m_mgr.AddPane(m_pDirCtrl);

	// Canvas to render textures
	m_pWorldCanvas = new WorldCanvas(this, wxID_ANY, wxDefaultPosition, wxSize{ 1024, 720 });
	m_mgr.AddPane(m_pWorldCanvas, wxAuiPaneInfo().Name("WorldCanvas").
		CenterPane().PaneBorder(false));

	// Properties window
	m_pProperties = new Properties(this, wxID_ANY, wxDefaultPosition, wxSize{ 500, 500 });
	m_mgr.AddPane(m_pProperties, wxAuiPaneInfo().Name("Properties").Caption("Properties").
		Right());


	m_mgr.Update();
}

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
	wxFrame(parent, id, title, pos, size, style)
{
}

MainFrame::~MainFrame()
{
	m_pExceptionInfo = DestroyExceptionInfo(m_pExceptionInfo);

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

wxMenuBar* MainFrame::CreateMenuBar()
{
	// Menus
	wxMenuBar* mb = new wxMenuBar{};

	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(wxID_EXIT);
	wxMenu* editMenu = new wxMenu();
	wxMenu* viewMenu = new wxMenu();
	wxMenu* imageMenu = new wxMenu();
	wxMenu* optionsMenu = new wxMenu();
	wxMenu* helpMenu = new wxMenu();

	// Toolbars
	wxAuiToolBar* tb2 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	tb2->SetToolBitmapSize(FromDIP(wxSize(16, 16)));
	tb2->AddTool(ID_New, "New", wxArtProvider::GetBitmap(wxART_NEW));
	tb2->AddTool(ID_Open, "Open", wxArtProvider::GetBitmap(wxART_FILE_OPEN));
	tb2->AddTool(ID_Save, "Save", wxArtProvider::GetBitmap(wxART_FILE_SAVE));
	tb2->AddTool(ID_SaveAs, "Save As", wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS));
	tb2->AddSeparator();
	tb2->AddTool(ID_EditUndo, "Undo", wxArtProvider::GetBitmap(wxART_UNDO));
	tb2->AddTool(ID_EditRedo, "Redp", wxArtProvider::GetBitmap(wxART_REDO));
	tb2->AddSeparator();
	tb2->AddTool(ID_GoBack, "Go Back", wxArtProvider::GetBitmap(wxART_GO_BACK));
	tb2->AddTool(ID_GoForward, "Go Forward", wxArtProvider::GetBitmap(wxART_GO_FORWARD));
	tb2->AddSeparator();
	tb2->AddTool(ID_EditCopy, "Copy", wxArtProvider::GetBitmap(wxART_COPY));
	tb2->AddTool(ID_EditCut, "Cut", wxArtProvider::GetBitmap(wxART_CUT));
	tb2->AddTool(ID_EditPaste, "Paste", wxArtProvider::GetBitmap(wxART_PASTE));
	tb2->Realize();

	wxAuiToolBar* tb3 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	tb3->AddTool(ID_ZoomIn, "Zoom In", wxArtProvider::GetBitmap(wxART_PLUS));
	tb3->AddTool(ID_ZoomOut, "Zoom Out", wxArtProvider::GetBitmap(wxART_MINUS));

	m_mgr.AddPane(tb2, wxAuiPaneInfo().
		Name("tb2").Caption("File Toolbar").
		ToolbarPane().Top().Row(1));

	m_mgr.AddPane(tb3, wxAuiPaneInfo().
		Name("tb3").Caption("Zoom Toolbar").
		ToolbarPane().Top().Row(1));

	mb->Append(fileMenu, _("&File"));
	mb->Append(editMenu, _("&Edit"));
	mb->Append(viewMenu, _("&View"));
	mb->Append(imageMenu, _("&Image"));
	mb->Append(optionsMenu, _("&Options"));
	mb->Append(helpMenu, _("&Help"));

	return mb;
}

void MainFrame::SelectedFile(wxTreeEvent& e)
{
	
	wxString filename = m_pDirCtrl->GetPath(e.GetItem());
	m_pWorldCanvas->OpenTexture(filename);
	m_pProperties->SetFileName(filename);
	GetStatusBar()->SetStatusText(filename);
}

void MainFrame::OnExit(wxCommandEvent& evt)
{
	Close(true);
}
