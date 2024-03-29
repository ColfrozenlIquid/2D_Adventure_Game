#pragma once
#include <string>
#include <iostream>
#include <vector>

enum WIDGET_TYPE {
    SELECT,
    SLIDER,
    INPUT,
    CONTROL
};

class Widget {

    public:
        Widget();
        Widget(std::string label, std::string name);
        ~Widget();

        std::string get_Name();
        std::string get_Label();
        int get_x_Pos();
        int get_y_Pos();

        void set_x_Pos(int x_pos);
        void set_y_Pos(int y_pos);
        void set_Width(int width);
        void set_Height(int height);

        void action();

    private:
        std::string m_name;
        std::string m_label;
        int m_x_pos;
        int m_y_pos;
        int m_width;
        int m_height;
        WIDGET_TYPE m_widget_type;
};