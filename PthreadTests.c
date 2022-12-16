#include "asserts.h"
#include "face_errno.h"
#include "face_pthread.h"

pthread_t *thread1, *thread2, *thread3, *thread4, *thread5, *thread6;
pthread_attr_t *attr1, *attr2, *attr3, *attr4, *attr5, *attr6;
// pthread_key_t key;	未实现，无法测试线程退出时私有数据状态

void* task1_func()
{
	printf("executing task1 ......\n");
	while (1) {
		printf("task1 still running ......\n");
		sleep(1);
	}
	
}

void* routine1(void* p_arg)
{
	printf("routine executed ......\n");
}

void* task2_func()
{
	pthread_cleanup_push(routine1, 0);
	printf("executing task2 ......\n");
	printf("executing task2 ......\n");
	printf("executing task2 ......\n");

	sleep(3);

	printf("executing task2 ......\n");
	printf("executing task2 ......\n");
	printf("executing task2 ......\n");
	pthread_cleanup_pop(0);	// 测试在 sleep 时就把线程取消了，不应该执行到此处，这样写只是为了 posix 文档中 push 和 pop 需成对执行
}

void* task3_func()
{
	int oldstate;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
	char* oldstate_text;
	if (oldstate == PTHREAD_CANCEL_ENABLE)
		oldstate_text = "cancellable";
	else if (oldstate == PTHREAD_CANCEL_DISABLE)
		oldstate_text = "uncancellable";
	else
		oldstate_text = "unknown";
	printf("executing task3 ... set uncancellable, oldstate is %s\n", oldstate_text);
	sleep(3);
	printf("executing task3 ......");

}

void test_pthread_setup()
{
	thread1 = (pthread_t*)malloc(sizeof(pthread_t));
	thread2 = (pthread_t*)malloc(sizeof(pthread_t));
	thread3 = (pthread_t*)malloc(sizeof(pthread_t));
	thread4 = (pthread_t*)malloc(sizeof(pthread_t));
	thread5 = (pthread_t*)malloc(sizeof(pthread_t));
	thread6 = (pthread_t*)malloc(sizeof(pthread_t));
	attr1 = (pthread_attr_t*)malloc(sizeof(pthread_attr_t));
	attr2 = (pthread_attr_t*)malloc(sizeof(pthread_attr_t));
	attr3 = (pthread_attr_t*)malloc(sizeof(pthread_attr_t));
	attr4 = (pthread_attr_t*)malloc(sizeof(pthread_attr_t));
	attr5 = (pthread_attr_t*)malloc(sizeof(pthread_attr_t));
	attr6 = (pthread_attr_t*)malloc(sizeof(pthread_attr_t));
	pthread_attr_init(attr1);
	pthread_attr_init(attr2);
	pthread_attr_init(attr3);
	pthread_attr_init(attr4);
	pthread_attr_init(attr5);
	pthread_attr_init(attr6);
	attr1->schedparam.sched_priority = 1;
	attr2->schedparam.sched_priority = 2;
	attr3->schedparam.sched_priority = 3;
	attr4->schedparam.sched_priority = 4;
	attr5->schedparam.sched_priority = 5;
	attr6->schedparam.sched_priority = 6;
}

void test_pthread_teardown()
{
	free(thread1);
	free(thread2);
	free(thread3);
	free(thread4);
	free(thread5);
	free(thread6);
	free(attr1);
	free(attr2);
	free(attr3);
	free(attr4);
	free(attr5);
	free(attr6);
}

void test_pthread_create()
{
	int res = -1;

	/******** 1# Normal Operation ********/
	res = pthread_create(thread1, attr1, task1_func, NULL);
	ASSERT_LONG_EQUAL(0, res);
	// pthread_join(thread1);	// 这里应该等待线程结束比较安全，但是没有实现pthread_join

	/******** 2# Lack Resources ********/
	// 缺少 PTHREAD_THREADS_MAX 常量，无法测试
}

// 对于单进程多线程的 ucOS 来说， 这个接口没有意义
void test_pthread_detach()
{
	/******** 1# Normal Operation ********/
}


// 未实现
void test_pthread_join()
{
	/******** 1# Normal Operation ********/
}

void test_pthread_cancel()
{
	int res = -1;

	/******** 1# Normal Operation ********/
	res = pthread_create(thread2, attr2, task2_func, NULL);
	if (res != 0) {
		FAIL("pthread_create failure");
	}
	res = pthread_cancel(thread2);	// 发出取消命令
	ASSERT_LONG_EQUAL(0, res);
	// pthread_join(thread2);
	sleep(5);	// 等待线程2退出

	/******** 2# Uncancellable Thread ********/
	res = pthread_create(thread3, attr3, task3_func, NULL);
	if (res != 0) {
		FAIL("pthread_create failure");
	}
	sleep(1);	// 等待线程将自己变成 Uncancellable
	res = pthread_cancel(thread3);
	// ASSERT_LONG_EQUAL(ENOEFF, res); ENOEFF 未定义

	/******** 3# Terminated Thread ********/
	res = pthread_create(thread4, attr4, routine1, NULL);
	if (res != 0) {
		FAIL("pthread_create failure");
	}
	sleep(1);
	res = pthread_cancel(thread4);
}

void test_pthread_testcancel()
{
	/******** 1# Normal Operation ********/
}