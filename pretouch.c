/*
 *
 * pretouch.c
 * test 1.8GB memory write speed, only for linux native process
 * pretouch the memory before 180 loops, memory is allocted by malloc
 *
 * joehuang.sweden@gmail.com
 *
 */

#include <stdio.h>
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <unistd.h>
#include <time.h>	/* for clock_gettime */
#include <string.h>


#define TOTAL_LOOP 180
#define MEM_PER_LOOP (10*1024*1024)
#define BILLION 1000000000L

void *test_mem(int loop, char* pAllMem) {
	int i;
	char *pMem = NULL;

	pMem = pAllMem + loop*MEM_PER_LOOP;
	if (pMem == NULL) {
		printf("no enough memory %d loop \n", loop);
		return NULL;
	}

	for (i=0; i<MEM_PER_LOOP; i++) {
		*(pMem+i) = i % 255;
	}

	return pMem;
}


void test_loop(void) {
	int loop;
	char *pMem;
	char *pAllMem;

	pAllMem = malloc(TOTAL_LOOP*MEM_PER_LOOP);
	if (pAllMem == NULL) {
		printf("memory pointer space allocation failure \n");
		return;
	}
	memset(pAllMem, 0x00, TOTAL_LOOP*MEM_PER_LOOP);

	for (loop=0; loop<TOTAL_LOOP; loop++) {
		test_mem(loop, pAllMem);
	}
}

int main(void)
{
	uint64_t diff;
	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start);
	test_loop();
	clock_gettime(CLOCK_MONOTONIC, &end);

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

	return 0;
}
