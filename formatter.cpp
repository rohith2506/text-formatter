#include <vector>
#include <iostream>

#include "formatter.hpp"

namespace formatter
{

Align Formatter::GetAlignMode(const std::string& align_mode) {
    if (align_mode == "LEFT_ALIGN") {
        return Align::LEFT_ALIGN;
    } else if (align_mode == "RIGHT_ALIGN") {
        return Align::RIGHT_ALIGN;
    } else if (align_mode == "CENTER_ALIGN") {
        return Align::CENTER_ALIGN;
	} else if (align_mode == "JUSTIFY") {
		return Align::JUSTIFY;
	} else {
        throw std::invalid_argument("Align mode \"" + align_mode + "\" is not currently supported");
    }
}

std::string Formatter::AlignText(const std::string& text, size_t column_width, const std::string& align_mode) {
    if (!formatter_utils::IsValid(text)) {
        std::cerr << "Error: Invalid text input. No characters apart from lowercase ASCII or uppercase ASCII or spaces is allowed" << std::endl;
        return "";
    }
    if (!text.length()) {
        std::cerr << "Error: Empty input" << std::endl;
        return "";
    }
    
    std::vector<std::string> words = formatter_utils::SplitString(text);
    std::vector<FormattedLine> lines;

    auto const construct = [this, &lines, &words, &column_width, &align_mode](size_t start_index, size_t end_index, size_t current_line_length) {
        switch (GetAlignMode(align_mode)) {
            case Align::LEFT_ALIGN:
            {
                lines.emplace_back(FormattedLine{start_index, end_index, 0, 0, {}});
                break;
            };
            case Align::RIGHT_ALIGN:
            {
                auto padding_length = std::max(0ul, column_width - current_line_length + 1);
                lines.emplace_back(FormattedLine{start_index, end_index, padding_length, 0, {}});
                break;
            };
            case Align::CENTER_ALIGN:
            {
                auto padding_length = std::max(0ul, column_width - current_line_length + 1);
                // For uneven padding length, Keep the text more left aligned than right aligned
                auto left_padding_length = padding_length / 2;
                auto right_padding_length = padding_length - left_padding_length;
                lines.emplace_back(FormattedLine{start_index, end_index, left_padding_length, right_padding_length, {}});
				break;
			};
            case Align::JUSTIFY:
            {
                int64_t padding_length = std::max(0ul, column_width - current_line_length + 1);
                auto num_words = (end_index - start_index - 1);
                if (!num_words || end_index == words.size()) {
                    lines.emplace_back(FormattedLine{start_index, end_index, 0, 0, {}});	
                }
                else {
                    auto padding_distribution =  (size_t)ceil(padding_length * 1.0 / (end_index - start_index - 1));	
                    std::deque<size_t> extra_spaces;
                    while (padding_length > 0) {
                        extra_spaces.push_back(std::min(padding_length, (int64_t)padding_distribution));
                        padding_length -= padding_distribution;
                    }
                    lines.emplace_back(FormattedLine{start_index, end_index, 0, 0, extra_spaces});
                }
                break;	
            }
        }
    };

    size_t start_index = 0, current_line_length = 0;
    for (size_t end_index = 0; end_index < words.size(); end_index++) {
        const auto& word = words[end_index];
        // If the word is longer than column width, print error to STDERR
        if (word.length() > column_width) {
            std::cerr << "Error: current word \"" << word << "\" is longer than column width (" << column_width << ")" << std::endl;
            return "";  
        }
        if (current_line_length + word.length() > column_width) {
            construct(start_index, end_index, current_line_length);
            current_line_length = word.length() + 1;
            start_index = end_index;
        }
        else {
            current_line_length += word.length() + 1;
        }
    }
    if (current_line_length) {
        construct(start_index, words.size(), current_line_length);
    }

    std::string result;
    for (auto& [start_index, end_index, left_padding, right_padding, extra_spaces] : lines) {
        result += std::string(left_padding, ' ');
        for (auto index = start_index; index < end_index; index++) {
            result += words[index];
            result += ' ';
            if (extra_spaces.size()) {
                result += std::string(extra_spaces.front(), ' ');
                extra_spaces.pop_front();
            }
        }
        result.pop_back();
        result += std::string(right_padding, ' ');
        result += "\n";
    }
    result.pop_back();

    return result;
}

} // namespace formatter

