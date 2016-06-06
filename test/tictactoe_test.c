#include <unity/unity.h>
#include "tictactoe.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_tictactoe(void)
{
	TEST_ASSERT_EQUAL_INT(42, tictactoe());
}