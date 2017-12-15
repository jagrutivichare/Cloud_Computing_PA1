#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <immintrin.h>

long NUM_OPERATIONS = 10000000;
char OPERATION='F';
int THREAD_COUNT=1;

void* calculate_FLOPS(void* arg){
    // IF AVX is supported
    __m256d vector_a = _mm256_set_pd(7.0, 4.0, 6.0, 5.0);
    __m256d vector_b = _mm256_set_pd(1.0, 2.0, 3.0, 2.0);
    __m256d vector_c = _mm256_set_pd(1.0, 1.0, 1.0, 1.0);
    int i;
    for (i=0;i<NUM_OPERATIONS;i++){ //2 operations - 1 comparison and one addition 
        // adding vector_a and vector_b and storing the result into vector_c
        vector_c = _mm256_add_pd(vector_a, vector_b); //8 operations - 4 additions and 4 assignments
        // subtracting vector_b from vector_a and storing the result into vector_c
        vector_c = _mm256_sub_pd(vector_a, vector_b); //8 operations - 4 subtractions and 4 assignments
        // multiplying vector_a and vector_b and storing the result into vector_c
        vector_c = _mm256_mul_pd(vector_a, vector_b); //8 operations - 4 multiplications and 4 assignments
    }
    pthread_exit(NULL);
    //Total operations = 24+2 = 26
}

void* calculate_IOPS(void* arg) {
    // IF AVX2 is supported
    __m256i vector_a = _mm256_set_epi32(7, 4, 6, 5, 5, 7, 8, 2);
    __m256i vector_b = _mm256_set_epi32(1, 2, 3, 2, 8, 6, 5, 3);
    __m256i vector_c = _mm256_set_epi32(1, 1, 1, 1, 8, 5, 6, 8);
    int i;
    for (i=0;i<NUM_OPERATIONS;i++){ //2 operations - 1 comparison and one addition 
        // adding vector_a and vector_b and storing the result into vector_c
        vector_c = _mm256_add_epi32(vector_a, vector_b); //16 operations - 8 additions and 8 assignments
        // subtracting vector_b from vector_a and storing the result into vector_c
        vector_c = _mm256_sub_epi32(vector_a, vector_b); //16 operations - 8 subtractions and 8 assignments
        // multiplying vector_a and vector_b and storing the result into vector_c
        vector_c = _mm256_mul_epi32(vector_a, vector_b); //16 operations - 8 multiplications and 8 assignments
    }
    pthread_exit(NULL);
    //Total operations = 48+2 = 50
}

void calculate_operations_per_sec(){
    pthread_t thread_id[THREAD_COUNT];
    int thread[THREAD_COUNT]; int i;
    
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL );
    
    if(OPERATION == 'F') {
        for (i=0;i<THREAD_COUNT;i++) {
            thread[i] = pthread_create(&(thread_id[i]),NULL,calculate_FLOPS,NULL);
        }
    } else {
        for (i=0;i<THREAD_COUNT;i++) {
            thread[i] = pthread_create(&(thread_id[i]),NULL,calculate_IOPS,NULL);
        }
    }  
    for (i=0;i<THREAD_COUNT;i++) {
      pthread_join(thread_id[i], NULL);
    }
    
    gettimeofday(&end_time, NULL);
    double total_time = ((end_time.tv_sec+(end_time.tv_usec/1000000.0))-(start_time.tv_sec+(start_time.tv_usec/1000000.0)));
	
    double ops;
	if (OPERATION == 'F') {
		ops = (THREAD_COUNT*NUM_OPERATIONS*26)/total_time;
	} else {
		ops = (THREAD_COUNT*NUM_OPERATIONS*50)/total_time;
	}
	printf("CPU, %d threads, speed = %.2lf Giga %s\n",THREAD_COUNT,ops/1000000000,OPERATION == 'F'?"FLOPS/sec":"IOPS/sec");
}

int main(int argc, char *argv[]){
   int arg;
    while((arg=getopt(argc, argv, "ifo:t:")) != -1) {
        switch(arg) {
            case 'i':
            OPERATION='I'; // for IOPS calculation
            break;
            case 'f':
            OPERATION='F'; // for FLOPS calculation
            break;
            case 'o':
            NUM_OPERATIONS=atoi(optarg);
            case 't':
            THREAD_COUNT=atoi(optarg);
            break;
            default:
            break;
        }
    }
    calculate_operations_per_sec();
    return 0;
}
