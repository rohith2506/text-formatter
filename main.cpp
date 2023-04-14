#include <iostream>
#include <chrono>

#include "formatter.hpp"

struct ProgramOptions {
    std::string text;
    size_t column_width;
    std::string align_mode;
};

ProgramOptions parse_options(int argc, char* argv[]) {
    if (argc != 4) {
        throw std::runtime_error("Usage: align_text <text> <column_width> <align_mode>");
    }
    // Parse the text argument
    std::string text = argv[1];
    // Parse the column width argument
    size_t column_width;
    std::stringstream column_width_ss(argv[2]);
    if (!(column_width_ss >> column_width) || column_width <= 0) {
        throw std::runtime_error("Invalid column width argument: " + std::string(argv[2]));
    }
    // Parse the alignment mode argument
    std::string align_mode = argv[3];
    // Parse the alignment mode argument
    std::string align_mode_str = argv[3];
    return {text, column_width, align_mode};    
}

int main(int argc, char* argv[]) {
    try {
        auto&& [text, column_width, align_mode] = parse_options(argc, argv);
        formatter::Formatter text_formatter;
        std::string result = text_formatter.AlignText(text, column_width, align_mode);
        std::cout << result << std::endl;
    } catch(const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}