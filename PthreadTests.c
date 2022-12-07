#include "asserts.h"
#include "face_pthread.h"

void task1_func()
{
	printf("executing task1 ......\n");
	while (1) {
		printf("task1 still running ......\n");
		sleep(1);
	}
	
}

void pthread_create_normaloperation()
{
	pthread_t* thread = (pthread_t*) malloc(sizeof(pthread_t));
	int res = pthread_create(thread, (const pthread_attr_t*) NULL, task1_func, NULL);
	ASSERT_LONG_EQUAL(0, res);
}