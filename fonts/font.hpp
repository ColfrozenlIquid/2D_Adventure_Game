#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#define FONT_TEXTURE_SIZE 1024
#define NUM_GLYPHS 128

#define ENTER_COMMAND_BOLD_PATH     "C:/Users/Daniel/Desktop/Game/fonts/EnterCommand-Bold.ttf"
#define ENTER_COMMAND_ITALIC_PATH   "C:/Users/Daniel/Desktop/Game/fonts/EnterCommand-Italic.ttf"
#define ENTER_COMMAND_PATH          "C:/Users/Daniel/Desktop/Game/fonts/EnterCommand.ttf"

class Font{
    public:

        enum FONT_TYPE{
            ENTER_COMMAND_BOLD,
            ENTER_COMMAND_ITALIC,
            ENTER_COMMAND
        };

        Font();
        Font(SDL_Renderer* sdl_renderer, FONT_TYPE font_type, int font_size, SDL_Color color);
        ~Font();

        TTF_Font* get_Font_Data();
        SDL_Color get_Font_Color();

        void init_Font_Atlas();
        void draw_Text(std::string text, FONT_TYPE font_type, SDL_Color color, int x_pos, int y_pos);

        SDL_Texture* get_Text_Texture(std::string text);
        void blit_Texture(SDL_Texture* texture, int x_pos, int y_pos);

    private:        
        SDL_Rect m_glyphs[NUM_GLYPHS];
        SDL_Texture* m_glyph_atlas;

        TTF_Font* m_font_data;
        FONT_TYPE m_font_type;
        std::string m_font_path;
        int m_font_size;
        SDL_Color m_font_color;
        SDL_Renderer* m_renderer;

        std::string get_Font_Path(FONT_TYPE font_type);
        SDL_Texture* to_Texture(SDL_Surface* sdl_surface, int destroy_surface);

        friend class Fonts;
};