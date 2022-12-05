#include "CppUTest/TestHarness.h"
extern "C" {
	#include "face_pthread.h"
}

void* task1_func(void* p_arg)
{

	return 0;
}

void* task2_func(void* p_arg)
{
	int res = pthread_detach(pthread_self());
	LONGS_EQUAL(0, res);
	return 0;
}

TEST_GROUP(PthreadTests)
{
	void setup()
	{
		OSInit();
		// OSStart();
	}
};

TEST(PthreadTests, PthreadCreateNormalOperation)
{
	pthread_t thread;
	int res = pthread_create(&thread, (const pthread_attr_t*) NULL, task1_func, NULL);
	LONGS_EQUAL_TEXT(0, res, "Will pthread_create success?");
}

TEST(PthreadTests, PthreadCreateLackResources)
{
	// 未实现PTHREAD_THREADS_MAX
}

TEST(PthreadTests, PthreadDetachNormalOperation)
{
	pthread_t thread;
	pthread_create(&thread, (const pthread_attr_t*) NULL, task2_func, NULL);
}

TEST(PthreadTests, PthreadDetachUnjoinableThread)
{
	// 需创建一个unjoinnalbe thread，或许没实现？
}

TEST(PthreadTests, PthreadDetachTerminatedThread)
{
	pthread_t thread;
	pthread_create(&thread, (const pthread_attr_t*)NULL, task1_func, NULL);
	// pthread_join(thread, NULL); 未实现？
	OSStart();    // 必须用OSStart才能调用uc的sleep，调用了就编译不了
	sleep(1);    // 替代pthread_join等待线程结束
	int res = pthread_detach(thread);
	LONGS_EQUAL_TEXT(ESRCH, res, "terminated thread shall not be detached!");
}

TEST(PthreadTests, PthreadJoinNormalOperation)
{
	// 未实现
}