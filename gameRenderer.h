#pragma once

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

struct TextObj {
    uint m_w;
    uint m_h;
    SDL_Texture * m_texture;
};

class GameRenderer {
    public:
        GameRenderer();
        bool init();
        void quit();
        void renderBlock(uint x, uint y, const std::string & texture);
        void setText(const std::string & text);
        void renderText(uint x, uint y);
        void renderStart();
        void renderEnd();
        bool loadSprite(const std::string & name);
        uint getNumSprites();
    private:
        SDL_Window * m_window;
        SDL_Renderer * m_renderer;
        SDL_Rect m_srcRect;
        SDL_Rect m_dstRect;
        TTF_Font * m_font;
        SDL_Color m_textColour;
        TextObj m_scoreCntr;
        std::map<std::string, SDL_Texture*> m_sprites;
};
