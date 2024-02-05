#include "menu.hpp"

Menu::Menu() {
    m_x_pos = 0;
    m_y_pos = 0;
    m_width = 0;
    m_height = 0;

    m_widget_count = 0;
    m_active_widget = 0;
}

Menu::~Menu() {}

void Menu::add_Widget_To_Menu(Widget& widget) {
    m_menu_widgets.push_back(widget);
    m_widget_count += 1;
}

void Menu::calculate_Menu_Dimensions(Font font) {
    int widget_relative_y_pos = 0;
    for (int i = 0; i < m_widget_count; i++) {
        int widget_width = 0;
        int widget_height = 0;

        TTF_SizeUTF8(font.get_Font_Data(), m_menu_widgets[i].get_Label().c_str(), &widget_width, &widget_height);
        m_menu_widgets[i].set_Width(widget_width);
        m_menu_widgets[i].set_Height(widget_height);
        m_menu_widgets[i].set_y_Pos(widget_relative_y_pos);

        widget_relative_y_pos += widget_height + WIDGET_BOTTOM_PADDING;

        if (widget_width > m_width) {
            m_width = widget_width;
        }
        if (i < m_widget_count - 1) {
            m_height += widget_height + WIDGET_BOTTOM_PADDING;
        }
        else {
            m_height += widget_height;
        }
    }
    m_x_pos = (SCREEN_WIDTH/2) - (m_width/2);
    m_y_pos = (SCREEN_HEIGHT/2) - (m_height/2);
}

void Menu::draw_Widgets(Font font, Font::TEXT_ALIGNMENT alignment) {
    for (int i = 0; i < m_widget_count; i++) {
        int y_pos = m_menu_widgets[i].get_y_Pos() + m_y_pos;
        if (i == m_active_widget) {
            //std::string label = "> " + m_menu_widgets[i].get_Label();
            font.draw_Text(m_menu_widgets[i].get_Label(), font.ENTER_COMMAND, Color::get_Color(Color::GREEN), alignment, m_x_pos, y_pos, 100);
        }
        else {
            font.draw_Text(m_menu_widgets[i].get_Label(), font.ENTER_COMMAND, Color::get_Color(Color::WHITE), alignment, m_x_pos, y_pos, 100);
        }
    }
}

void Menu::print_Stats() {
    std::cout << "Menu x pos: " << m_x_pos << std::endl;
    std::cout << "Menu y pos: " << m_y_pos << std::endl;
    std::cout << "Menu width: " << m_width << std::endl;
    std::cout << "Menu height: " << m_height << std::endl;
}

void Menu::print_Menu() {
    std::cout << "Current menu size is: " << m_widget_count << std::endl;
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
                handle_Key_Down(&event.key);
                break;
            case SDL_KEYUP:
                handle_Key_Up(&event.key);
                break;
            default:
                break;
        }
    }
}

void Menu::handle_Key_Down(SDL_KeyboardEvent* keyboard_event) {
    if (keyboard_event->repeat == 0) {
        if ((keyboard_event->keysym.scancode == SDL_SCANCODE_W) || (keyboard_event->keysym.scancode == SDL_SCANCODE_UP)) {
            if (m_widget_count != 1) {
                if (m_active_widget == 0) {
                    m_active_widget = m_widget_count;
                }
                if (m_active_widget > 0) {
                    m_active_widget -= 1;
                }
            }
            return;
        }
        if ((keyboard_event->keysym.scancode == SDL_SCANCODE_S) || (keyboard_event->keysym.scancode == SDL_SCANCODE_DOWN)) {
            if (m_widget_count != 1) {
                if (m_active_widget < m_widget_count) {
                    m_active_widget += 1;
                }
                if (m_active_widget == m_widget_count) {
                    m_active_widget = 0;
                }
            }
            return;
        }
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_SPACE || keyboard_event->keysym.scancode == SDL_SCANCODE_RETURN) {
            m_menu_widgets[m_active_widget].action();
            return;
        }
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_Q) {
            SDL_Quit();
            exit(0);
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

int Menu::get_Widget_Count() {
    return this->m_widget_count;
}