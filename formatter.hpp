#pragma once

#include <string>
#include "utils.hpp"

namespace formatter
{
    
enum Align {
    LEFT_ALIGN, 
    RIGHT_ALIGN, 
    CENTER_ALIGN
};

struct FormattedLine {
    size_t start_index;
    size_t end_index;
    size_t left_padding;
    size_t right_padding;
};

class Formatter {
public:
    std::string AlignText(const std::string& text, size_t column_width, const std::string& align_mode);
    Align GetAlignMode(const std::string& align_mode);
};

} // namespace formatter
