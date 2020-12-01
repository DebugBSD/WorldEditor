#pragma once
#include <wx/window.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/valnum.h>

class Properties :
    public wxWindow
{
public:
    enum
    {
        ID_BUTTON_SAVE_COPY_AS = wxID_HIGHEST + 1,
        ID_BUTTON_SAVE_CURRENT,
        ID_BUTTON_SHAVE,
        ID_BUTTON_RESIZE_TEXTURE,
        ID_BUTTON_ROTATE,
        ID_BUTTON_SCALE,
        ID_BUTTON_CROP,
        ID_BUTTON_FLIP,
        ID_BUTTON_TRIM,
        ID_BUTTON_COMPOSITE,
        ID_BUTTON_COMPOSITE_FIND_TEXTURE0,
        ID_BUTTON_COMPOSITE_FIND_TEXTURE1,
        ID_BUTTON_COMPOSITE_FIND_TEXTURE2,
        ID_BUTTON_COMPOSITE_FIND_TEXTURE3
    };

    Properties(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = 128);

    void SetFileName(const wxString& fileName);
private:
    wxString m_FileName;
    class MainFrame* m_pMainFrame;

    bool m_FileNameUpdated;

    // Size properties
    unsigned int m_Width;
    unsigned int m_Height;

    // Rotation
    float m_Angle;

    // Scale 
    float m_ScaleWidth;
    float m_ScaleHeight;

    // Crop
    unsigned int m_CropX;
    unsigned int m_CropY;
    unsigned int m_CropWidth;
    unsigned int m_CropHeight;

    // Flip
    bool m_Flip;

    // Shave
    unsigned int m_ShaveWidth;
    unsigned int m_ShaveHeight;

    // Controls
    wxTextCtrl* m_pFilenameTextCtrl;
    wxTextCtrl* m_pSizeWidthTextCtrl;
    wxTextCtrl* m_pSizeHeightTextCtrl;
    wxTextCtrl* m_pRotationTextCtrl;
    wxTextCtrl* m_pScaleXTextCtrl;
    wxTextCtrl* m_pScaleYTextCtrl;
    wxTextCtrl* m_pCropXTextCtrl;
    wxTextCtrl* m_pCropYTextCtrl;
    wxTextCtrl* m_pCropWidthTextCtrl;
    wxTextCtrl* m_pCropHeightTextCtrl;
    wxTextCtrl* m_pFuzzTextCtrl;
    wxTextCtrl* m_pShaveWidthTextCtrl;
    wxTextCtrl* m_pShaveHeightTextCtrl;

    // Composite Controls
    wxTextCtrl* m_pCompositeFilename0TextCtrl;
    wxTextCtrl* m_pCompositeFilename1TextCtrl;
    wxTextCtrl* m_pCompositeFilename2TextCtrl;
    wxTextCtrl* m_pCompositeFilename3TextCtrl;
    wxTextCtrl* m_pCompisteX0TextCtrl;
    wxTextCtrl* m_pCompisteY0TextCtrl;
    wxTextCtrl* m_pCompisteX1TextCtrl;
    wxTextCtrl* m_pCompisteY1TextCtrl;
    wxTextCtrl* m_pCompisteX2TextCtrl;
    wxTextCtrl* m_pCompisteY2TextCtrl;
    wxTextCtrl* m_pCompisteX3TextCtrl;
    wxTextCtrl* m_pCompisteY3TextCtrl;


private:

    void UpdateView();
    void OnSaveAs(wxCommandEvent& event);
    void OnSaveCurrent(wxCommandEvent& event);
    void OnSizeChanged(wxCommandEvent& event);
    void OnShaveChanged(wxCommandEvent& event);
    void OnRotationChanged(wxCommandEvent& event);
    void OnScaleChanged(wxCommandEvent& event);
    void OnCropChanged(wxCommandEvent& event);
    void OnFlipChanged(wxCommandEvent& event);
    void OnTrimChanged(wxCommandEvent& event);
    void OnCompositeChanged(wxCommandEvent& event);
    void OnFindTexture0(wxCommandEvent& event);
    void OnFindTexture1(wxCommandEvent& event);
    void OnFindTexture2(wxCommandEvent& event);
    void OnFindTexture3(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

