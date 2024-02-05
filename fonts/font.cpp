#include "font.hpp"

Font::Font() {}

Font::Font(SDL_Renderer* sdl_renderer, FONT_TYPE font_type, int font_size, SDL_Color color) {
    this->m_renderer = sdl_renderer;
    this->m_font_size = font_size;
    this->m_font_color = color;
    this->m_font_type = font_type;

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

void Font::find_Supported_Characters() {
    int utf_8_start = 0;        //first utf8 code point
    int utf_8_end = 0x10ffff;   //last utf8 code point
    
    for (int i = utf_8_start; i <= utf_8_end; i++) {
        
    }
}

void Font::init_Font_Atlas_UTF8() {
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
        Uint32 capitalA = 0x0407;
        text = TTF_RenderUTF8_Blended(m_font_data, c, color);
        if(TTF_GlyphIsProvided32(m_font_data, capitalA) != 0 ) {
            std::cout << "Character: " << capitalA << " is present in current font" << std::endl;
        }
        else {
            std::cout << "Character: " << capitalA << " is not present in current font" << std::endl;
        }
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
        // if(TTF_GlyphIsProvided32(m_font_data, (Uint32)c) != 0 ) {
        //     std::cout << "Character: " << c << "is present in current font" << std::endl;
        // }
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

void Font::draw_Text(std::string text, FONT_TYPE font_type, SDL_Color color, TEXT_ALIGNMENT alignment, int x_pos, int y_pos, int max_width) {

    if (max_width > 0) {
        draw_Text_Wrapped(text, font_type, color, alignment, x_pos, y_pos, max_width, 1);
    }
    else {
        draw_Text_Line(text, font_type, color, alignment, x_pos, y_pos);
    }
}

void Font::draw_Rect(int x_pos, int y_pos, int width, int height, SDL_Color color) {
    SDL_Rect rect;
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = width;
    rect.h = height;

    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_renderer, &rect);
}

void Font::draw_Outline_Rect(int x_pos, int y_pos, int width, int height, SDL_Color color) {

}

void Font::draw_Boxed_Text(std::string text, SDL_Color font_color, SDL_Color box_color, TEXT_ALIGNMENT alignment, int x_pos, int y_pos) {
    int width = TEXT_BOX_WIDTH;
    int height = get_Wrapped_Text_Height(text, m_font_type, alignment, width);

    width += 10;
    height += 10;

    draw_Rect(x_pos - PADDING, y_pos - PADDING, width + PADDING*2, height + PADDING*2, Color::get_Color(Color::WHITE));
    draw_Rect(x_pos, y_pos, width, height, box_color);
    draw_Text(text, m_font_type, font_color, alignment, x_pos + 10, y_pos, width);
}

int Font::get_Wrapped_Text_Height(std::string text, FONT_TYPE font_type, TEXT_ALIGNMENT alignment, int width) {
    return draw_Text_Wrapped(text, font_type, m_font_color, alignment, 0, 0, width, 0);
}

int Font::draw_Text_Wrapped(std::string text, FONT_TYPE font_type, SDL_Color color, TEXT_ALIGNMENT alignment, int x_pos, int y_pos, int max_width, int do_draw) {
    char word[MAX_WORD_LENGTH];
    char line[MAX_LINE_LENGTH];
    int i = 0;
    int n = 0;
    int word_width = 0;
    int line_width = 0;
    int character = text[i++];
    int length = text.size();

    memset(word, 0, MAX_WORD_LENGTH);
    memset(line, 0, MAX_LINE_LENGTH);

    while (character) {
        word_width += m_glyphs[character].w;
        if (character != ' ') {
            word[n++] = character;
        }
        if (character == ' ' || i == length) {
            if ((line_width + word_width) >= max_width) {
                if (do_draw) {
                    draw_Text_Line(line, font_type, color, alignment, x_pos, y_pos);
                }
                memset(line, 0, MAX_LINE_LENGTH);
                y_pos += m_glyphs[' '].h;
                line_width = 0;
            }
            else if (line_width != 0) {
                strcat(line, " ");
            }
            strcat(line, word);
            line_width += word_width;
            memset(word, 0, MAX_WORD_LENGTH);
            word_width = 0;
            n = 0;
        }
        character = text[i++];
    }
    if (do_draw) {
        draw_Text_Line(line, font_type, color, alignment, x_pos, y_pos);
    }
    return (y_pos + m_glyphs[' '].h);
}

void Font::draw_Text_Line(std::string text, FONT_TYPE font_type, SDL_Color color, TEXT_ALIGNMENT alignment, int x_pos, int y_pos) {
    int i = 0;
    int character = text[i++];
    int w;
    int h;

    SDL_Rect* glyph;
    SDL_Rect destination;

    SDL_SetTextureColorMod(m_glyph_atlas, color.r, color.g, color.b);

    if (alignment != TEXT_ALIGNMENT::TEXT_ALIGN_LEFT) {
        calculate_Text_Dimnesions(text, font_type, &w, &h);
        if (alignment == TEXT_ALIGNMENT::TEXT_ALIGN_CENTER) {
            x_pos -= (w/2);
        }
        if (alignment == TEXT_ALIGNMENT::TEXT_ALIGN_RIGHT) {
            x_pos -= w;
        }
    }
    
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

void Font::calculate_Text_Dimnesions(std::string text, FONT_TYPE font_type, int* w, int* h) {
    int i = 0;
    int character = text[i++];
    SDL_Rect* glyph;
    *w = 0;
    *h = 0;

    while (character) {
        glyph = &m_glyphs[character];
        *w += glyph->w;
        *h = MAX(glyph->h, *h);
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
    std::string font_path;
    switch (font_type) {
        case ENTER_COMMAND:         font_path = ENTER_COMMAND_PATH; break;
        case ENTER_COMMAND_BOLD:    font_path = ENTER_COMMAND_BOLD_PATH; break;
        case ENTER_COMMAND_ITALIC:  font_path = ENTER_COMMAND_ITALIC_PATH; break;
        case RETRO_GAMING:          font_path = RETRO_GAMING_PATH; break;
        case SCRIPTORIUM:           font_path = SCRIPTORIUM_PATH; break;
        default:                    font_path = ENTER_COMMAND_PATH; break;
    }
    return font_path;
}

TTF_Font* Font::get_Font_Data() {
    return this->m_font_data;
}

SDL_Color Font::get_Font_Color() {
    return this->m_font_color;
}