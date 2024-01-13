#pragma once
#include <string>

class Widget {
    public:
        Widget();
        Widget(std::string label, std::string name, int x_pos, int y_pos);
        ~Widget();

        std::string get_Name();
        std::string get_Label();
        int get_x_Pos();
        int get_y_Pos();

    private:
        std::string m_name;
        std::string m_label;
        int m_x_pos;
        int m_y_pos;
};