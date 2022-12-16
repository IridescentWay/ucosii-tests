#ifndef __PTHREAD_TESTS_H__
#define __PTHREAD_TESTS_H__

void test_pthread_setup();
void test_pthread_teardown();

void test_pthread_create();
void test_pthread_detach();
void test_pthread_join();
void test_pthread_cancel();
void test_pthread_testcancel();
void test_pthread_setcancelstate();
void test_pthread_setcanceltype();
void test_pthread_kill();
void test_pthread_equal();
void test_pthread_getschedparam();
void test_pthread_setschedparam();
void test_pthread_self();
void test_pthread_setschedprio();
void test_pthread_once();
void test_pthread_getcpuclockid();
void test_pthread_getconcurrency();
void test_pthread_setconcurrency();

#endif