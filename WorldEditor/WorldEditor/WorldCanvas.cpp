#include "stdafx.h"
#include "WorldCanvas.h"

WorldCanvas::WorldCanvas(wxWindow* pParent, wxWindowID id, wxPoint& Position, wxSize& size, long style):
	wxSFMLCanvas(pParent, id, Position, size, style)
{
	bool res = m_Texture.loadFromFile("C:\\Users\\debugg\\My Projects\\Videojuegos\\Heroes of Magic Worlds\\Assets\\Tilesets\\Ground\\[A]GroundTextures_17\\Volcanic_7_Tile.png");
	m_Sprite.setTexture(m_Texture);
	
}

void WorldCanvas::OnUpdate()
{
	// Clear the view
	clear(sf::Color(0, 128, 128));

	// Display the sprite in the view
	draw(m_Sprite);
}
