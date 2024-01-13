#include "widget.hpp"

Widget::Widget() {}

Widget::~Widget() {}

//Widget(label, name, x_pos, y_pos)
Widget::Widget(std::string label, std::string name, int x_pos, int y_pos) {
    m_label = label;
    m_name = name;
    m_x_pos = x_pos;
    m_y_pos = y_pos;
}

std::string Widget::get_Name() {
    return this->m_name;
}

std::string Widget::get_Label() {
    return this->m_label;
}

int Widget::get_x_Pos() {
    return this->m_x_pos;
}

int Widget::get_y_Pos() {
    return this->m_y_pos;
}