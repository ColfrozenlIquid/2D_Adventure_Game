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
    if ((font = TTF_OpenFont(font_path.c_str(), font_size)) == NULL) {
        std::cout << "Failed to open font: " << SDL_GetError() << std::endl;
    }
    this->m_font_data = TTF_OpenFont(font_path.c_str(), font_size);
    std::cout << "Font data is: " << m_font_data << std::endl;
}

Font::~Font() {}

TTF_Font* Font::get_Font_Data() {
    return this->m_font_data;
}

SDL_Color Font::get_Font_Color() {
    return this->m_font_color;
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