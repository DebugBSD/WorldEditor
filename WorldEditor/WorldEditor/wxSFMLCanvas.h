#pragma once
#include <wx/wx.h>
#include <SFML/Graphics.hpp>

class wxSFMLCanvas :
    public wxControl,
    public sf::RenderWindow
{
public:
    wxSFMLCanvas(wxWindow* pParent = NULL, wxWindowID Id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& Size = wxDefaultSize, long style = 0);

    virtual ~wxSFMLCanvas();

private:
    DECLARE_EVENT_TABLE();

    virtual void OnUpdate();

    void OnIdle(wxIdleEvent &evt);

    void OnPaint(wxPaintEvent &evt);
    void OnSize(wxSizeEvent& evt);

    void OnEraseBackground(wxEraseEvent &evt);
};

