/* memspeed.c
 * test 1.8GB memory write speed 
 */

#include <stdio.h>
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <unistd.h>
#include <time.h>	/* for clock_gettime */
#include <string.h>

#define MEM1G (1024*1024*1024)
#define TOTAL_LOOP 180
#define MEM_PER_LOOP (100*1024*1024)
#define BILLION 1000000000L

void *test_mem(int loop) {
    int i;
    char *pMem = NULL;
    pMem = malloc(MEM_PER_LOOP);
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
    char *pNow;
    pAllMem = malloc((TOTAL_LOOP+2)*sizeof(char *));
    if (pAllMem == NULL) {
        printf("memory pointer space allocation failure \n");
        return;
    }
    memset(pAllMem, 0x00, (TOTAL_LOOP+2)*sizeof(char *));
    pNow = pAllMem;
    for (loop=0; loop<TOTAL_LOOP; loop++) {
        pMem = test_mem(loop);
        if (pMem == NULL) {
            return;
        }
        memcpy(pNow, &pMem, sizeof(char *));
        pNow += sizeof(char *);
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
