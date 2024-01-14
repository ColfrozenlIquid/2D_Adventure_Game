#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "../defines.hpp"
#include "../fonts/color.hpp"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define FONT_TEXTURE_SIZE 1024
#define NUM_GLYPHS 128

#define MAX_WORD_LENGTH 30
#define MAX_LINE_LENGTH 80

#define PADDING 1

#define ENTER_COMMAND_BOLD_PATH     "C:/Users/Daniel/Desktop/Game/fonts/EnterCommand-Bold.ttf"
#define ENTER_COMMAND_ITALIC_PATH   "C:/Users/Daniel/Desktop/Game/fonts/EnterCommand-Italic.ttf"
#define ENTER_COMMAND_PATH          "C:/Users/Daniel/Desktop/Game/fonts/EnterCommand.ttf"
#define RETRO_GAMING_PATH           "C:/Users/Daniel/Desktop/Game/fonts/Retro Gaming.ttf"
#define SCRIPTORIUM_PATH           "C:/Users/Daniel/Desktop/Game/fonts/Scriptorium.ttf"

#define SUPPORTED_CHARACTERS ""

class Font{
    public:
        enum FONT_TYPE{
            ENTER_COMMAND_BOLD,
            ENTER_COMMAND_ITALIC,
            ENTER_COMMAND,
            RETRO_GAMING,
            SCRIPTORIUM
        };

        enum TEXT_ALIGNMENT {
            TEXT_ALIGN_LEFT,
            TEXT_ALIGN_CENTER,
            TEXT_ALIGN_RIGHT
        };

        enum TEXT_SCENE {
            SCENE_ALIGN,
            SCENE_WRAPPED,
            SCENE_BOXED,
            SCENE_TYPEWRITER
        };

        Font();
        Font(SDL_Renderer* sdl_renderer, FONT_TYPE font_type, int font_size, SDL_Color color);
        ~Font();

        TTF_Font* get_Font_Data();
        SDL_Color get_Font_Color();

        void init_Font_Atlas();
        void init_Font_Atlas_UTF8();

        void draw_Text(std::string text, FONT_TYPE font_type, SDL_Color color, TEXT_ALIGNMENT alignment, int x_pos, int y_pos, int max_width);
        int draw_Text_Wrapped(std::string text, FONT_TYPE font_type, SDL_Color color, TEXT_ALIGNMENT alignment, int x_pos, int y_pos, int max_width, int do_draw);
        void draw_Text_Line(std::string text, FONT_TYPE font_type, SDL_Color color, TEXT_ALIGNMENT alignment, int x_pos, int y_pos);
        void calculate_Text_Dimnesions(std::string text, FONT_TYPE font_type, int* w, int* h);

        void draw_Boxed_Text(std::string text, SDL_Color font_color, SDL_Color box_color, TEXT_ALIGNMENT alignment, int x_pos, int y_pos);

        SDL_Texture* get_Text_Texture(std::string text);

    private:        
        SDL_Rect m_glyphs[NUM_GLYPHS];
        SDL_Texture* m_glyph_atlas;

        TTF_Font* m_font_data;
        FONT_TYPE m_font_type;
        std::string m_font_path;
        int m_font_size;
        SDL_Color m_font_color;
        SDL_Renderer* m_renderer;

        void blit_Texture(SDL_Texture* texture, int x_pos, int y_pos);
        void draw_Rect(int x_pos, int y_pos, int width, int height, SDL_Color color);
        void draw_Outline_Rect(int x_pos, int y_pos, int width, int height, SDL_Color color);

        int get_Wrapped_Text_Height(std::string text, FONT_TYPE font_type, TEXT_ALIGNMENT alignment, int w);

        std::string get_Font_Path(FONT_TYPE font_type);
        SDL_Texture* to_Texture(SDL_Surface* sdl_surface, int destroy_surface);
};