#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

int OPERATIONS = 1000;
int BLOCK = 8;
int THREAD_COUNT = 1;
char TYPE = 'W';

struct thread_param {
    char * param1;
    char * param2;
};

void* calculate_for_read_write(void* arg) {
    struct thread_param *param = (struct thread_param *)arg;
    int i;
    for (i=0;i<OPERATIONS;i++) {
        memcpy(param->param1+(i*BLOCK), param->param2, BLOCK);
    }
    pthread_exit(NULL);
}

void* calculate_for_sequential_write(void* arg) {
    char *source = (char *)arg;
    int i;
    for (i=0;i<OPERATIONS;i++) {
      memset(source+(i*BLOCK), 0, BLOCK);
    }
    pthread_exit(NULL);
}

void* calculate_for_random_write(void* arg) {
    char *source = (char *)arg;
    int random_var,i;
    for (i=0;i<OPERATIONS;i++) {
      random_var = rand() % OPERATIONS;
      memset(source+(random_var*BLOCK), 0, BLOCK);
    }
    pthread_exit(NULL);
}

void print_result(double time, double thrpt) {
    double total_time=time;
    double throughput=thrpt;
    if (TYPE=='W') {
        if (BLOCK==8) {
            printf("Memory, Latency -> Read write operations, 8B block size, %d thread - %.6lf us\n",THREAD_COUNT,(total_time/(OPERATIONS*BLOCK))*1000000);
        } else if (BLOCK==8192){
            printf("Memory, Throughput -> Read write operations, 8KB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else if (BLOCK==8388608) {
            printf("Memory, Throughput -> Read write operations, 8MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else {
            printf("Memory, Throughput -> Read write operations, 80MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        }
    } else if (TYPE=='S') {
        if (BLOCK==8) {
            printf("Memory, Latency -> Write sequential operations, 8B block size, %d thread - %.6lf us\n",THREAD_COUNT,(total_time/(OPERATIONS*BLOCK))*1000000);
        } else if (BLOCK==8192){
            printf("Memory, Throughput -> Write sequential operations, 8KB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else if (BLOCK==8388608) {
            printf("Memory, Throughput -> Write sequential operations, 8MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else {
            printf("Memory, Throughput -> Write sequential operations, 80MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        }
    } else {
        if (BLOCK==8) {
            printf("Memory, Latency -> Write random operations, 8B block size, %d thread - %.6lf us\n",THREAD_COUNT,(total_time/(OPERATIONS*BLOCK))*1000000);
        } else if (BLOCK==8192){
            printf("Memory, Throughput -> Write random operations, 8KB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else if (BLOCK==8388608) {
            printf("Memory, Throughput -> Write random operations, 8MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else {
            printf("Memory, Throughput -> Write random operations, 80MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        }
    }
}

void calculate_memory_benchmark(){
    char * source = (char *)malloc(BLOCK*OPERATIONS);
	char * dest = (char *)malloc(BLOCK);
    
    memset(source, 2, BLOCK*OPERATIONS);
	memset(dest, 1, BLOCK);
    
    struct thread_param params;
    params.param1 = source;
    params.param2 = dest;
    
    struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL );

    pthread_t thread_id[THREAD_COUNT];
    int thread[THREAD_COUNT]; int i;
    if(TYPE == 'W') {
        for (i=0;i<THREAD_COUNT;i++) {
            thread[i] = pthread_create(&(thread_id[i]),NULL,calculate_for_read_write,(void *)&params);
        }
    } else if (TYPE == 'S') {
        for (i=0;i<THREAD_COUNT;i++) {
            thread[i] = pthread_create(&(thread_id[i]),NULL,calculate_for_sequential_write,source);
        }
    } else {
        for (i=0;i<THREAD_COUNT;i++) {
            thread[i] = pthread_create(&(thread_id[i]),NULL,calculate_for_random_write,source);
        }
    }
    for (i=0;i<THREAD_COUNT;i++) {
      pthread_join(thread_id[i], NULL);
    }
    
    gettimeofday(&end_time, NULL);
	double total_time = ((end_time.tv_sec+(end_time.tv_usec/1000000.0))-(start_time.tv_sec+(start_time.tv_usec/1000000.0)));
	
    double bytes_accessed = (double) (BLOCK*OPERATIONS*THREAD_COUNT);
	double throughput = bytes_accessed/total_time;
    print_result(total_time,throughput);
}

int main(int argc, char *argv[]){
    int arg;
    while((arg=getopt(argc, argv, "wsro:t:b:")) != -1) {
        switch(arg) {
            case 'w':
            TYPE='W'; // for read-write
            break;
            case 's':
            TYPE='S'; // for sequential write
            break;
            case 'r':
            TYPE='R'; // for random write
            break;
            case 'o':
            OPERATIONS=atoi(optarg);
            break;
            case 't':
            THREAD_COUNT=atoi(optarg);
            break;
            case 'b':
            BLOCK=atoi(optarg);
            break;
            default:
            break;
        }
    }
    calculate_memory_benchmark();
    return 0;
}
