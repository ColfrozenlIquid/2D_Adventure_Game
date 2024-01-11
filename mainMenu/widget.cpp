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

void Widget::set_Name(std::string name) {
    this->m_name = name;
}

void Widget::set_Label(std::string label) {
    this->m_label = label;
}

void Widget::set_X_Pos(int x_pos) {
    this->m_x_pos = x_pos;
}

void Widget::set_Y_Pos(int y_pos) {
    this->m_y_pos = y_pos;
}

void Widget::set_Prev_Widget(Widget* widget) {
    this->m_prev_widget = widget;
}

void Widget::set_Next_Widget(Widget* widget) {
    this->m_next_widget = widget;
}