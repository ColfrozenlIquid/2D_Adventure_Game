#pragma once
#include "widget.hpp"

class Widget_Slider : public Widget {
    public:
        Widget_Slider();
        ~Widget_Slider();

    private:
        int m_option_count;
        int m_current_option;
        std::vector<std::string> m_options_vec;
};