#include "menu.hpp"

Menu::Menu() {}

Menu::~Menu() {}

Menu::append_Widget(std::string label, std::string name) {
    Widget* widget;

    widget->set_Label(label);
    widget->set_Name(name);
    this.
    
    widget->m_label = label;
    widget->m_name = name;

    this->m_next_widget = widget;
    widget->m_prev_widget = this;
    widget->m_next_widget = nullptr;
}