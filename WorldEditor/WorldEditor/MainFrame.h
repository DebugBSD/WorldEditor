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
#include "Properties.h"

class MainFrame :
    public wxFrame
{
public:
    enum
    {
        ID_New = wxID_HIGHEST + 1,
        ID_Open,
        ID_Save,
        ID_SaveAs,
        ID_Close,
        ID_EditCut,
        ID_EditCopy,
        ID_EditPaste,
        ID_EditDelete,
        ID_EditUndo,
        ID_EditRedo,
        ID_GoBack,
        ID_GoForward,
        ID_ZoomIn,
        ID_ZoomOut
    };

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
    void OnSize(wxSizeEvent &event);

    WorldCanvas* GetWorldCanvas() { return m_pWorldCanvas; }

private:
    wxMenuBar* CreateMenuBar();

    wxAuiManager m_mgr;
    WorldCanvas* m_pWorldCanvas; 
    Properties* m_pProperties;
    wxGenericDirCtrl* m_pDirCtrl;

    void SelectedFile(wxTreeEvent &e);
    void OnExit(wxCommandEvent& evt);

    wxDECLARE_EVENT_TABLE();
};