#include "stdafx.h"
#include "WorldCanvas.h"

WorldCanvas::WorldCanvas(wxWindow* pParent, wxWindowID id, const wxPoint& Position, const wxSize& size, long style):
	wxSFMLCanvas(pParent, id, Position, size, style),
	m_pSprite{nullptr},
	m_pTexture{nullptr}
{

}

bool WorldCanvas::OpenTexture(const wxString& pathToTexture)
{
	free(); // Preexisting textures...

	m_pTexture = new sf::Texture();
	bool res = m_pTexture->loadFromFile(pathToTexture.ToStdString());
	if (res)
	{
		m_pSprite = new sf::Sprite();
		m_pSprite->setTexture(*m_pTexture);
		int width, height;
		GetClientSize(&width, &height);
		m_pSprite->setPosition(width / 2, height / 2);

		m_pSprite->setOrigin(m_pTexture->getSize().x / 2, m_pTexture->getSize().y / 2);
	}
	else
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	return res;
}

void WorldCanvas::free()
{
	if (m_pSprite)
	{
		delete m_pSprite;
		m_pSprite = nullptr;
	}

	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void WorldCanvas::OnUpdate()
{
	static int lastWidth = 0, lastHeight = 0;
	int width, height;
	GetClientSize(&width, &height);

	if (((lastWidth != width) || (lastHeight != height)) && m_pSprite != nullptr)
	{
		m_pSprite->setPosition(width / 2, height / 2);

		m_pSprite->setOrigin(m_pTexture->getSize().x / 2, m_pTexture->getSize().y / 2);

		lastWidth = width;
		lastHeight = height;
	}

	// Clear the view
	clear(sf::Color(0, 128, 128));

	// Display the sprite in the view
	//m_Sprite.rotate(0.16);
	if (m_pSprite != nullptr)
	{
		draw(*m_pSprite);
	}
}
