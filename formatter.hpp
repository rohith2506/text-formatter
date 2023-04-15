#pragma once

#include <string>
#include <queue>
#include "utils.hpp"

namespace formatter
{
    
enum Align {
    LEFT_ALIGN, 
    RIGHT_ALIGN, 
    CENTER_ALIGN,
	JUSTIFY
};

struct FormattedLine {
    size_t start_index;
    size_t end_index;
    size_t left_padding;
    size_t right_padding;
	std::deque<size_t> extra_spaces;

	FormattedLine() = delete;

	FormattedLine(
			size_t start_index, 
			size_t end_index, 
			size_t left_padding, 
			size_t right_padding, 
			std::deque<size_t> extra_spaces
	):
		start_index(start_index),
		end_index(end_index),
		left_padding(left_padding),
		right_padding(right_padding),
		extra_spaces(std::move(extra_spaces))
	{}
};

class Formatter {
public:
    std::string AlignText(const std::string& text, size_t column_width, const std::string& align_mode);
    Align GetAlignMode(const std::string& align_mode);
};

} // namespace formatter
