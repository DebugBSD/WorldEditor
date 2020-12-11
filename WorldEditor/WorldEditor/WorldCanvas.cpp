#include "stdafx.h"
#include "MainFrame.h"
#include "WorldCanvas.h"
#include "weImage.h"

#include <vector>

wxBEGIN_EVENT_TABLE(WorldCanvas, wxScrolledCanvas)
// some useful events
/*
 EVT_MOTION(wxImagePanel::mouseMoved)
 EVT_LEFT_DOWN(wxImagePanel::mouseDown)
 EVT_LEFT_UP(wxImagePanel::mouseReleased)
 EVT_RIGHT_DOWN(wxImagePanel::rightClick)
 EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
 EVT_KEY_DOWN(wxImagePanel::keyPressed)
 EVT_KEY_UP(wxImagePanel::keyReleased)
 EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
 */

 // catch paint events
	EVT_PAINT(WorldCanvas::paintEvent)
	EVT_IDLE(WorldCanvas::OnIdle)
	EVT_SIZE(WorldCanvas::OnSize)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(wxWorldCanvasNotebook, wxAuiNotebook)
	EVT_AUINOTEBOOK_PAGE_CLOSE(wxID_ANY, wxWorldCanvasNotebook::OnCloseTab)
	EVT_AUINOTEBOOK_PAGE_CLOSED(wxID_ANY, wxWorldCanvasNotebook::OnClosedTab)
	EVT_AUINOTEBOOK_PAGE_CHANGED(wxID_ANY, wxWorldCanvasNotebook::OnTabChanged)
wxEND_EVENT_TABLE()

WorldCanvas::WorldCanvas(wxWindow* pParent, wxWindowID id, const wxPoint& Position, const wxSize& size, long style) :
	wxScrolledCanvas(pParent, wxID_ANY),
	m_Width{-1},
	m_Height{-1},
	m_ClearBackground{ true },
	m_DrawPositionX{0},
	m_DrawPositionY{0},
	m_pImage{NULL},
	m_pWEImage{NULL}
{

}

WorldCanvas::~WorldCanvas()
{
	free();
}

void WorldCanvas::CreateTexture(const wxSize& size)
{
	m_pWEImage = new weImage();
	m_pWEImage->init(size);
	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	SetScrollbars(1, 1, m_pWEImage->getSize().x, m_pWEImage->getSize().y, 0, 0);
	UpdateBitmap();
	m_ClearBackground = true;
}

bool WorldCanvas::OpenTexture(const wxString& pathToTexture)
{
	free();

	bool success = true;
	m_pWEImage = new weImage();
	m_pWEImage->init(pathToTexture.ToStdString());
	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	if (success)
	{

		/* init scrolled area size, scrolling speed, etc. */
		SetScrollbars(1, 1, m_pWEImage->getSize().x, m_pWEImage->getSize().y, 0, 0);
		UpdateBitmap();
		m_ClearBackground = true;
	}
	else
	{
		// Log the error...
	}
	return success;
}

wxSize WorldCanvas::ImageSize()
{
	wxSize size{ -1, -1 };
	if (m_pWEImage != NULL)
	{
		size = m_pWEImage->getSize();
	}
	return size;
}

void WorldCanvas::SaveImage()
{
	if (m_pWEImage != NULL)
	{
		m_pWEImage->save();
	}
}

void WorldCanvas::SaveImageAs(const wxString& pathToTexture)
{
	if (m_pWEImage != NULL)
	{
		m_pWEImage->saveAs(pathToTexture.ToStdString());
	}
}

void WorldCanvas::ShaveImage(size_t width, size_t height)
{
	delete m_pImage;
	m_pWEImage->shave(width, height);
	m_pWEImage->update();

	// NOTE: Debug this algorithm. When the image is rotated the size of the used memory grows exponentially.
	//sizes.push_back(m_pWEImage->getSize()); 

	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	UpdateBitmap();
	m_ClearBackground = true;
}

void WorldCanvas::CropImage(double x, double y, double width, double height)
{
	delete m_pImage;
	m_pWEImage->crop(x,y,width,height);
	m_pWEImage->update();

	// NOTE: Debug this algorithm. When the image is rotated the size of the used memory grows exponentially.
	//sizes.push_back(m_pWEImage->getSize()); 

	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	UpdateBitmap();
	m_ClearBackground = true;
}

void WorldCanvas::ScaleImage(double x, double y)
{
	//static std::vector<wxSize> sizes;
	delete m_pImage;
	m_pWEImage->scale(x,y);
	m_pWEImage->update();

	// NOTE: Debug this algorithm. When the image is rotated the size of the used memory grows exponentially.
	//sizes.push_back(m_pWEImage->getSize()); 

	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	UpdateBitmap();
	m_ClearBackground = true;
}

void WorldCanvas::RotateImage(float degrees)
{
	//static std::vector<wxSize> sizes;
	delete m_pImage;
	m_pWEImage->rotate(degrees);
	m_pWEImage->update();

	// NOTE: Debug this algorithm. When the image is rotated the size of the used memory grows exponentially.
	//sizes.push_back(m_pWEImage->getSize()); 

	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	UpdateBitmap();
	m_ClearBackground = true;
}

void WorldCanvas::ResizeImage(size_t width, size_t height)
{
	//static std::vector<wxSize> sizes;
	delete m_pImage;
	m_pWEImage->resize(width, height);
	m_pWEImage->update();

	// NOTE: Debug this algorithm. When the image is rotated the size of the used memory grows exponentially.
	//sizes.push_back(m_pWEImage->getSize()); 

	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	UpdateBitmap();
	m_ClearBackground = true;
}

void WorldCanvas::TrimImage(double fuzz)
{
	delete m_pImage;
	m_pWEImage->trim(fuzz);
	m_pWEImage->update();

	// NOTE: Debug this algorithm. When the image is rotated the size of the used memory grows exponentially.
	//sizes.push_back(m_pWEImage->getSize()); 

	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	UpdateBitmap();
	m_ClearBackground = true;
}

void WorldCanvas::SplitImage(const std::vector<TSplitImage>& images)
{
	m_pWEImage->split(images);
}

void WorldCanvas::CompositeImage(const std::vector<TCompositeImage>& images)
{
	delete m_pImage;
	m_pWEImage->composite(images);
	m_pWEImage->update();

	// NOTE: Debug this algorithm. When the image is rotated the size of the used memory grows exponentially.
	//sizes.push_back(m_pWEImage->getSize()); 

	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	UpdateBitmap();
	m_ClearBackground = true;
}

void WorldCanvas::FlipImage(void)
{
	delete m_pImage;
	m_pWEImage->flip();
	m_pWEImage->update();

	m_pImage = new wxImage(m_pWEImage->getSize().x, m_pWEImage->getSize().y, m_pWEImage->getPixels(), m_pWEImage->getAlphaPixels());
	UpdateBitmap();
	m_ClearBackground = true;
}

void WorldCanvas::UpdateBitmap()
{
	int neww, newh;
	GetClientSize(&neww, &newh);

	if (m_pImage->GetWidth() > neww || m_pImage->GetHeight() > newh)
	{
		neww = (m_pImage->GetWidth() > neww) ? neww : m_pImage->GetWidth();
		newh = (m_pImage->GetHeight() > newh) ? newh : m_pImage->GetHeight();

		int vScrollPos = GetScrollPos(wxVERTICAL);
		int hScrollPos = GetScrollPos(wxHORIZONTAL);

		m_Bitmap = wxBitmap(m_pImage->GetSubImage(wxRect{ hScrollPos, vScrollPos, neww, newh }));
		m_DrawPositionX = m_DrawPositionY = 0;

	}
	else
	{
		m_Bitmap = wxBitmap(*m_pImage);
		m_DrawPositionX = neww / 2 - (m_pImage->GetWidth() / 2);
		m_DrawPositionY = neww / 2 - (m_pImage->GetHeight() / 2);
	}
}

void WorldCanvas::UpdateView()
{
	int neww, newh;
	GetClientSize(&neww, &newh);
	if (m_pImage->GetWidth() > neww || m_pImage->GetHeight() > newh)
	{
		neww = (m_pImage->GetWidth() > neww) ? neww : m_pImage->GetWidth();
		newh = (m_pImage->GetHeight() > newh) ? newh : m_pImage->GetHeight();

		int vScrollPos = GetScrollPos(wxVERTICAL);
		int hScrollPos = GetScrollPos(wxHORIZONTAL);

		m_Bitmap = wxBitmap(m_pImage->GetSubImage(wxRect{ hScrollPos, vScrollPos, neww, newh }));
		m_DrawPositionX = m_DrawPositionY = 0;

	}
	else
	{
		m_Bitmap = wxBitmap(*m_pImage);
		m_DrawPositionX = neww / 2 - (m_pImage->GetWidth() / 2);
		m_DrawPositionY = neww / 2 - (m_pImage->GetHeight() / 2);
	}
}

bool WorldCanvas::init()
{
	return false;
}

void WorldCanvas::free()
{

	if (m_pImage != NULL)
	{
		delete m_pImage;
		m_pImage = NULL;
	}

	if (m_pWEImage != NULL)
	{
		delete m_pWEImage;
		m_pWEImage = NULL;
	}

}

bool WorldCanvas::Destroy()
{
	free();

	return true;
}

void WorldCanvas::OnIdle(wxIdleEvent& event)
{
	paintNow();
	event.RequestMore();

}

void WorldCanvas::paintEvent(wxPaintEvent& event)
{
	wxPaintDC dc{ this };
	render(dc);
}

void WorldCanvas::paintNow()
{
	wxClientDC dc{ this };

	render(dc);
}

void WorldCanvas::OnSize(wxSizeEvent& event)
{
	Refresh();

	if (m_pImage && m_pImage->IsOk())
	{
		UpdateBitmap();
	}

	event.Skip();
}

void WorldCanvas::render(wxDC& dc)
{
	if (!m_pImage || !m_pImage->IsOk()) return;

	if (m_ClearBackground)
	{
		dc.Clear();
		m_ClearBackground = false;
	}

	UpdateView();

	dc.DrawBitmap(m_Bitmap, m_DrawPositionX, m_DrawPositionY, true);

}

wxWorldCanvasNotebook::wxWorldCanvasNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
	wxAuiNotebook(parent, id, pos, size, style),
	m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) },
	m_pCurrentCanvas{nullptr}
{
}

wxWorldCanvasNotebook::~wxWorldCanvasNotebook()
{
	int stop = 1;
}

bool wxWorldCanvasNotebook::OpenCanvas(const wxString& texture)
{
	WorldCanvas* canvas = new WorldCanvas{ this, wxID_ANY, wxDefaultPosition, wxDefaultSize };
	canvas->OpenTexture(texture);

	wxFileName filename{ texture };

	AddPage(canvas, filename.GetName(), true);

	return false;
}

bool wxWorldCanvasNotebook::NewCanvas(const wxSize& size)
{
	WorldCanvas* canvas = new WorldCanvas{ this, wxID_ANY, wxDefaultPosition, wxDefaultSize };
	canvas->CreateTexture(size);

	AddPage(canvas, "New", true);

	return false;
}

// Called when the tab is about to be closed.
void wxWorldCanvasNotebook::OnCloseTab(wxAuiNotebookEvent& event)
{
	m_pCurrentCanvas = (WorldCanvas *)GetCurrentPage();
}

// Called after the tab has been closed.
void wxWorldCanvasNotebook::OnClosedTab(wxAuiNotebookEvent& event)
{
	if (m_pCurrentCanvas != nullptr)
	{
		m_pCurrentCanvas->Destroy();
		m_pCurrentCanvas = nullptr;
	}

	if (GetPageCount() == 0)
	{
		m_pMainFrame->DisableViews();
	}
}

void wxWorldCanvasNotebook::OnTabChanged(wxAuiNotebookEvent& event)
{
	WorldCanvas* canvas = (WorldCanvas*)GetCurrentPage();

	m_pMainFrame->GetStatusBar()->SetStatusText(canvas->getImage()->getFileName());
}
