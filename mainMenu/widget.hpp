#pragma once
#include <string>

class Widget {
    public:
        Widget();
        Widget(std::string label, std::string name);
        ~Widget();

        void append_Widget(std::string label, std::string name);

        void set_Name(std::string name);
        void set_Label(std::string label);
        void set_X_Pos(int x_pos);
        void set_Y_Pos(int y_pos);
        void set_Prev_Widget(Widget* widget);
        void set_Next_Widget(Widget* widget);

    private:
        std::string m_name;
        std::string m_label;
        int m_x_pos;
        int m_y_pos;
        Widget* m_prev_widget;
        Widget* m_next_widget;
};