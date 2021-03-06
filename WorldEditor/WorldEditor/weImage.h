#pragma once

#include <string>
#include <vector>

#include <wx/wx.h>
#include <wx/mstream.h>

#include <MagickCore/MagickCore.h>
#include <MagickWand/MagickWand.h>

struct TSplitImage
{
	std::string m_File;
	wxSize m_Rect;
};

struct TCompositeImage
{
	std::string m_File;
	wxPoint m_Point;
};

class weImage
{
public:
	weImage();
	~weImage();

	bool init(const wxSize& size, bool transparent = true);
	bool init(const std::string &filename);
	void free();

	void read();
	void save();
	void saveAs(const std::string& filename);

	wxString getFileName() { return m_Filename; }

	uint8_t* getPixels() { return m_pPixels; }
	uint8_t* getAlphaPixels() { return m_pAlphaPixels; }
	wxSize getSize();

	void update();
	void resize(size_t width, size_t height);
	void scale(double x, double y);
	void crop(double x, double y, double width, double height);
	void shave(size_t width, size_t height);
	void split(const std::vector<TSplitImage>& images);
	void rotate(double degrees);
	void trim(double fuzz);
	void composite(const std::vector<TCompositeImage>&images);
	void flip();

	wxMemoryInputStream* getInputStream() { return m_pInputStream; }

private:

	void readPixelsFromImage();

private:

	class MainFrame* m_pMainFrame;

	uint8_t* m_pPixels;
	uint8_t* m_pAlphaPixels; // wxWidgets (wxImage/wxBitmap) uses pixels and alpha channel in different buffers.

	std::string m_Filename;

	bool m_ImageModified;

	// ImageMagick context
	MagickWand* m_pMagickWand;

	// Just for testing purposes
	wxMemoryInputStream* m_pInputStream;
};

