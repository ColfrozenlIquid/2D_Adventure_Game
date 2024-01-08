#pragma once
#include "widget.hpp"

class Menu {
    public:
        Menu();
        ~Menu();
        void append_Widget(std::string label, std::string name);

    private:
        Widget* m_active_widget;
        Widget* m_widget_tail;
        Widget* m_widget_head;
};