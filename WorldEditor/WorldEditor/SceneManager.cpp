#include "stdafx.h"
#include "SceneManager.h"

wxBEGIN_EVENT_TABLE(SceneManager, wxPanel)
EVT_TREELIST_SELECTION_CHANGED(ID_TREECTRL,SceneManager::OnSelectionChanged)
wxEND_EVENT_TABLE()

SceneManager::SceneManager(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style) :
	wxPanel(parent, id, pos, size, style),
	m_pTreeCtrl{nullptr}
{
	wxBoxSizer* boxSizer = new wxBoxSizer{ wxVERTICAL };

	m_pTreeCtrl = new wxTreeListCtrl(this, ID_TREECTRL, wxDefaultPosition, wxDefaultSize, wxTL_MULTIPLE | wxTL_USER_3STATE);
	boxSizer->Add(m_pTreeCtrl, 1, wxEXPAND | wxALL);

	SetSizerAndFit(boxSizer);
}

void SceneManager::OnSelectionChanged(wxTreeListEvent& event)
{
}
