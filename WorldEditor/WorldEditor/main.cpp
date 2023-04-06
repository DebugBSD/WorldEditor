
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

    // Se comentan las dos siguientes llamadas a la API de ImageMagick porque cuando 
    // se cierra el programa da una excepcion y no tengo claro todavia el por que.
    // El caso es que me molesta para editar las texturas del nivel que estoy 
    // haciendo asi que ya lo mirare con mas calma cuando tenga mas tiempo.
    //MagickCoreTerminus();

    //MagickWandTerminus();

    return true;
}

