#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "application.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "player.hpp"
#include "devil.hpp"
#include "chest.hpp"
#include "cat.hpp"
#include "demon.hpp"
#include "mainMenu/menu.hpp"
#include "mainMenu/widget.hpp"
#include "./fonts/font.hpp"
#include "./fonts/color.hpp"

#define MOVEMENT_SPEED 4
#define FONT_SIZE_MENU 80
#define FONT_SIZE_GAME 30

void main_menu(Application main_Application, SDL_Renderer* main_Renderer);
void game(Application main_Application, SDL_Renderer* main_Renderer);

enum GAME_STATE {
    MAIN_MENU,
    GAME
};

int main() {
    GAME_STATE game_state = MAIN_MENU;
    Application main_Application;
    SDL_Renderer* main_Renderer = main_Application.m_renderer;
    int running = 1;

    switch (game_state) {
        case MAIN_MENU:
            main_menu(main_Application, main_Renderer);
            break;
        case GAME:
            game(main_Application, main_Renderer);
        default:
            break;
    }

    SDL_Quit();
    return 0;
}

void main_menu(Application main_Application, SDL_Renderer* main_Renderer) {
    Menu main_menu;
    SDL_Color font_color = Color::get_Color(Color::LIGHT_BLUE);
    Font font(main_Renderer, Font::FONT_TYPE::ENTER_COMMAND, FONT_SIZE_MENU, font_color);
    
    Widget widget1("Start", "widget_name1");
    Widget widget2("Load", "widget_name2");
    Widget widget3("Options", "widget_name3");
    Widget widget4("Credits", "widget_name4");
    Widget widget5("Exit", "widget_name5");
    main_menu.add_Widget_To_Menu(widget1);
    main_menu.add_Widget_To_Menu(widget2);
    main_menu.add_Widget_To_Menu(widget3);
    main_menu.add_Widget_To_Menu(widget4);
    main_menu.add_Widget_To_Menu(widget5);
    main_menu.calculate_Menu_Dimensions(font);

    while (true) {
        main_Application.prepare_Scene();
        main_menu.handle_Input();
        main_menu.draw_Widgets(font, Font::TEXT_ALIGN_LEFT);
        main_Application.present_Scene();
        SDL_Delay(32);
    }
}

void game(Application main_Application, SDL_Renderer* main_Renderer) {
    Player player_entity(main_Renderer);
    Devil devil_entity(main_Renderer);
    Demon demon_entity(main_Renderer);
    Chest chest_entity(main_Renderer);
    Cat cat_entity(main_Renderer);

    Map map(main_Renderer);

    SDL_Color font_color = Color::get_Color(Color::WHITE);

    Font font(main_Renderer, Font::FONT_TYPE::ENTER_COMMAND, FONT_SIZE_GAME, font_color);

    std::string sample_text = "One morning, when Gregor Samsa woke from troubled dreams, he found himself transformed in his bed into a horrible vermin. He lay on his armour-like back, and if he lifted his head a little he could see his brown belly, slightly domed and divided by arches into stiff sections.";
    std::string sample_text2 = "Than of your graces and your gifts to tell; Which borrowed from this holy fire of Love, That they elsewhere might dart their injuries: I do believe her though I know she lies,";

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
            map.update_camera_y_position(-MOVEMENT_SPEED);
        }
        else if (direction == Player_Movement_Direction::DOWN) {
            player_entity.move_Entity_Vertical(MOVEMENT_SPEED);
            map.update_camera_y_position(MOVEMENT_SPEED);
        }
        else if (direction == Player_Movement_Direction::LEFT) {
            player_entity.move_Entity_Horizontal(-MOVEMENT_SPEED);
            player_entity.set_Entity_Facing(Facing_Direction::FACE_LEFT);
            map.update_camera_x_position(-MOVEMENT_SPEED);
        }
        else if (direction == Player_Movement_Direction::RIGHT) {
            player_entity.move_Entity_Horizontal(MOVEMENT_SPEED);
            player_entity.set_Entity_Facing(Facing_Direction::FACE_RIGHT);
            map.update_camera_x_position(MOVEMENT_SPEED);
        }

        //font.draw_Text("Hello World", Font::FONT_TYPE::ENTER_COMMAND, font_color, 100, 300);
        
        font.draw_Boxed_Text(sample_text, font_color, Color::get_Color(Color::DARK_GRAY), Font::TEXT_ALIGNMENT::TEXT_ALIGN_LEFT, 100, 300);
        font.draw_Boxed_Text(sample_text2, font_color, Color::get_Color(Color::DARK_GRAY), Font::TEXT_ALIGNMENT::TEXT_ALIGN_LEFT, 600, 200);

        player_entity.blit_Texture(player_entity.get_Entity_x_pos(), player_entity.get_Entity_y_pos());
        devil_entity.blit_Texture(devil_entity.get_Entity_x_pos(), devil_entity.get_Entity_y_pos());
        chest_entity.blit_Texture(chest_entity.get_Entity_x_pos(), chest_entity.get_Entity_y_pos());
        cat_entity.blit_Texture(cat_entity.get_Entity_x_pos(), cat_entity.get_Entity_y_pos());
        demon_entity.blit_Texture(demon_entity.get_Entity_x_pos(), demon_entity.get_Entity_y_pos());

        main_Application.present_Scene();
        SDL_Delay(16);
    }
}