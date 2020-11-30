#include "stdafx.h"
#include <wx/app.h>
#include "Properties.h"
#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(Properties, wxWindow)
    EVT_BUTTON(ID_BUTTON_SAVE_COPY_AS,      Properties::OnSaveAs)
    EVT_BUTTON(ID_BUTTON_SAVE_CURRENT,      Properties::OnSaveCurrent)
    EVT_BUTTON(ID_BUTTON_RESIZE_TEXTURE,    Properties::OnSizeChanged)
    EVT_BUTTON(ID_BUTTON_CROP,              Properties::OnCropChanged)
    EVT_BUTTON(ID_BUTTON_ROTATE,            Properties::OnRotationChanged)
    EVT_BUTTON(ID_BUTTON_SCALE,             Properties::OnScaleChanged)
    EVT_BUTTON(ID_BUTTON_SHAVE,             Properties::OnShaveChanged)
    EVT_BUTTON(ID_BUTTON_FLIP,              Properties::OnFlipChanged)
wxEND_EVENT_TABLE()

Properties::Properties(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style):
	wxWindow(parent, id, pos, size, style),
    m_Flip{false},
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) },
    m_FileNameUpdated{false}
{
#pragma region validators
    wxIntegerValidator<unsigned int>
        val1(&m_Width, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        val2(&m_Height, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxFloatingPointValidator<float>
        rot(&m_Angle, wxNUM_VAL_DEFAULT);

    wxFloatingPointValidator<float>
        scaleWidthVal(&m_ScaleWidth, wxNUM_VAL_DEFAULT);

    wxFloatingPointValidator<float>
        scaleHeightVal(&m_ScaleHeight, wxNUM_VAL_DEFAULT);

    wxIntegerValidator<unsigned int>
        cropXval(&m_CropX, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        cropYval(&m_CropY, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        cropWidthval(&m_CropWidth, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        cropHeightval(&m_CropHeight, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        shaveWidthval(&m_ShaveWidth, wxNUM_VAL_THOUSANDS_SEPARATOR);

    wxIntegerValidator<unsigned int>
        shaveHeightval(&m_ShaveHeight, wxNUM_VAL_THOUSANDS_SEPARATOR);

#pragma endregion

	wxBoxSizer* boxSizer = new wxBoxSizer{wxVERTICAL};

    m_pFilenameTextCtrl = new wxTextCtrl(this, -1, "");
    boxSizer->Add(
        m_pFilenameTextCtrl,
        0,                          // make vertically stretchable
        wxEXPAND |                  // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonsSizer->Add(
        new wxButton(this, ID_BUTTON_SAVE_COPY_AS, "Save Copy As"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1

    buttonsSizer->Add(
        new wxButton(this, ID_BUTTON_SAVE_CURRENT, "Save Current"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1

    boxSizer->Add(buttonsSizer, 0, wxALL | wxALIGN_RIGHT);

#pragma region // Size of file
    wxBoxSizer* imageSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    imageSizeSizer->Add(
        new wxStaticText(this,-1,"Width:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );

    m_pSizeWidthTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, val1);
    imageSizeSizer->Add(
        m_pSizeWidthTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL | wxALIGN_CENTER,                      //   and make border all around
        2);                         // set border width to 1

    imageSizeSizer->Add(
        new wxStaticText(this, -1, "Height:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );

    m_pSizeHeightTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, val2);
    imageSizeSizer->Add(
        m_pSizeHeightTextCtrl,
        0,
        wxALL | wxALIGN_CENTER,
        2);

    imageSizeSizer->Add(
        new wxButton(this, ID_BUTTON_RESIZE_TEXTURE, "Resize"),
        0,                          // make horizontally unstretchable
        wxALL |                     // make border all around (implicit top alignment)
        wxALIGN_CENTER,              //   and align the button to the right
        2);                         // set border width to 1

    boxSizer->Add(imageSizeSizer, 0, wxALL | wxALIGN_CENTER);
#pragma endregion 

#pragma region // Rotate image
    wxBoxSizer* rotateImageSizer = new wxBoxSizer(wxHORIZONTAL);
    rotateImageSizer->Add(
        new wxStaticText(this, -1, "Degrees:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );

    m_pRotationTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, rot);
    rotateImageSizer->Add(
        m_pRotationTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    rotateImageSizer->Add(
        new wxButton(this, ID_BUTTON_ROTATE, "Rotate"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1
    boxSizer->Add(rotateImageSizer, 0, wxALL | wxALIGN_CENTER);
#pragma endregion

#pragma region // Scale image
    wxBoxSizer* scaleImageSizer = new wxBoxSizer(wxHORIZONTAL);
    scaleImageSizer->Add(
        new wxStaticText(this, -1, "X:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pScaleXTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, scaleWidthVal);
    scaleImageSizer->Add(
        m_pScaleXTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    scaleImageSizer->Add(
        new wxStaticText(this, -1, "Y:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pScaleYTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, scaleHeightVal);
    scaleImageSizer->Add(
        m_pScaleYTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    scaleImageSizer->Add(
        new wxButton(this, ID_BUTTON_SCALE, "Scale"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1
    boxSizer->Add(scaleImageSizer, 0, wxALL | wxALIGN_CENTER);
#pragma endregion

#pragma region // Crop Image
    wxFlexGridSizer* cropImageSizeSizer = new wxFlexGridSizer(2,4,2,2);
    cropImageSizeSizer->Add(
        new wxStaticText(this, -1, "X:"),
        0,
        wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL,
        2
    );

    m_pCropXTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, cropXval);
    cropImageSizeSizer->Add(
        m_pCropXTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL ,                      //   and make border all around
        2);                         // set border width to 1

    cropImageSizeSizer->Add(
        new wxStaticText(this, -1, "Y:"),
        0,
        wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL,
        2
    );

    m_pCropYTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, cropYval);
    cropImageSizeSizer->Add(
        m_pCropYTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    cropImageSizeSizer->Add(
        new wxStaticText(this, -1, "Width:"),
        0,
        wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL,
        2
    );

    m_pCropWidthTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, cropWidthval);
    cropImageSizeSizer->Add(
        m_pCropWidthTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    cropImageSizeSizer->Add(
        new wxStaticText(this, -1, "Height:"),
        0,
        wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL,
        2
    );
    m_pCropHeightTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, cropHeightval);
    cropImageSizeSizer->Add(
        m_pCropHeightTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    boxSizer->Add(cropImageSizeSizer, 0, wxALL | wxALIGN_CENTER);

    boxSizer->Add(
        new wxButton(this, ID_BUTTON_CROP, "Crop"),
        0,                          // make horizontally unstretchable
        wxALL |                     // make border all around (implicit top alignment)
        wxALIGN_RIGHT,              //   and align the button to the right
        2);                         // set border width to 1
#pragma endregion

#pragma region // Trim Image
    wxBoxSizer* trimImageSizer = new wxBoxSizer(wxHORIZONTAL);
    trimImageSizer->Add(
        new wxStaticText(this, -1, "Fuzz:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );

    m_pFuzzTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, rot);
    trimImageSizer->Add(
        m_pFuzzTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    trimImageSizer->Add(
        new wxButton(this, ID_BUTTON_TRIM, "Trim"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1
    boxSizer->Add(trimImageSizer, 0, wxALL | wxALIGN_CENTER);
#pragma endregion

#pragma region // Shave image
    wxBoxSizer* shaveImageSizer = new wxBoxSizer(wxHORIZONTAL);
    shaveImageSizer->Add(
        new wxStaticText(this, -1, "Width:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pShaveWidthTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, shaveWidthval);
    shaveImageSizer->Add(
        m_pShaveWidthTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    shaveImageSizer->Add(
        new wxStaticText(this, -1, "Height:"),
        0,
        wxALL | wxALIGN_CENTER,
        2
    );
    m_pShaveHeightTextCtrl = new wxTextCtrl(this, wxID_ANY, "0", wxDefaultPosition, wxSize{ 100, -1 }, 0, shaveHeightval);
    shaveImageSizer->Add(
        m_pShaveHeightTextCtrl,
        0,                          // make vertically stretchable
                          // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1

    shaveImageSizer->Add(
        new wxButton(this, ID_BUTTON_SHAVE, "Shave"),
        0,                          // make horizontally unstretchable
        wxALL,              //   and align the button to the right
        2);                         // set border width to 1
    boxSizer->Add(shaveImageSizer, 0, wxALL | wxALIGN_CENTER);
#pragma endregion
	SetSizerAndFit(boxSizer);
}

void Properties::SetFileName(const wxString& fileName)
{
    m_FileName = fileName; 
    m_FileNameUpdated = true;
    UpdateView();
}

void Properties::UpdateView()
{
    wxSize size = m_pMainFrame->GetWorldCanvas()->ImageSize();

    m_pFilenameTextCtrl->SetValue(m_FileName);

    m_pSizeWidthTextCtrl->SetValue(wxString::FromDouble(size.x));
    m_pSizeHeightTextCtrl->SetValue(wxString::FromDouble(size.y));
}


void Properties::OnSaveAs(wxCommandEvent& event)
{
    /* 
     * Verificaciones:
     * - El nombre del fichero debe ser igual que el de la caja de texto.
     * - El fichero actual haya sido modificado.
     */
}

void Properties::OnSaveCurrent(wxCommandEvent& event)
{
    m_pMainFrame->GetWorldCanvas()->SaveImage();
}

void Properties::OnSizeChanged(wxCommandEvent& event)
{
    wxString strWidth = m_pSizeWidthTextCtrl->GetValue();
    wxString strHeight = m_pSizeHeightTextCtrl->GetValue();
    m_Width = wxAtoi(strWidth);
    m_Height = wxAtoi(strHeight);

    m_pMainFrame->GetWorldCanvas()->ResizeImage(m_Width, m_Height);

    UpdateView();
}

void Properties::OnShaveChanged(wxCommandEvent& event)
{
    wxString strWidth = m_pShaveWidthTextCtrl->GetValue();
    wxString strHeight = m_pShaveHeightTextCtrl->GetValue();

    m_ShaveWidth = wxAtoi(strWidth);
    m_ShaveHeight = wxAtoi(strHeight);

    m_pMainFrame->GetWorldCanvas()->ShaveImage(m_ShaveWidth, m_ShaveHeight);

    UpdateView();
}

void Properties::OnRotationChanged(wxCommandEvent& event)
{
    wxString strRotation = m_pRotationTextCtrl->GetValue();
    double value;
    strRotation.ToDouble(&value);

    m_Angle = (float)value;

    m_pMainFrame->GetWorldCanvas()->RotateImage(m_Angle);

    UpdateView();
}

void Properties::OnScaleChanged(wxCommandEvent& event)
{
    wxString strX = m_pScaleXTextCtrl->GetValue();
    wxString strY = m_pScaleYTextCtrl->GetValue();
    double value;
    strX.ToDouble(&value);
    m_ScaleWidth = (float)value;

    strY.ToDouble(&value);
    m_ScaleHeight = (float)value;

    m_pMainFrame->GetWorldCanvas()->ScaleImage(m_ScaleWidth, m_ScaleHeight);

    UpdateView();
}

void Properties::OnCropChanged(wxCommandEvent& event)
{
    wxString strX = m_pCropXTextCtrl->GetValue();
    wxString strY = m_pCropYTextCtrl->GetValue();
    wxString strWidth = m_pCropWidthTextCtrl->GetValue();
    wxString strHeight = m_pCropHeightTextCtrl->GetValue();

    m_CropX = wxAtoi(strX);
    m_CropY = wxAtoi(strY);
    m_CropWidth = wxAtoi(strWidth);
    m_CropHeight = wxAtoi(strHeight);

    m_pMainFrame->GetWorldCanvas()->CropImage(m_CropX, m_CropY, m_CropWidth, m_CropHeight);

    UpdateView();
}

void Properties::OnFlipChanged(wxCommandEvent& event)
{
    int stop = 1;
}

void Properties::OnTrimChanged(wxCommandEvent& event)
{
    wxString strFuzz = m_pFuzzTextCtrl->GetValue();
    double value;
    strFuzz.ToDouble(&value);

    m_pMainFrame->GetWorldCanvas()->TrimImage(value);

    UpdateView();
}
