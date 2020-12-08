#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/aui/auibook.h>
#include <wx/filename.h>

#include <vector>

#include "weImage.h"

class WorldCanvas :
    public wxPanel
{
public:
    WorldCanvas(wxWindow *pParent, wxWindowID id, const wxPoint &Position, const wxSize &size, long style = 0);
    ~WorldCanvas();

    void CreateTexture(const wxSize &size);
    bool OpenTexture(const wxString &pathToTexture);
    class weImage* getImage() { return m_pWEImage; }

    wxSize ImageSize();
    void SaveImage();
    void SaveImageAs(const wxString& pathToTexture);
    void ShaveImage(size_t width, size_t height);
    void CropImage(double x, double y, double width, double height);
    void ScaleImage(double x, double y);
    void RotateImage(float degrees);
    void ResizeImage(size_t width, size_t height);
    void TrimImage(double fuzz);
    void CompositeImage(const std::vector<TCompositeImage> &images);

    bool init();
    void free();

    bool Destroy();

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

class wxWorldCanvasNotebook: public wxAuiNotebook
{
public:
    wxWorldCanvasNotebook(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxAUI_NB_DEFAULT_STYLE);
    ~wxWorldCanvasNotebook();

    bool OpenCanvas(const wxString &texture);
    bool NewCanvas(const wxSize &size);

private:
    class MainFrame* m_pMainFrame;
    class WorldCanvas *m_pCurrentCanvas;

private:
    // Events
    void OnCloseTab(wxAuiNotebookEvent& event);
    void OnClosedTab(wxAuiNotebookEvent& event);
    void OnTabChanged(wxAuiNotebookEvent& event);

    wxDECLARE_EVENT_TABLE();

};