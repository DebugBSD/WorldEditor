#pragma once
#include "wxSFMLCanvas.h"
class WorldCanvas :
    public wxSFMLCanvas
{
public:
    WorldCanvas(wxWindow *pParent, wxWindowID id, const wxPoint &Position, const wxSize &size, long style = 0);

    bool OpenTexture(const wxString &pathToTexture);

private:

    void free();

    virtual void OnUpdate();

    sf::Texture *m_pTexture;
    sf::Sprite *m_pSprite;
};

