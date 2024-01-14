#include "widget.hpp"

Widget::Widget() {}

Widget::~Widget() {}

Widget::Widget(std::string label, std::string name) {
    m_label = label;
    m_name = name;
    m_x_pos = 0;
    m_y_pos = 0;
}

void Widget::set_x_Pos(int x_pos) {
    this->m_x_pos = x_pos;
}

void Widget::set_y_Pos(int y_pos) {
    this->m_y_pos = y_pos;
}

void Widget::set_Width(int width) {
    this->m_width = width;
}

void Widget::set_Height(int height){
    this->m_height = height;
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