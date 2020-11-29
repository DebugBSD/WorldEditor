#include "stdafx.h"
#include <wx/app.h>
#include "Properties.h"
#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(Properties, wxWindow)
    EVT_BUTTON(ID_BUTTON_SAVE_COPY_AS,      Properties::OnSaveAs)
    EVT_BUTTON(ID_BUTTON_RESIZE_TEXTURE,    Properties::OnSizeChanged)
    EVT_BUTTON(ID_BUTTON_ROTATE,            Properties::OnRotationChanged)
    EVT_BUTTON(ID_BUTTON_SCALE,             Properties::OnScaleChanged)
    EVT_BUTTON(ID_BUTTON_CROP,              Properties::OnCropChanged)
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
#pragma endregion

	wxBoxSizer* boxSizer = new wxBoxSizer{wxVERTICAL};

    // create text ctrl with minimal size 100x60
    boxSizer->Add(
        new wxTextCtrl(this, -1, "FileName"),
        0,                          // make vertically stretchable
        wxEXPAND |                  // make horizontally stretchable
        wxALL,                      //   and make border all around
        2);                         // set border width to 1
    boxSizer->Add(
        new wxButton(this, ID_BUTTON_SAVE_COPY_AS, "Save Copy As"),
        0,                          // make horizontally unstretchable
        wxALL |                     // make border all around (implicit top alignment)
        wxALIGN_RIGHT,              //   and align the button to the right
        2);                         // set border width to 1
    
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

	SetSizerAndFit(boxSizer);
}

void Properties::CreateThumbnail()
{
    Image
        * image,
        * images,
        * resize_image,
        * thumbnails;

    ImageInfo
        * image_info;

    ExceptionInfo* exception = m_pMainFrame->GetExceptionInfoPtr();

    image_info = CloneImageInfo((ImageInfo*)NULL);
    (void)strcpy(image_info->filename, "C:\\Users\\debugg\\My Projects\\Videojuegos\\Heroes of Magic Worlds\\Game\\Debug\\Resources\\Levels\\Textures\\Dirt_8_Tile.png");
    images = ReadImage(image_info, exception);
    if (exception->severity != UndefinedException)
        CatchException(exception);
    if (images == (Image*)NULL)
        exit(1);
    /*
      Convert the image to a thumbnail.
    */
    thumbnails = NewImageList();
    while ((image = RemoveFirstImageFromList(&images)) != (Image*)NULL)
    {
        resize_image = ResizeImage(image, 106, 80, LanczosFilter, exception);
        if (resize_image == (Image*)NULL)
            MagickError(exception->severity, exception->reason, exception->description);
        (void)AppendImageToList(&thumbnails, resize_image);
        DestroyImage(image);
    }
    /*
      Write the image thumbnail.
    */
    (void)strcpy(thumbnails->filename, "C:\\Users\\debugg\\My Projects\\Videojuegos\\Heroes of Magic Worlds\\Game\\Debug\\Resources\\Levels\\Textures\\Dirt.png");
    WriteImage(image_info, thumbnails, exception);
    /*
      Destroy the image thumbnail and exit.
    */
    thumbnails = DestroyImageList(thumbnails);
    image_info = DestroyImageInfo(image_info);
}

void Properties::OnSaveAs(wxCommandEvent& event)
{
    int stop = 1;
}

void Properties::OnSizeChanged(wxCommandEvent& event)
{
    wxString strWidth = m_pSizeWidthTextCtrl->GetValue();
    wxString strHeight = m_pSizeHeightTextCtrl->GetValue();
    m_Width = wxAtoi(strWidth);
    m_Height = wxAtoi(strHeight);

    m_pMainFrame->GetWorldCanvas()->ResizeImage(m_Width, m_Height);

#if 0
    Image *image,*resize_image;

    ImageInfo *image_info;

    ExceptionInfo* exception = m_pMainFrame->GetExceptionInfoPtr();

    image_info = CloneImageInfo((ImageInfo*)NULL);
    (void)strcpy(image_info->filename, m_FileName.c_str());
    image = ReadImage(image_info, exception);
    if (exception->severity != UndefinedException)
        CatchException(exception);
    if (image == (Image*)NULL)
    {
        // Log error...
        image_info = DestroyImageInfo(image_info);
        //exit(1);
        return;
    }

    /*
      Convert the image to a thumbnail.
    */
    resize_image = ResizeImage(image, m_Width, m_Height, LanczosFilter, exception);
    if (resize_image == (Image*)NULL)
    {
        // Log error...
        image_info = DestroyImageInfo(image_info);
        MagickError(exception->severity, exception->reason, exception->description);
    }
    DestroyImage(image);
    /*
      Write the image thumbnail.
    */
    (void)strcpy(resize_image->filename, "C:\\Users\\debugg\\My Projects\\Videojuegos\\Heroes of Magic Worlds\\Assets\\Tilesets\\Ground\\resized.png");
    WriteImage(image_info, resize_image, exception);
    /*
      Destroy the image thumbnail and exit.
    */
    image_info = DestroyImageInfo(image_info);
#endif
}

void Properties::OnRotationChanged(wxCommandEvent& event)
{
    wxString strRotation = m_pRotationTextCtrl->GetValue();
    double value;
    strRotation.ToDouble(&value);

    m_Angle = (float)value;

    m_pMainFrame->GetWorldCanvas()->RotateImage(m_Angle);
#if 0
    //CreateThumbnail();

    // Image Magick rotation
    
    MagickWand
        * magick_wand;  /* the appended output image */

    PixelWand
        * color;

    MagickBooleanType
        status;

    /* read in the red image */
    magick_wand = NewMagickWand();
    //MagickSetSize(red, 100, 100);
    status = MagickReadImage(magick_wand, m_FileName.c_str());
    if (status == MagickFalse)
        ThrowWandException(magick_wand);

    /* rotate the rose image - one image only */
    color = NewPixelWand();
    PixelSetColor(color, "transparent");
    status = MagickRotateImage(magick_wand, color, m_Angle);
    if (status == MagickFalse)
        ThrowWandException(magick_wand);
    color = DestroyPixelWand(color);

    /* NOTE ABOUT MagickAppendImages()
     *
     * It is important to either 'set first' or 'reset' the iterator before
     * appending images, as only images from current image onward are
     * appended together.
     *
     * Also note how a new wand is created by this operation, and that new
     * wand does not inherit any settings from the previous wand (at least not
     * at this time).
     */

     /* Final output */
    status = MagickWriteImage(magick_wand, "C:\\Users\\debugg\\My Projects\\Videojuegos\\Heroes of Magic Worlds\\Assets\\Tilesets\\Ground\\rotated.png");
    if (status == MagickFalse)
        ThrowWandException(magick_wand);

    magick_wand = DestroyMagickWand(magick_wand);
#endif
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
}

void Properties::OnFlipChanged(wxCommandEvent& event)
{
    int stop = 1;
}
