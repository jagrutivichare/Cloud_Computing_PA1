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

void* calculate_for_read_random(void* arg) {
    FILE *fp = (FILE *)arg;
    fp = fopen("file.txt", "rb");
    char *file_ptr;
    file_ptr=(char *)malloc(BLOCK);
	int i;
    for(i=0; i<OPERATIONS; i++) {
        fseek(fp,rand()%BLOCK+1,SEEK_SET);
        fread(file_ptr, BLOCK, 1, fp);
    }
    fclose(fp);
    pthread_exit(NULL);
}

void* calculate_for_read_sequential(void* arg){
    FILE *fp = (FILE *)arg;
    fp = fopen("file.txt", "rb");
    char *file_ptr;
    file_ptr=(char *)malloc(BLOCK);
	int i;
    for(i=0; i<OPERATIONS; i++) {
        fread(file_ptr, BLOCK, 1, fp);
    }
    fclose(fp);
    pthread_exit(NULL);
}

void* calculate_for_read_write(void* arg) {
    FILE *fp = (FILE *)arg;
    fp = fopen("file.txt", "rb");
    char *file_ptr;
    file_ptr=(char *)malloc(BLOCK);
	int i;
    for(i=0; i<OPERATIONS; i++) {
		fread(file_ptr,BLOCK,1,fp);
        fwrite(file_ptr,BLOCK,1,fp);
    }
    fclose(fp);
    pthread_exit(NULL);
}

void print_result(double time, double thrpt) {
    double total_time=time;
    double throughput=thrpt;
    if (TYPE=='W') {
        if (BLOCK==8) {
            printf("Disk, Latency -> Read write operations, 8B block size, %d thread - %.6lf ms\n",THREAD_COUNT,(total_time/(OPERATIONS*BLOCK))*1000);
        } else if (BLOCK==8192){
            printf("Disk, Throughput -> Read write operations, 8KB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else if (BLOCK==8388608) {
            printf("Disk, Throughput -> Read write operations, 8MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else {
            printf("Disk, Throughput -> Read write operations, 80MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        }
    } else if (TYPE=='S') {
        if (BLOCK==8) {
            printf("Disk, Latency -> Read sequential operations, 8B block size, %d thread - %.6lf ms\n",THREAD_COUNT,(total_time/(OPERATIONS*BLOCK))*1000);
        } else if (BLOCK==8192){
            printf("Disk, Throughput -> Read sequential operations, 8KB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else if (BLOCK==8388608) {
            printf("Disk, Throughput -> Read sequential operations, 8MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else {
            printf("Disk, Throughput -> Read sequential operations, 80MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        }
    } else {
        if (BLOCK==8) {
            printf("Disk, Latency -> Read random operations, 8B block size, %d thread - %.6lf ms\n",THREAD_COUNT,(total_time/(OPERATIONS*BLOCK))*1000);
        } else if (BLOCK==8192){
            printf("Disk, Throughput -> Read random operations, 8KB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else if (BLOCK==8388608) {
            printf("Disk, Throughput -> Read random operations, 8MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        } else {
            printf("Disk, Throughput -> Read random operations, 80MB block size, %d thread - %.2lf MB/sec\n",THREAD_COUNT,throughput/1048576);
        }
    }
}

void calculate_disk_benchmark() {
	char *file_ptr;
    file_ptr=(char *)malloc(BLOCK*OPERATIONS);
	FILE *fp = fopen( "file.txt" , "w" );
	fwrite(file_ptr,1,BLOCK*OPERATIONS,fp);
  
	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL );

    pthread_t thread_id[THREAD_COUNT];
    int thread[THREAD_COUNT]; int i;
    if(TYPE == 'W') {
        for (i=0;i<THREAD_COUNT;i++) {
            thread[i] = pthread_create(&(thread_id[i]),NULL,calculate_for_read_write,fp);
        }
    } else if (TYPE == 'S') {
        for (i=0;i<THREAD_COUNT;i++) {
            thread[i] = pthread_create(&(thread_id[i]),NULL,calculate_for_read_sequential,fp);
        }
    } else {
        for (i=0;i<THREAD_COUNT;i++) {
            thread[i] = pthread_create(&(thread_id[i]),NULL,calculate_for_read_random,fp);
        }
    }
    for (i=0;i<THREAD_COUNT;i++) {
      pthread_join(thread_id[i], NULL);
    }
	
	gettimeofday(&end_time, NULL);
	double total_time = ((end_time.tv_sec+(end_time.tv_usec/1000000.0))-(start_time.tv_sec+(start_time.tv_usec/1000000.0)));
    double bytes_accessed = (double) (OPERATIONS*BLOCK*THREAD_COUNT);
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
    calculate_disk_benchmark();
    return 0;
}
