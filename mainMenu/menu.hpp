#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "widget.hpp"
#include "../fonts/font.hpp"
#include "../fonts/color.hpp"

#define ACTIVE_WIDGET_COLOR Color::BLUE

#define WIDGET_BOTTOM_PADDING 10

class Menu {
    public:
        Menu();
        ~Menu();
        void add_Widget_To_Menu(Widget& widget);
        void print_Menu();
        void check_Active_Widget();
        void handle_Input();
        void draw_Widgets(Font font, Font::TEXT_ALIGNMENT alignment);
        void print_Stats();
        int get_Widget_Count();
        void calculate_Menu_Dimensions(Font font);

    protected:
        int m_widget_count;
        int m_active_widget;
        std::vector<Widget> m_menu_widgets;

    private:
        int m_x_pos;
        int m_y_pos;
        int m_width;
        int m_height;

        void handle_Key_Up(SDL_KeyboardEvent* keyboard_event);
        void handle_Key_Down(SDL_KeyboardEvent* keyboard_event);
};