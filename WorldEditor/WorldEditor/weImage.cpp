#include "stdafx.h"
#include "weImage.h"

#include "MainFrame.h"

weImage::weImage():
	m_pMagickWand{NULL},
	m_ImageModified{false},
	m_pPixels{NULL},
    m_pAlphaPixels{NULL},
    m_pMainFrame{ static_cast<MainFrame*>(wxTheApp->GetTopWindow()) }
{

}

weImage::~weImage()
{
    free();

    if (m_pMagickWand != NULL)
    {
        m_pMagickWand = DestroyMagickWand(m_pMagickWand);
        m_pMagickWand = NULL;
    }
}

bool weImage::init(const std::string& filename)
{
    if (m_pMagickWand != NULL)
    {
        m_pMagickWand = DestroyMagickWand(m_pMagickWand);
        m_pMagickWand = NULL;
    }

    m_pMagickWand = NewMagickWand();

    m_Filename = filename;
    readPixelsFromImage();
	return true;
}

void weImage::free()
{

}

void weImage::read()
{
	m_ImageModified = true;
}

void weImage::save()
{
	if (m_ImageModified)
	{
		m_ImageModified = true;
	}
}

wxSize weImage::getSize()
{
    wxSize size;

    size.y = MagickGetImageHeight(m_pMagickWand);
    size.x = MagickGetImageWidth(m_pMagickWand);

    return size;
}

void weImage::scale(double x, double y)
{
}

void weImage::crop(double x, double y, double width, double height)
{
}

void weImage::rotate(double degrees)
{
}

void weImage::readPixelsFromImage()
{
    PixelWand
        * color;

    MagickBooleanType
        status;

    /* read in the red image */
    status = MagickReadImage(m_pMagickWand, m_Filename.c_str());
    if (status == MagickFalse)
        ThrowWandException(m_pMagickWand);

    wxSize size = getSize();

    std::free(m_pPixels);
    std::free(m_pAlphaPixels);

    m_pPixels = (uint8_t*)malloc((size_t)size.x * (size_t)size.y * (size_t)3);
    m_pAlphaPixels = (uint8_t*)malloc((size_t)size.x * (size_t)size.y);

    Quantum* pData = GetAuthenticPixels(GetImageFromMagickWand(m_pMagickWand), 0, 0, size.x, size.y, m_pMainFrame->GetExceptionInfoPtr());

    if (pData != NULL)
    {
        int pixelsIndex = 0;
        int alphaIndex = 0;
        for (int i = 0; i < size.x * size.y * 4; i+=4)
        {
            m_pPixels[pixelsIndex++] = (uint8_t)pData[i];
            m_pPixels[pixelsIndex++] = (uint8_t)pData[i+1];
            m_pPixels[pixelsIndex++] = (uint8_t)pData[i+2];
            m_pAlphaPixels[alphaIndex++] = (uint8_t)pData[i+3];
        }
    }
}
