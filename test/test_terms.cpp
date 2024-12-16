#include "translator.h"

#include <gtest.h>
// тест терм

TEST(operand, can_create_operand)
{
    ASSERT_NO_THROW(operand a(6));
}

TEST(operand, can_get_value)
{
    operand a(6);
    EXPECT_EQ(a.getValue(), 6);
}

TEST(operation, can_create_operand)
{
    ASSERT_NO_THROW(operation a('+'));
}

TEST(operation, can_get_operation)
{
    operation a('+');
    EXPECT_EQ(a.getOperation(), '+');
}

TEST(operation, can_get_priority)
{
    operation a('+');
    EXPECT_EQ(a.getPriority(), 1);
}

TEST(open_bracket, can_create_open_bracket)
{
    ASSERT_NO_THROW(open_bracket t);
}

TEST(close_bracket, can_create_close_bracket)
{
    ASSERT_NO_THROW(close_bracket t);
}


TEST(close_bracket, can_get_operation)
{
    close_bracket t;
    EXPECT_EQ(t.getOperation(), ')');
}

TEST(open_bracket, can_get_operation)
{
    open_bracket t;
    EXPECT_EQ(t.getOperation(), '(');
}