/*
 *
 * pretouch3.c
 * test 1.8GB memory write speed, only for linux native process
 * hugepage memory allocated via mmap, pretouch and excluded
 * from the running time
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
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

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


void test_loop(char *pAllMem) {
	int loop;
	char *pMem;

	for (loop=0; loop<TOTAL_LOOP; loop++) {
		test_mem(loop, pAllMem);
	}
}

void* alloc_huge(void) {
	void *addr;
    	int fd, ret;
    
	fd = open("/dev/hugepages/test1", O_CREAT | O_RDWR, 0755);
    	if (fd < 0) {
		printf("Open huge page file failed\n");
		exit(1);
    	}
    
	addr = mmap(NULL, TOTAL_LOOP*MEM_PER_LOOP, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE | MAP_HUGETLB, fd, 0);
     
	if (addr == MAP_FAILED) {
		printf("mmap failure\n");
		exit(1);
    	}
    
	return addr;
}

int main(void)
{
	uint64_t diff;
	struct timespec start, end;
	char *pAllMem;

	pAllMem = alloc_huge();
        if (pAllMem == NULL) {
                printf("memory pointer space allocation failure \n");
                return 0;
        }
        memset(pAllMem, 0x00, TOTAL_LOOP*MEM_PER_LOOP);

	clock_gettime(CLOCK_MONOTONIC, &start);
	test_loop(pAllMem);
	clock_gettime(CLOCK_MONOTONIC, &end);

	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

	return 0;
}
