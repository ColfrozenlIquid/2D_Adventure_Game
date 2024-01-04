#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "application.hpp"
#include "entity.hpp"

#define PLAYER_START_X 100
#define PLAYER_START_Y 100

int main() {
    Application main_Application;
    SDL_Renderer* main_Renderer = main_Application.get_SDL_Renderer();
    Entity player_entity(main_Renderer);

    while (true) {
        main_Application.prepare_Scene();
        main_Application.handle_Input();
        player_entity.blit_Texture(PLAYER_START_X, PLAYER_START_Y);
        main_Application.present_Scene();
        SDL_Delay(16);
    }

    SDL_Quit();

    return 0;
}