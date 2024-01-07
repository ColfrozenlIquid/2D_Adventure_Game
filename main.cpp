#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "application.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "player.hpp"
#include "devil.hpp"
#include "chest.hpp"
#include "cat.hpp"

#define MOVEMENT_SPEED 4

int main() {
    Application main_Application;
    SDL_Renderer* main_Renderer = main_Application.m_renderer;
    std::cout << "Main renderer address: " << main_Renderer << std::endl;
    Player player_entity(main_Renderer);
    Devil devil_entity(main_Renderer);
    Chest chest_entity(main_Renderer);
    Cat cat_entity(main_Renderer);
    //Entity devil_entity(main_Renderer, Character::DEVIL, 500, 500);
    Map map(main_Renderer);

    while (true) {
        uint32_t animation_speed = SDL_GetTicks() / 175;
        int idx = animation_speed % CAT_ANIMATION_FRAMES;
        main_Application.prepare_Scene();
        map.draw_Map();
        main_Application.handle_Input();
        cat_entity.set_Animation_State(idx);
        Player_Movement_Direction direction = main_Application.get_Player_Movement_Direction();

        if (direction == Player_Movement_Direction::UP) {
            player_entity.move_Entity_Vertical(-MOVEMENT_SPEED);
        }
        if (direction == Player_Movement_Direction::DOWN) {
            player_entity.move_Entity_Vertical(MOVEMENT_SPEED);
        }
        if (direction == Player_Movement_Direction::LEFT) {
            player_entity.move_Entity_Horizontal(-MOVEMENT_SPEED);
            player_entity.set_Entity_Facing(Facing_Direction::FACE_LEFT);
        }
        if (direction == Player_Movement_Direction::RIGHT) {
            player_entity.move_Entity_Horizontal(MOVEMENT_SPEED);
            player_entity.set_Entity_Facing(Facing_Direction::FACE_RIGHT);
        }

        player_entity.blit_Texture(player_entity.get_Entity_x_pos(), player_entity.get_Entity_y_pos());
        devil_entity.blit_Texture(devil_entity.get_Entity_x_pos(), devil_entity.get_Entity_y_pos());
        chest_entity.blit_Texture(chest_entity.get_Entity_x_pos(), chest_entity.get_Entity_y_pos());
        cat_entity.blit_Texture(cat_entity.get_Entity_x_pos(), cat_entity.get_Entity_y_pos());
        //devil_entity.blit_Texture(devil_entity.get_Entity_x_pos(), devil_entity.get_Entity_y_pos());
        main_Application.present_Scene();
        SDL_Delay(16);
    }

    SDL_Quit();

    return 0;
}