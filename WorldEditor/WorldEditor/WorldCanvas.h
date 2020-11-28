#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>

/*
 * - See: https://wiki.wxwidgets.org/An_image_panel 
 * - See ho to use this instead of the actual wxBitmap and wxImage on wxControl: 
 *      - https://docs.wxwidgets.org/trunk/classwx_buffered_paint_d_c.html
 */
class WorldCanvas :
    public wxPanel
{
public:
    WorldCanvas(wxWindow *pParent, wxWindowID id, const wxPoint &Position, const wxSize &size, long style = 0);

    bool OpenTexture(const wxString &pathToTexture);

    void RotateImage(float degrees);

    bool init();
    void free();

private:
    class weImage* m_pWEImage;
    wxImage *m_pImage;
    wxBitmap m_Bitmap;
    int m_Width;
    int m_Height;
    bool m_ClearBackground;
    wxCoord m_DrawPositionX;
    wxCoord m_DrawPositionY;
private:

    void UpdateBitmap();

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

