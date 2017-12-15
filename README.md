# Cloud_Computing_PA1
Benchmark different parts of computer system using Chameleon testbed (CS553)

Run CPU Benchmark
Directory ‘PA1_VICHARE_’ has all the benchmarking programs. Files
‘cpu_benchmark.c’ and ‘cpu_benchmark_2.c’ performs CPU benchmark.
‘cpu_benchmark.c’ - This program calculates latency, GFLOPS and GIOPS of CPU
at varying concurrency level for 1, 2, 4 and 8 threads.

It takes few command line arguments which are mentioned below:
-i calculate IOPS
-f calculate FLOPS
-o O Number of operations
-t T Number of threads

To run this program individually do below mentioned steps:
gcc -mavx2 cpu_benchmark.c -o cpu -lpthread
./cpu -f|-i -o O -t T

To run the CPU benchmark to calculate GIOPS for 1000 operations on 2 threads,
use following command:
./cpu -i -o 1000 -t 2

To run this program for all possible combinations of GIOPS/GFLOPS, number of
operations and threads, run following command
make cpu

‘cpu_benchmark_2.c’ - This program runs the benchmark on double precision
floating point and integer instructions and 8 threads for a 10-minute period for
each one, and take samples every second.

It takes following command line arguments :
-i calculate IOPS
-f calculate FLOPS

To run this program individually, run following commands:
gcc -mavx2 cpu_benchmark_2.c -o cpu2 -lpthread
./cpu2 -f // to calculate FLOPS
./cpu2 -i // to calculate IOPS

To run this program for all possible combinations of IOPS/FLOPS, run following
command:
make cpu2

Run Memory Benchmark
File ‘memory_benchmark.c’ performs Memory benchmark.
‘memory_benchmark.c’ - This program calculates latency(in microseconds),
memory throughput(in MB/sec) for read/write, sequential write and random write
operations for 8B, 8KB, 8MB and 80MB block sizes at varying concurrency level
for 1, 2, 4 and 8 threads.

It takes following command line arguments:
-w Read/write operations
-s Sequential write operations
-r Random write operations
-o O Number of operations
-t T Number of threads
-b B Block size

To run this program individually do below mentioned steps:
gcc memory_benchmark.c -o memory -lpthread
./memory -w|-s|-r -o O -b B -t T

To run the Memory benchmark to calculate throughput and latency for read/write
operations for 1000 operations on 2 threads having block size 8B, use following
command:
./memory -w -o 1000 -t 2 -b 8

To run this program for all possible combinations of type of operations, number of
operations, threads and block sizes, run following command
make memory

Run Disk Benchmark
File ‘disk_benchmark.c’ performs Disk benchmark.
‘disk_benchmark.c’ - This program calculates latency(in milliseconds), memory
throughput(in MB/sec) for read/write, sequential read and random read
operations for 8B, 8KB, 8MB and 80MB block sizes at varying concurrancy level
for 1, 2, 4 and 8 threads.

It takes following command line arguments:
-w Read/write operations
-s Sequential read operations
-r Random read operations
-o O Number of operations
-t T Number of threads
-b B Block size

To run this program individually, run following commands:
gcc disk_benchmark.c -o disk -lpthread
./disk -w|-s|-r -o O -b B -t T

To run the disk benchmark to calculate throughput and latency for read/write
operations for 1000 operations on 2 threads having block size 8B, use following
command:
./disk -w -o 1000 -t 2 -b 8

To run this program for all possible combinations of type of operations, number of
operations, threads and block sizes, run following command
make disk

Run Network Benchmark
File server.c performs the benchmark for the server side of network benchmark.
File client.c performs the benchmark for the client side of network benchmark.
Parameter space includes the TCP protocol stack, UDP, fixed packet/buffer size
(64KB), and varying the concurrency (1 thread, 2 threads, 4 threads, 8 threads);
and also multi-threaded support exists at both client and server.

It takes the following command line arguments:
- Connection type : TCP/UDP
- Block Size: 64Kb fixed
- No. of Threads: 1,2,4,8

Run GPU Benchmark
‘CUDA.cu’ file performs GPU benchmark. Follow below mentioned command to
run GPU code:
nvcc CUDA.cu -o gpu_benchmark
./gpu_benchamrk

To run the CPU, Memory and Disk benchmarks one by one , run
following commands:
make all
