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
    MagickBooleanType
        status;

    if (m_pMagickWand != NULL)
    {
        m_pMagickWand = DestroyMagickWand(m_pMagickWand);
        m_pMagickWand = NULL;
    }

    m_pMagickWand = NewMagickWand();

    m_Filename = filename;

    /* read in the red image */
    status = MagickReadImage(m_pMagickWand, m_Filename.c_str());
    if (status == MagickFalse)
    {
        // TODO: Handle errors
        ThrowWandException(m_pMagickWand);
    }

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

void weImage::update()
{
    readPixelsFromImage();
}

void weImage::resize(size_t width, size_t height)
{
    /* 
     * Possible algorithms to use:
     * - MagickAdaptativeResizeImage
     * - MagickInterpolativeResizeImage
     * - MagickResizeImage
     *      - Filters: 
     *          Bessel, Blackman, Box, Catrom, CubicGaussian, Hanning, Hermite, 
     *          Lanczos, Mitchell, PointQuandratic, Sinc, Triangle.
     */
    MagickBooleanType resized = MagickResizeImage(m_pMagickWand, width, height, BoxFilter);
    // There is no description about the return value.
}

void weImage::scale(double x, double y)
{
    MagickBooleanType scaled = MagickScaleImage(m_pMagickWand, getSize().x * x, getSize().y * y);
}

void weImage::crop(double x, double y, double width, double height)
{
}

void weImage::rotate(double degrees)
{
    PixelWand *color;

    MagickBooleanType status;

    color = NewPixelWand();
    PixelSetColor(color, "transparent");
    status = MagickRotateImage(m_pMagickWand, color, degrees);
    if (status == MagickFalse)
    {
        // TODO: Handle errors
        ThrowWandException(m_pMagickWand);
    }
    color = DestroyPixelWand(color);
}

void weImage::readPixelsFromImage()
{
    PixelWand *color;

    MagickBooleanType status;

    wxSize size = getSize();

    m_pPixels = (uint8_t*)malloc((size_t)size.x * (size_t)size.y * (size_t)3);
    m_pAlphaPixels = (uint8_t*)malloc((size_t)size.x * (size_t)size.y);

    char* pixels = (char *)malloc((size_t)size.x * (size_t)size.y * (size_t)4);

    MagickBooleanType isOK = MagickExportImagePixels(m_pMagickWand, 0,0, size.x, size.y, "RGBA", CharPixel, pixels);
    if (isOK == MagickTrue)
    {
        if (pixels != NULL)
        {
            int pixelsIndex = 0;
            int alphaIndex = 0;
            for (int i = 0; i < size.x * size.y * 4; i += 4)
            {
                m_pPixels[pixelsIndex++] = (uint8_t)pixels[i];
                m_pPixels[pixelsIndex++] = (uint8_t)pixels[i + 1];
                m_pPixels[pixelsIndex++] = (uint8_t)pixels[i + 2];
                m_pAlphaPixels[alphaIndex++] = (uint8_t)pixels[i + 3];
            }
            std::free(pixels);
        }
    }
    else
    {
        // Log error...

        // Clean resources
        if (m_pPixels != NULL)
        {
            std::free(m_pPixels);
            m_pPixels = NULL;
        }

        if (m_pAlphaPixels != NULL)
        {
            std::free(m_pAlphaPixels);
            m_pAlphaPixels = NULL;
        }

        if (pixels != NULL)
        {
            std::free(pixels);
        }
    }
}
