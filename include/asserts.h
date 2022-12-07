#ifndef __ASSERT_H__
#define __ASSERT_H__

#define ASSERT_LONG_EQUAL(expected, actual) assert_long_equal(expected, actual, __FILE__, __LINE__)
#define ASSERT_STRING_EQUAL(expected, actual) assert_string_equal(expected, actual, __FILE__, __LINE__)
#define CHECK(actual) check(actual, __FILE__, __LINE__)

void assert_long_equal(const long expected, const long actual, const char *file, const int line);
void assert_string_equal(const char *expected, const char *actual, const char *file, const int line);

void check(const int actual, const char *file, const int line);


void test_fail(int condition, const char* file, const int line);

#endif