#pragma once

#include <wx/app.h>
#include <wx/grid.h>
#include <wx/treectrl.h>
#include <wx/spinctrl.h>
#include <wx/artprov.h>
#include <wx/clipbrd.h>
#include <wx/image.h>
#include <wx/colordlg.h>
#include <wx/wxhtml.h>
#include <wx/imaglist.h>
#include <wx/dataobj.h>
#include <wx/dcclient.h>
#include <wx/bmpbuttn.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/msgdlg.h>
#include <wx/textdlg.h>
#include <wx/dirctrl.h>

#include "wx/aui/aui.h"

#include "WorldCanvas.h"

class MainFrame :
    public wxFrame
{
public:
    MainFrame();

    MainFrame(wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);
    ~MainFrame();

    wxAuiDockArt* GetDockArt();
    void Update();

private:

    wxAuiManager m_mgr;
    WorldCanvas* m_pWorldCanvas;
    wxGenericDirCtrl* m_pDirCtrl;

    void SelectedFile(wxTreeEvent &e);

    wxDECLARE_EVENT_TABLE();
};

