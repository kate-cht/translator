#include "translator.h"

#include <gtest.h>
// тест транслятор

TEST(translator, can_get_expression)
{
    translator t("2+2");
    EXPECT_EQ(t.get_expression(), "2+2");
}

TEST(translator, throw_if_invalid_character)
{
    translator t("2+2!");
    ASSERT_ANY_THROW(t.parser());
}

TEST(translator, throw_if_invalid_character_2)
{
    translator t("");
    ASSERT_ANY_THROW(t.parser());
}

TEST(translator, no_throw_if_invalid_character)
{
    translator t("5+5*5");
    ASSERT_NO_THROW(t.parser());
}

TEST(translator, throw_if_syntaxis_analysis_first_close_bracket)
{
    translator t(")5+5");
    t.parser();
    ASSERT_ANY_THROW(t.syntax_analysis());
}

TEST(translator, throw_if_syntaxis_analysis_first_operation)
{
    translator t("-5+5");
    t.parser();
    ASSERT_ANY_THROW(t.syntax_analysis());
}


TEST(translator, throw_if_syntaxis_analysis_count_bracket)
{
    translator t("(5+5");
    t.parser();
    ASSERT_ANY_THROW(t.syntax_analysis());
}

TEST(translator, throw_syntaxis_analysis)
{
    translator t("5-+5");
    t.parser();
    ASSERT_ANY_THROW(t.syntax_analysis());
}

TEST(translator, throw_syntaxis_analysis_1)
{
    translator t("5+5");
    t.parser();
    ASSERT_NO_THROW(t.syntax_analysis());
}
TEST(translator, can_get_expressions)
{
    translator t("2+2*2");
    cout << endl << t.get_expression() << endl;
    t.parser();
    t.print_expression();
    EXPECT_EQ(t.get_expression(), "2+2*2");
}

TEST(translator, no_throw_converter)
{
    translator t("2+2*2");
    t.parser();
    ASSERT_NO_THROW(t.converter());
}


TEST(translator, no_throw_calculate)
{
    translator t("2+2*2");
    t.parser();
    t.syntax_analysis();
    t.print_expression();
    t.converter();
    t.print_polish();
    ASSERT_NO_THROW(t.calculate());
}

TEST(translator, correct_calculate)
{
    translator t("2+2*2");
    EXPECT_EQ(t.get_result(), 6);
}

TEST(translator, correct_calculate_exp_with_brackets)
{
    translator t("4+9*(5-2)");
    EXPECT_EQ(t.get_result(), 31);
}

TEST(translator, throw_with_div_zero)
{
    translator t("4+9/(5-5)");
    ASSERT_ANY_THROW(t.get_result());
}

TEST(translator, throw_exp_incorrec_breacket)
{
    translator t("4*7)+(9/(5-1)-1");
    ASSERT_ANY_THROW(t.get_result());
}