#include <string>
#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"
#include "formatter.hpp"

TEST_CASE("left-align-text") {
    formatter::Formatter text_formatter;
    std::string line = "This test should be left aligned";

    std::string aligned_text = text_formatter.AlignText(line, 10, "LEFT_ALIGN");
    std::string expected_text = "This test\n"
                                "should be\n"
                                "left\n"
                                "aligned";
    REQUIRE(aligned_text == expected_text);

    aligned_text = text_formatter.AlignText(line, 20, "LEFT_ALIGN");
    expected_text = 
            "This test should be\n"
            "left aligned";
    REQUIRE(aligned_text == expected_text);
}

TEST_CASE("right-align-text") {
    formatter::Formatter text_formatter;

    std::string line = "This test should be right aligned";
    std::string aligned_text = text_formatter.AlignText(line, 10, "RIGHT_ALIGN");
    std::string expected_text = " This test\n"
                                " should be\n"
                                "     right\n"
                                "   aligned";
    REQUIRE(aligned_text == expected_text);

    aligned_text = text_formatter.AlignText(line, 20, "RIGHT_ALIGN");
    expected_text = " This test should be\n"
                    "       right aligned";
    REQUIRE(aligned_text == expected_text);
}

TEST_CASE("center-align-text") {
    formatter::Formatter text_formatter;

    std::string line = "This test should be center aligned";
    std::string aligned_text = text_formatter.AlignText(line, 10, "CENTER_ALIGN");
    std::string expected_text = "This test \n"
                                "should be \n"
                                "  center  \n"
                                " aligned  ";
    REQUIRE(aligned_text == expected_text);

    aligned_text = text_formatter.AlignText(line, 20, "CENTER_ALIGN");
    expected_text = "This test should be \n"
                    "   center aligned   ";
    REQUIRE(aligned_text == expected_text);

    line = "hello world hello world hello world";
    aligned_text = text_formatter.AlignText(line, 20, "CENTER_ALIGN");
    expected_text = " hello world hello  \n"
        " world hello world  ";
    REQUIRE(aligned_text == expected_text);
}

TEST_CASE("empty-text") {
    formatter::Formatter text_formatter;
    std::string line = "";
    std::string aligned_text = text_formatter.AlignText(line, 3, "LEFT_ALIGN");
    std::string expected_text = "";
    REQUIRE(aligned_text == expected_text);
}

TEST_CASE("words-length-equal-to-column-width") {
    formatter::Formatter text_formatter;
    std::string line = "brown hello paper";
    std::string aligned_text = text_formatter.AlignText(line, 5, "CENTER_ALIGN");
    std::string expected_text = "brown\nhello\npaper";
    REQUIRE(aligned_text == expected_text);

    aligned_text = text_formatter.AlignText(line, 5, "RIGHT_ALIGN");
    expected_text = "brown\nhello\npaper";
    REQUIRE(aligned_text == expected_text);
}

TEST_CASE("non-ascii-characters") {
    formatter::Formatter text_formatter;
    std::string line = "Voilà, c'est fini";
    std::string aligned_text = text_formatter.AlignText(line, 3, "LEFT_ALIGN");
    std::string expected_text = "";
    REQUIRE(aligned_text == expected_text);
}

TEST_CASE("words-longer-than-column-width") {
    formatter::Formatter text_formatter;
    std::string line = "Supercalifragilisticexpialidocious";
    std::string aligned_text = text_formatter.AlignText(line, 10, "LEFT_ALIGN");
    std::string expected_text = "";
    REQUIRE(aligned_text == expected_text);
}

TEST_CASE("mix-case-text") {
    formatter::Formatter text_formatter;
    std::string line = "ThE QuIcK BrOWn fOx jUmPs oVeR ThE LaZy dOg";
    std::string aligned_text = text_formatter.AlignText(line, 20, "RIGHT_ALIGN");
    std::string expected_text =
        " ThE QuIcK BrOWn fOx\n"
        " jUmPs oVeR ThE LaZy\n"
        "                 dOg";
    REQUIRE(aligned_text == expected_text);
}

/*
In order to compare the correctness, we took the google docs output and compare
that with the program output and it matched
*/
TEST_CASE("google-docs-a5-page-format") {
    formatter::Formatter text_formatter;
    std::string line = "the fox likes to wander in the forest during the night "
        "and sometimes when it sees a tiger it makes its best attempt to hide away "
        "and then once the danger is gone it goes back to its resting place";
    
    std::string aligned_text = text_formatter.AlignText(line, 76, "CENTER_ALIGN");
    std::string expected_text = 
        "the fox likes to wander in the forest during the night and sometimes when it\n"
        "sees a tiger it makes its best attempt to hide away and then once the danger\n"
        "                 is gone it goes back to its resting place                  ";
    REQUIRE(aligned_text == expected_text);
}

TEST_CASE("google-docs-statement-page-format") {
    formatter::Formatter text_formatter;
    std::string line = "the fox likes to wander in thou forest during the night "
        "and sometimes when it sees a tiger it makes its best attempt to hide away "
        "and then once the danger is gone it goes back to its resting kingdom";
    
    std::string aligned_text = text_formatter.AlignText(line, 30, "CENTER_ALIGN");
    std::string expected_text = 
        "  the fox likes to wander in  \n"
        " thou forest during the night \n"
        " and sometimes when it sees a \n"
        "   tiger it makes its best    \n"
        "attempt to hide away and then \n"
        "  once the danger is gone it  \n"
        "   goes back to its resting   \n"
        "           kingdom            ";
    REQUIRE(aligned_text == expected_text);
}
