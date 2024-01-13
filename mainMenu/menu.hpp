#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "widget.hpp"

class Menu {
    public:
        Menu();
        ~Menu();
        void add_Widget_To_Menu(Widget& widget);
        void print_Menu();
        void check_Active_Widget();
        void handle_Input();

        void handle_Key_Up(SDL_KeyboardEvent* keyboard_event);
        void handle_Key_Down(SDL_KeyboardEvent* keyboard_event);

        int get_Menu_Size();

    protected:
        int m_menu_size;
        int m_active_widget;
        std::vector<Widget> m_menu_widgets;

    private:
};