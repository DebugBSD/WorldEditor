
#include "stdafx.h"
#include <wx/wxprec.h>
#include <wx/utils.h>

#include "MainFrame.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MagickWandGenesis();
    char** pArgv = (char **)wxApp::argv;
    MagickCoreGenesis(pArgv[0], MagickTrue);

    MainFrame* frame = new MainFrame();
    frame->Show(true);
    return true;
}

int MyApp::OnExit()
{

    MagickCoreTerminus();

    MagickWandTerminus();

    return true;
}

