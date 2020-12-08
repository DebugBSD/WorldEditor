#include "stdafx.h"
#include "MainFrame.h"
#include "Logger.h"

#include <wx/textctrl.h>
#include <wx/log.h>

/*
 * See how to handle all errors reported by ImageMagick:
 *	- See ImageMagick errors: https://imagemagick.org/script/exception.php and https://imagemagick.org/api/exception.php
 */

Logger::Logger(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
	wxPanel(parent, id, pos, size, style),
	m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) },
	m_pTextCtrlLogger{nullptr},
	m_pLogTextControl{nullptr}
{
	wxBoxSizer* boxSizer = new wxBoxSizer{ wxHORIZONTAL };

	m_pTextCtrlLogger = new wxTextCtrl{ this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE };
	m_pLogTextControl = new wxLogTextCtrl{ m_pTextCtrlLogger };
	wxLog::SetActiveTarget(m_pLogTextControl);

	boxSizer->Add(m_pTextCtrlLogger, 1, wxEXPAND | wxALL);

	SetSizerAndFit(boxSizer);
}
