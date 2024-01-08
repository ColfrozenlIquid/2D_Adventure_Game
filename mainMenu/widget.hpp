#pragma once
#include <string>

class Widget {
    public:
        Widget();
        Widget(std::string label, std::string name);
        ~Widget();

        void append_Widget(std::string label, std::string name);

    private:
        std::string m_name;
        std::string m_label;
        int m_x_pos;
        int m_y_pos;
        Widget* m_prev_widget;
        Widget* m_next_widget;
};