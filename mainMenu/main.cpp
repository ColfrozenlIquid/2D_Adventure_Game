#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "menu.hpp"
#include "widget.hpp"

int main() {
    int renderer_Flags = SDL_RENDERER_ACCELERATED;
    int window_Flags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialise. SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window* m_window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, window_Flags);

    if (!m_window) {
        printf("failed to open %d x %d SDL window: %s\n", 800, 600, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_Renderer* m_renderer = SDL_CreateRenderer(m_window, -1, renderer_Flags);

    if (!m_renderer) {
        printf("Failed to create SDL renderer: %s", SDL_GetError());
        exit(1);
    }
    Menu menu;
    Widget widget1("widget_label", "widget_name", 100, 100);
    Widget widget2("widget_label2", "widget_name2", 200, 200);
    menu.add_Widget_To_Menu(widget1);
    menu.add_Widget_To_Menu(widget2);
    std::cout << "Menu size is: " << menu.get_Menu_Size() << std::endl;
    while (true) {
        menu.handle_Input();
        menu.check_Active_Widget();
        SDL_Delay(200);
    }
    return 0;
}