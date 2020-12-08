#pragma once
#include <wx/panel.h>
#include <wx/treelist.h>
#include <wx/sizer.h>

class SceneManager :
    public wxPanel
{
public:
    enum
    {
        ID_TREECTRL = wxID_HIGHEST + 1,
    };

    SceneManager(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

private:
    class MainFrame* m_pMainFrame;

    class wxTreeListCtrl* m_pTreeCtrl;

    void OnSelectionChanged(wxTreeListEvent &event);

    wxDECLARE_EVENT_TABLE();

};

