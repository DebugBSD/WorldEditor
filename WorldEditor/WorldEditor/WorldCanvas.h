#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>

/*
 * - See: https://wiki.wxwidgets.org/An_image_panel 
 */
class WorldCanvas :
    public wxControl
{
public:
    WorldCanvas(wxWindow *pParent, wxWindowID id, const wxPoint &Position, const wxSize &size, long style = 0);

    bool OpenTexture(const wxString &pathToTexture);

private:
    wxImage m_Image;
    wxBitmap m_Bitmap;
    int m_Width;
    int m_Height;
    bool m_ClearBackground;
private:

    void free();

    void OnIdle(wxIdleEvent &event);
    void paintEvent(wxPaintEvent &event);
    void paintNow();
    void OnSize(wxSizeEvent &event);
    void render(wxDC &dc);
    
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    wxDECLARE_EVENT_TABLE();
};

