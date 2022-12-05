#include "face_pthread.h"

void task1_func()
{
	printf("executing task1 ......\n");
	while (1) {
		printf("task1 still running ......\n");
		sleep(1);
	}
	
}

void pthread_test_normaloperation()
{
	pthread_t* thread = (pthread_t*) malloc(sizeof(pthread_t));
	pthread_create(thread, (const pthread_attr_t*) NULL, task1_func, NULL);
	int res = pthread_detach(thread);
	if (res != 0) {
		printf("__FILE__:%s\n", __FILE__);
		printf("__LINE__:%d\n", __LINE__ - 3);
	}
}