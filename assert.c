#include "asserts.h"
#include <stdlib.h>
#include <string.h>

void assert_long_equal(const long expected, const long actual, const char *file, const int line)
{
	test_fail(expected != actual, file, line);
}

void assert_string_equal(const char *expected, const char *actual, const char *file, const int line)
{
	test_fail(strcmp(expected, actual) != 0, file, line);
}

void check(const int actual, const char *file, const int line)
{
	test_fail(!actual, file, line);
}

void test_fail(int condition, const char* file, const int line)
{
	if (condition) {
		printf("Test failed in file: %s, line: %d\n", file, line);
		system("pause");
	}
}