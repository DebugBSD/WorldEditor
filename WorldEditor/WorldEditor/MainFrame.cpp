#include "stdafx.h"
#include "icons/icon.xpm"
#include "MainFrame.h"
#include "NewImageDlg.h"
#include "ImageToolResizePage.h"
#include "ImageToolRotatePage.h"
#include "ImageToolScalePage.h"
#include "ImageToolCropPage.h"
#include "ImageToolTrimPage.h"
#include "ImageToolCompositePage.h"
#include "ImageToolShavePage.h"
#include "ImageToolFlipPage.h"
#include "ImageToolSplitPage.h"
#include "SceneManager.h"
#include "Logger.h"
#include "SFML/Graphics.hpp"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_DIRCTRL_FILEACTIVATED(wxID_ANY, MainFrame::SelectedFile)
EVT_SIZE(MainFrame::OnSize)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_MENU(ID_New, MainFrame::OnNewTexture)
EVT_MENU(ID_ZoomIn, MainFrame::OnZoomIn)
EVT_MENU(ID_ZoomOut, MainFrame::OnZoomOut)
wxEND_EVENT_TABLE()

MainFrame::MainFrame():
	wxFrame(NULL, wxID_ANY, "WorldEditor", wxPoint{0,0}, wxSize(1600, 960)),
	m_pWorldCanvasNotebook{nullptr},
	m_pProperties{nullptr},
	m_pDirCtrl{nullptr},
	m_pExceptionInfo{nullptr},
	m_pImageToolResize{nullptr},
	m_pSceneManager{nullptr},
	m_pImageToolFlip{nullptr}
{
	m_pExceptionInfo = AcquireExceptionInfo();

	m_mgr.SetManagedWindow(this);

	// set frame icon
	SetIcon(wxIcon(icon_xpm));
	
	SetMenuBar(CreateMenuBar());

	CreateStatusBar();
	GetStatusBar()->SetStatusText(_("Ready"));

	// Directory control
	m_pDirCtrl = new wxGenericDirCtrl(this, wxID_ANY, "C:\\Users\\debugg\\My Projects\\Videojuegos\\Heroes of Magic Worlds\\Game\\Debug\\Resources\\Levels\\Textures", wxDefaultPosition, wxSize{ 500, 500 }, 128, "Image Files|*.png;*.jpg;*.jpeg");
	m_mgr.AddPane(m_pDirCtrl);

	// Notebook to render the canvas for every texture
	m_pWorldCanvasNotebook = new wxWorldCanvasNotebook(this, wxID_ANY, wxDefaultPosition, wxSize{ 1024, 720 });
	m_mgr.AddPane(m_pWorldCanvasNotebook, wxAuiPaneInfo().Name("WorldCanvasNotebook").
		CenterPane().PaneBorder(false));

	// Properties window
	m_pProperties = new Properties(this);
	m_mgr.AddPane(m_pProperties, wxAuiPaneInfo().Name("Properties").Caption("Properties").Fixed().
		Right());

	// Image tool resize
	m_pImageToolResize = new ImageToolResizePage(this);
	m_mgr.AddPane(m_pImageToolResize, wxAuiPaneInfo().Name("Resize").Caption("Resize").Fixed().
		Right());

	m_pImageToolRotate = new ImageToolRotatePage(this);
	m_mgr.AddPane(m_pImageToolRotate, wxAuiPaneInfo().Name("Rotate").Caption("Rotate").Fixed().
		Right());

	m_pImageToolScale = new ImageToolScalePage(this);
	m_mgr.AddPane(m_pImageToolScale, wxAuiPaneInfo().Name("Scale").Caption("Scale").Fixed().
		Right());

	m_pImageToolCrop = new ImageToolCropPage(this);
	m_mgr.AddPane(m_pImageToolCrop, wxAuiPaneInfo().Name("Crop").Caption("Crop").Fixed().
		Right());

	m_pImageToolTrim = new ImageToolTrimPage(this);
	m_mgr.AddPane(m_pImageToolTrim, wxAuiPaneInfo().Name("Trim").Caption("Trim").Fixed().
		Right());

	m_pImageToolComposite = new ImageToolCompositePage(this);
	m_mgr.AddPane(m_pImageToolComposite, wxAuiPaneInfo().Name("Composite").Caption("Composite").
		Right());

	m_pImageToolSplit = new ImageToolSplitPage(this);
	m_mgr.AddPane(m_pImageToolSplit, wxAuiPaneInfo().Name("Split").Caption("Split").
		Right());

	m_pImageToolShave = new ImageToolShavePage(this);
	m_mgr.AddPane(m_pImageToolShave, wxAuiPaneInfo().Name("Shave").Caption("Shave").Fixed().
		Right());

	m_pImageToolFlip = new ImageToolFlipPage(this);
	m_mgr.AddPane(m_pImageToolFlip, wxAuiPaneInfo().Name("Flip").Caption("Flip").Fixed().
		Right());

	m_pSceneManager = new SceneManager(this);
	m_mgr.AddPane(m_pSceneManager, wxAuiPaneInfo().Name("Scene Manager").Caption("Scene Manager").
		Right());

	m_pLogger = new Logger(this);
	m_mgr.AddPane(m_pLogger, wxAuiPaneInfo().Name("Logger").Caption("Logger").MinSize(-1,200).
		Left());

	// Disable views so user can't interact with them when there is no texture
	DisableViews();

	m_mgr.Update();

	wxLogWarning("Epa!");
}

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
	wxFrame(parent, id, title, pos, size, style)
{
}

MainFrame::~MainFrame()
{
	m_pExceptionInfo = DestroyExceptionInfo(m_pExceptionInfo);

	if (m_pWorldCanvasNotebook)
	{
		delete m_pWorldCanvasNotebook;
		m_pWorldCanvasNotebook = nullptr;
	}
}

wxAuiDockArt* MainFrame::GetDockArt()
{
	return nullptr;
}

void MainFrame::Update()
{
}

void MainFrame::OnNewTexture(wxCommandEvent& event)
{
	NewImageDlg newImage;

	if (newImage.ShowModal() == wxID_OK)
	{
		wxSize size = newImage.GetSizeOfCanvas();

		m_pWorldCanvasNotebook->NewCanvas(size);

		EnableViews();
	}
}

void MainFrame::OnSize(wxSizeEvent& event)
{
	Refresh();
}

void MainFrame::UpdateView()
{
	m_pImageToolResize->UpdateView();
}

void MainFrame::EnableViews()
{
	m_pProperties->Enable();
	m_pImageToolResize->Enable();
	m_pImageToolRotate->Enable();
	m_pImageToolScale->Enable();
	m_pImageToolCrop->Enable();
	m_pImageToolTrim->Enable();
	m_pImageToolComposite->Enable();
	m_pImageToolShave->Enable();
}

void MainFrame::DisableViews()
{
	m_pProperties->Disable();
	m_pImageToolResize->Disable();
	m_pImageToolRotate->Disable();
	m_pImageToolScale->Disable();
	m_pImageToolCrop->Disable();
	m_pImageToolTrim->Disable();
	m_pImageToolComposite->Disable();
	m_pImageToolShave->Disable();
}

wxMenuBar* MainFrame::CreateMenuBar()
{
	// Menus
	wxMenuBar* mb = new wxMenuBar{};

	wxMenu* fileMenu = new wxMenu();
	fileMenu->Append(ID_New, "New Texture", "Create a new empty texture");
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
	tb3->SetToolBitmapSize(FromDIP(wxSize(16, 16)));
	tb3->AddTool(ID_ZoomIn, "Zoom In", wxArtProvider::GetBitmap(wxART_PLUS));
	tb3->AddTool(ID_ZoomOut, "Zoom Out", wxArtProvider::GetBitmap(wxART_MINUS));

	m_mgr.AddPane(tb2, wxAuiPaneInfo().
		Name("tb2").Caption("File Toolbar").
		ToolbarPane().Top().Row(1));

	m_mgr.AddPane(tb3, wxAuiPaneInfo().
		Name("tb3").Caption("Zoom Toolbar").
		ToolbarPane().Top().Row(1));

	m_mgr.AddPane(CreateImageToolsTB(), wxAuiPaneInfo().
		Name("imageTools").Caption("Image Tools Toolbar").
		ToolbarPane().Top().Row(1));
		
	mb->Append(fileMenu, _("&File"));
	mb->Append(editMenu, _("&Edit"));
	mb->Append(viewMenu, _("&View"));
	mb->Append(imageMenu, _("&Image"));
	mb->Append(optionsMenu, _("&Options"));
	mb->Append(helpMenu, _("&Help"));

	return mb;
}

wxAuiToolBar* MainFrame::CreateImageToolsTB()
{
	wxAuiToolBar* imageToolsToolBar = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	imageToolsToolBar->SetToolBitmapSize(FromDIP(wxSize(16, 16)));
	
	struct imageTools {
		int id;
		wxString caption;
		const char *filename;
		int scaleWidth;
		int scaleHeight;
	} imgTools[] =
	{
		{ wxID_ANY, "Crop", "icons/crop.png", 16, 16 },
		{ wxID_ANY, "Resize", "icons/resize.png", 16, 16 },
		{ wxID_ANY, "Rotate", "icons/rotate-right.png", 16, 16 },
		{ wxID_ANY, "Scale", "icons/scale.png", 16, 16 },
		{ wxID_ANY, "Shave", "icons/shave.png", 16, 16 },
		{ wxID_ANY, "Trim", "icons/trim.png", 16, 16 },
		{ wxID_ANY, "", NULL, 0, 0}
	};

	for(int i = 0; imgTools[i].filename != NULL; i++)
	{
		wxImage img{ imgTools[i].filename };
		img = img.Scale(imgTools[i].scaleWidth, imgTools[i].scaleHeight);
		wxBitmap bmp(img, wxBITMAP_TYPE_PNG);
		imageToolsToolBar->AddTool(imgTools[i].id, imgTools[i].caption, bmp);
	}

	return imageToolsToolBar;
}

void MainFrame::SelectedFile(wxTreeEvent& e)
{

	wxString filename = m_pDirCtrl->GetPath(e.GetItem());
	m_pWorldCanvasNotebook->OpenCanvas(filename);
	m_pProperties->SetFileName(filename);
	GetStatusBar()->SetStatusText(filename);

	EnableViews();
}

void MainFrame::OnExit(wxCommandEvent& evt)
{
	Close(true);
}

void MainFrame::OnZoomIn(wxCommandEvent& evt)
{
	WorldCanvas* canvas = (WorldCanvas*)m_pWorldCanvasNotebook->GetCurrentPage();
	if(canvas)
		canvas->ScaleImage(1.5, 1.5);
}

void MainFrame::OnZoomOut(wxCommandEvent& evt)
{
	WorldCanvas* canvas = (WorldCanvas*)m_pWorldCanvasNotebook->GetCurrentPage();
	if(canvas)
		canvas->ScaleImage(0.5, 0.5);
}
