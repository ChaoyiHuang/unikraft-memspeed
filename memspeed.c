#include <stdio.h>
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <unistd.h>
#include <time.h>	/* for clock_gettime */


#define MEM1G (1024*1024*1024)
#define MEM_PER_LOOP (100*1024*1024)
#define BILLION 1000000000L


int main(void)
{
	uint64_t diff;
	struct timespec start, end;
	char *pMem[30];
	char *pNow;
	int loop;
	long long unsigned int i;

	clock_gettime(CLOCK_MONOTONIC, &start);
	for (loop=0; loop<30; loop++) {
		pMem[loop] = malloc(MEM_PER_LOOP);
		if (pMem[loop] == NULL) {
			printf("no enough memory, loop=%d\n", loop);
			return 0;
		}

		for (i=0; i<MEM_PER_LOOP; i++) {
			pNow = pMem[loop] + i;
			*pNow = i % 255;
		}
	}
	clock_gettime(CLOCK_MONOTONIC, &end);

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

	return 0;
}
