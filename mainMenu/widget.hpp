#pragma once
#include <string>

class Widget {
    public:
        Widget();
        Widget(std::string label, std::string name);
        ~Widget();

    private:
        std::string name;
        std::string label;
        int x_pos;
        int y_pos;
        Widget* prev_widget;
        Widget* next_widget;
};