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
	wxControl(pParent, wxID_ANY),
	m_Width{-1},
	m_Height{-1},
	m_ClearBackground{ true }
{

}

bool WorldCanvas::OpenTexture(const wxString& pathToTexture)
{
	bool res = m_Image.LoadFile(pathToTexture);

	int neww, newh;
	GetClientSize(&neww, &newh);

	if (m_Image.GetWidth() > neww || m_Image.GetHeight() > newh)
		m_Bitmap = wxBitmap(m_Image.Scale(neww, newh));
	else
		m_Bitmap = wxBitmap(m_Image);

	m_ClearBackground = true;

	return res;
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
		int neww, newh;
		GetClientSize(&neww, &newh);

		if (m_Image.GetWidth() > neww || m_Image.GetHeight() > newh)
			m_Bitmap = wxBitmap(m_Image.Scale(neww, newh));
		else
			m_Bitmap = wxBitmap(m_Image);
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

	dc.DrawBitmap(m_Bitmap, 0,0, false);

}
