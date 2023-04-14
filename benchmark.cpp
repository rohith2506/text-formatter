#include <iostream>
#include <chrono>
#include <vector>
#include <random>

#include "formatter.hpp"

constexpr size_t MAX_WORD_SIZE = 100;
constexpr size_t COLUMN_WIDTH = 104;
const std::vector<int> NUM_WORDS = {1000, 10000, 100000, 1000000};
const std::vector<std::string> ALIGN_MODES = {"LEFT_ALIGN", "RIGHT_ALIGN", "CENTER_ALIGN"};

std::string generate_text(int length) {
    std::string result;

    while(length) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(97, 122);
        for (int i = 0; i < (rand() % MAX_WORD_SIZE) + 1; ++i) {
            result += static_cast<char>(dis(gen));
        }
        result += " ";
        length--;
    }
    result.pop_back();

    return result;
}

void run_benchmark() {
    formatter::Formatter text_formatter;

    for (size_t index = 0; index < NUM_WORDS.size(); index++) {
        std::cout << "Running benchmark: #" << index << std::endl;
        auto align_mode = ALIGN_MODES[(rand() % ALIGN_MODES.size()) + 1];
        std::cout << "TOTAL WORDS = " << NUM_WORDS[index] << "\tCOLUMN_WIDTH = " << COLUMN_WIDTH << "\tALIGN_MODE = " << align_mode << std::endl;

        std::string text = generate_text(NUM_WORDS[index]);

        auto stime = std::chrono::system_clock::now();
        auto result = text_formatter.AlignText(text, COLUMN_WIDTH, align_mode);
        auto etime = std::chrono::system_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(etime - stime).count();
        std::cout << "Time taken: " << duration << " us" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    run_benchmark();
    return EXIT_SUCCESS;
}