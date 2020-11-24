#include "stdafx.h"
#include "WorldCanvas.h"

wxBEGIN_EVENT_TABLE(WorldCanvas, wxPanel)
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

WorldCanvas::WorldCanvas(wxWindow* pParent, wxWindowID id, const wxPoint& Position, const wxSize& size, long style) :
	wxPanel(pParent, wxID_ANY),
	m_Width{-1},
	m_Height{-1},
	m_ClearBackground{ true },
	m_DrawPositionX{0},
	m_DrawPositionY{0}
{

}

bool WorldCanvas::OpenTexture(const wxString& pathToTexture)
{
	m_Image.SetLoadFlags(m_Image.GetLoadFlags() & ~wxImage::Load_Verbose);
	bool success = m_Image.LoadFile(pathToTexture);

	if (success)
	{
		UpdateBitmap();

		m_ClearBackground = true;
	}
	else
	{
		// Log the error...
	}
	return success;
}

void WorldCanvas::RotateImage(float degrees)
{
	double radians = wxDegToRad(degrees);
	m_Image = m_Image.Rotate(radians, wxPoint{m_Image.GetWidth() / 2, m_Image.GetHeight() / 2});
	UpdateBitmap();
	m_ClearBackground = true;
}

void WorldCanvas::UpdateBitmap()
{
	int neww, newh;
	GetClientSize(&neww, &newh);

	if (m_Image.GetWidth() > neww || m_Image.GetHeight() > newh)
	{
		m_Bitmap = wxBitmap(m_Image.Scale(neww, newh));
		m_DrawPositionX = m_DrawPositionY = 0;
	}
	else
	{
		m_Bitmap = wxBitmap(m_Image);
		m_DrawPositionX = neww / 2 - (m_Image.GetWidth() / 2);
		m_DrawPositionY = neww / 2 - (m_Image.GetHeight() / 2);
	}
}

void WorldCanvas::free()
{
	
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

	if (m_Image.IsOk())
	{
		UpdateBitmap();
	}

	event.Skip();
}

void WorldCanvas::render(wxDC& dc)
{
	if (!m_Image.IsOk()) return;

	if (m_ClearBackground)
	{
		dc.Clear();
		m_ClearBackground = false;
	}

	dc.DrawBitmap(m_Bitmap, m_DrawPositionX, m_DrawPositionY, false);

}
