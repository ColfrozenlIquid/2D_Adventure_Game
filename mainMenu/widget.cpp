#include "widget.hpp"

Widget::Widget() {}

Widget::~Widget() {}

Widget::Widget(std::string label, std::string name) {
    m_label = label;
    m_name = name;
    m_prev_widget = this;
    m_next_widget = this;
}

void Widget::append_Widget(std::string label, std::string name) {
    Widget* widget;
    widget->m_label = label;
    widget->m_name = name;

    this->m_next_widget = widget;
    widget->m_prev_widget = this;
    widget->m_next_widget = nullptr;

}