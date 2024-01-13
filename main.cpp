#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "application.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "player.hpp"
#include "devil.hpp"
#include "chest.hpp"
#include "cat.hpp"
#include "mainMenu/menu.hpp"
#include "mainMenu/widget.hpp"
#include "./fonts/font.hpp"

#define MOVEMENT_SPEED 4
#define FONT_SIZE 100

int main() {
    Application main_Application;
    SDL_Renderer* main_Renderer = main_Application.m_renderer;
    std::cout << "Main renderer address: " << main_Renderer << std::endl;
    Player player_entity(main_Renderer);
    Devil devil_entity(main_Renderer);
    Chest chest_entity(main_Renderer);
    Cat cat_entity(main_Renderer);

    Map map(main_Renderer);

    Menu main_menu;
    Widget widget1("label1", "name1", 100, 100);
    main_menu.add_Widget_To_Menu(widget1);

    SDL_Color font_color;
    font_color.r = 255;
    font_color.g = 255;
    font_color.b = 255;
    font_color.a = 255;
    std::cout << "Gets here" << std::endl;

    Font font(main_Renderer, Font::FONT_TYPE::ENTER_COMMAND, FONT_SIZE, font_color);

    SDL_Texture* text1 = font.get_Text_Texture("Sample text");
    std::cout << "Text1 address is: " << text1 << std::endl;

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

        font.draw_Text("Hello World", Font::FONT_TYPE::ENTER_COMMAND, font_color, 100, 300);
        
        player_entity.blit_Texture(player_entity.get_Entity_x_pos(), player_entity.get_Entity_y_pos());
        devil_entity.blit_Texture(devil_entity.get_Entity_x_pos(), devil_entity.get_Entity_y_pos());
        chest_entity.blit_Texture(chest_entity.get_Entity_x_pos(), chest_entity.get_Entity_y_pos());
        cat_entity.blit_Texture(cat_entity.get_Entity_x_pos(), cat_entity.get_Entity_y_pos());

        main_Application.present_Scene();
        SDL_Delay(16);
    }

    SDL_Quit();

    return 0;
}