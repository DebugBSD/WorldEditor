#pragma once

#include <string>

#include <wx/wx.h>

#include <MagickCore/MagickCore.h>
#include <MagickWand/MagickWand.h>

class weImage
{
public:
	weImage();
	~weImage();

	bool init(const std::string &filename);
	void free();

	void read();
	void save();

	uint8_t* getPixels() { return m_pPixels; }
	wxSize getSize();

	void scale(double x, double y);
	void crop(double x, double y, double width, double height);
	void rotate(double degrees);

private:

	void readPixelsFromImage();

private:

	class MainFrame* m_pMainFrame;

	uint8_t* m_pPixels;

	std::string m_Filename;

	bool m_ImageModified;

	// ImageMagick context
	MagickWand* m_pMagickWand;

};

