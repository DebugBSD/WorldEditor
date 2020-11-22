#pragma once
#include "wxSFMLCanvas.h"
class WorldCanvas :
    public wxSFMLCanvas
{
public:
    WorldCanvas(wxWindow *pParent, wxWindowID id, wxPoint &Position, wxSize &size, long style = 0);

private:

    virtual void OnUpdate();

    sf::Texture m_Texture;
    sf::Sprite m_Sprite;
};

