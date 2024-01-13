#include "font.hpp"

Font::Font() {}

Font::Font(SDL_Renderer* sdl_renderer, FONT_TYPE font_type, int font_size, SDL_Color color) {
    this->m_renderer = sdl_renderer;
    this->m_font_size = font_size;
    this->m_font_color = color;

    std::string font_path = get_Font_Path(font_type);
    std::cout << "Font path is: " << font_path << std::endl;
    this->m_font_path = font_path;
    TTF_Font* font;
    if ((font = TTF_OpenFont(font_path.c_str(), m_font_size)) == NULL) {
        std::cout << "Failed to open font: " << SDL_GetError() << std::endl;
    }
    this->m_font_data = TTF_OpenFont(font_path.c_str(), m_font_size);
    std::cout << "Font data is: " << m_font_data << std::endl;

    init_Font_Atlas();
}

Font::~Font() {}

void Font::init_Font_Atlas() {
    SDL_Surface* surface;
    SDL_Surface* text;
    SDL_Rect destination;
    SDL_Rect* glyph;
    char c[2];

    destination.x = 0;
    destination.y = 0;

    surface = SDL_CreateRGBSurface(0, FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, 32, 0, 0, 0, 0xff);
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGBA(surface->format, 0, 0, 0, 0));

    SDL_Color color;
    color.a = 255;
    color.b = 255;
    color.g = 255;
    color.r = 255;

    for (int i = ' '; i <= 'z'; i++) {
        c[0] = i;
        c[1] = 0;
        text = TTF_RenderUTF8_Blended(m_font_data, c, color);
        TTF_SizeText(m_font_data, c, &destination.w, &destination.h);

        if (destination.x + destination.w >= FONT_TEXTURE_SIZE) {
            destination.x = 0;
            destination.y += destination.h + 1;
            if (destination.y + destination.h >= FONT_TEXTURE_SIZE) {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Out of glyph space in glyph texture atlas");
                SDL_Quit();
                exit(1);
            }
        }
        SDL_BlitSurface(text, NULL, surface, &destination);
        glyph = &m_glyphs[i];
        glyph->x = destination.x;
        glyph->y = destination.y;
        glyph->w = destination.w;
        glyph->h = destination.h;
        SDL_FreeSurface(text);
        destination.x += destination.w;
    }
    m_glyph_atlas = to_Texture(surface, 1);
}

void Font::draw_Text(std::string text, FONT_TYPE font_type, SDL_Color color, int x_pos, int y_pos) {
    int i = 0;
    int character;
    SDL_Rect* glyph;
    SDL_Rect destination;

    SDL_SetTextureColorMod(m_glyph_atlas, color.r, color.g, color.b);
    character = text[i++];
    
    while (character) {
        glyph = &m_glyphs[character];
        destination.x = x_pos;
        destination.y = y_pos;
        destination.w = glyph->w;
        destination.h = glyph->h;

        SDL_RenderCopy(m_renderer, m_glyph_atlas, glyph, &destination);
        x_pos += glyph->w;
        character = text[i++];
    }
}

void Font::blit_Texture(SDL_Texture* texture, int x_pos, int y_pos) {
    SDL_Rect destination;
    destination.x = x_pos;
    destination.y = y_pos;

    if (SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h) < 0) {
        printf("Failed to query texture of text: %s", SDL_GetError());
        std::cout << "Texture is: " << texture << std::endl;
    }

    if (SDL_RenderCopy(m_renderer, texture, NULL, &destination) < 0) {
            printf("Failed to render copy of text: %s", SDL_GetError());
    }
}

SDL_Texture* Font::get_Text_Texture(std::string text) {
    SDL_Surface* surface;
    if ((surface = TTF_RenderUTF8_Blended(m_font_data, text.c_str(), m_font_color)) == NULL) {
        std::cout << "Failed to render text surface: " << SDL_GetError() << std::endl;
    }
    return to_Texture(surface, 1);
}

SDL_Texture* Font::to_Texture(SDL_Surface* sdl_surface, int destroy_surface) {
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(m_renderer, sdl_surface);

    if (destroy_surface) {
        SDL_FreeSurface(sdl_surface);
    }
    return texture;
}

std::string Font::get_Font_Path(FONT_TYPE font_type) {
    switch (font_type) {
    case FONT_TYPE::ENTER_COMMAND:
        return ENTER_COMMAND_PATH;
        break;
    case FONT_TYPE::ENTER_COMMAND_BOLD:
        return ENTER_COMMAND_BOLD_PATH;
        break;
    case FONT_TYPE::ENTER_COMMAND_ITALIC:
        return ENTER_COMMAND_ITALIC_PATH;
        break;
    default:
        break;
    }
    return "";
}

TTF_Font* Font::get_Font_Data() {
    return this->m_font_data;
}

SDL_Color Font::get_Font_Color() {
    return this->m_font_color;
}