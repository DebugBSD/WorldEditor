#include "stdafx.h"
#include "wxSFMLCanvas.h"

wxBEGIN_EVENT_TABLE(wxSFMLCanvas, wxControl)
	EVT_IDLE(wxSFMLCanvas::OnIdle)
	EVT_PAINT(wxSFMLCanvas::OnPaint)
	EVT_SIZE(wxSFMLCanvas::OnSize)
wxEND_EVENT_TABLE()

wxSFMLCanvas::wxSFMLCanvas(wxWindow* pParent, wxWindowID Id, const wxPoint& pos, const wxSize& Size, long style):
	wxControl(pParent, Id, pos, Size, style)
{
	sf::RenderWindow::create(GetHandle());
}

wxSFMLCanvas::~wxSFMLCanvas()
{
}

void wxSFMLCanvas::OnUpdate()
{
}

void wxSFMLCanvas::OnIdle(wxIdleEvent& evt)
{
	// Send a paint message when the control is idle, to ensure maximum framerate.
	Refresh(false);
}

void wxSFMLCanvas::OnPaint(wxPaintEvent& evt)
{
	// Prepare the control to be painted
	wxPaintDC dc(this);

	// Let the derived class do its specific stuff
	OnUpdate();

	// Display on screen
	display();
}

void wxSFMLCanvas::OnSize(wxSizeEvent& evt)
{
	Refresh(false);

	sf::RenderWindow::create(GetHandle());
}

void wxSFMLCanvas::OnEraseBackground(wxEraseEvent& evt)
{
}
