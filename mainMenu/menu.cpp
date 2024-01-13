#include "menu.hpp"

Menu::Menu() {
    m_menu_size = 0;
    m_active_widget = 0;
}

Menu::~Menu() {}

void Menu::add_Widget_To_Menu(Widget& widget) {
    m_menu_widgets.push_back(widget);
    m_menu_size += 1;
}

void Menu::print_Menu() {
    std::cout << "Current menu size is: " << m_menu_size << std::endl;
    int count = 0;
    for (Widget widget : m_menu_widgets) {
        std::cout << "Current widget address: " << &widget << std::endl;
        std::cout << "Label: " << widget.get_Label() << std::endl;
        std::cout << "Name: " << widget.get_Name() << std::endl;
        std::cout << "x Pos: " << widget.get_x_Pos() << std::endl;
        std::cout << "y Pos: " << widget.get_y_Pos() << std::endl;
    }
}

void Menu::handle_Input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                std::cout << "Registered key down event" << std::endl;
                handle_Key_Down(&event.key);
                break;
            case SDL_KEYUP:
                std::cout << "Registered key up event" << std::endl;
                handle_Key_Up(&event.key);
                break;
            default:
                break;
        }
    }
}

void Menu::handle_Key_Down(SDL_KeyboardEvent* keyboard_event) {
    if (keyboard_event->repeat == 0) {
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_W) {
            std::cout << "Pressed key up" << std::endl;
            if (m_menu_size != 1) {
                if (m_active_widget > 0) {
                    m_active_widget -= 1;
                    std::cout << "Moved current up" << std::endl;
                }
                if (m_active_widget == 0) {
                    m_active_widget = m_menu_size-1;
                    std::cout << "Looped around" << std::endl;
                }
            }
        }
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_S) {
            std::cout << "Pressed key down" << std::endl;
            if (m_menu_size != 1) {
                if (m_active_widget < m_menu_size-1) {
                    m_active_widget -= 1;
                    std::cout << "Moved current down" << std::endl;
                }
                if (m_active_widget == m_menu_size-1) {
                    m_active_widget = 0;
                    std::cout << "Looped around" << std::endl;
                }
            }
        }
    }
}

void Menu::handle_Key_Up(SDL_KeyboardEvent* keyboard_event) {

}

void Menu::check_Active_Widget() {
    int count = 0;
    for (Widget widget : m_menu_widgets) {
        if (count == m_active_widget) {
            std::cout << ">> ";
        }
        std::cout << widget.get_Label() << std::endl;
        count++;
    }
}

int Menu::get_Menu_Size() {
    return this->m_menu_size;
}