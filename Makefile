all:	cpu cpu2 memory disk
cpu:
	$(info ********************** CPU Benchmark **********************)
	gcc -mavx2 cpu_benchmark.c -o cpu -lpthread
	./cpu -f -o 1000000000 -t 1
	./cpu -f -o 1000000000 -t 2
	./cpu -f -o 10000000000 -t 4
	./cpu -f -o 10000000000 -t 8
	./cpu -i -o 1000000000 -t 1
	./cpu -i -o 1000000000 -t 2
	./cpu -i -o 1000000000 -t 4
	./cpu -i -o 1000000000 -t 8
cpu2:
	$(info ***************** CPU Benchmark- Part f *******************)
	gcc -mavx2 cpu_benchmark_2.c -o cpu2 -lpthread
	./cpu2 -f 
	./cpu2 -i
memory:
	$(info ******************* Memory Benchmark **********************)
	gcc memory_benchmark.c -o memory -lpthread
	./memory -w -o 1000000 -b 8 -t 1
	./memory -w -o 1000000 -b 8 -t 2
	./memory -w -o 100000 -b 8 -t 4
	./memory -w -o 100000 -b 8 -t 8
	
	./memory -w -o 1000 -b 8192 -t 1
	./memory -w -o 1000 -b 8192 -t 2
	./memory -w -o 1000 -b 8192 -t 4
	./memory -w -o 1000 -b 8192 -t 8
	
	./memory -w -o 1 -b 8388608 -t 1
	./memory -w -o 1 -b 8388608 -t 2
	./memory -w -o 1 -b 8388608 -t 4
	./memory -w -o 1 -b 8388608 -t 8
	
	./memory -w -o 1 -b 83886080 -t 1
	./memory -w -o 1 -b 83886080 -t 2
	./memory -w -o 1 -b 83886080 -t 4
	./memory -w -o 1 -b 83886080 -t 8
	./memory -s -o 100000 -b 8 -t 1
	./memory -s -o 100000 -b 8 -t 2
	./memory -s -o 100000 -b 8 -t 4
	./memory -s -o 100000 -b 8 -t 8
	
	./memory -s -o 1000 -b 8192 -t 1
	./memory -s -o 1000 -b 8192 -t 2
	./memory -s -o 1000 -b 8192 -t 4
	./memory -s -o 1000 -b 8192 -t 8
	
	./memory -s -o 1 -b 8388608 -t 1
	./memory -s -o 1 -b 8388608 -t 2
	./memory -s -o 1 -b 8388608 -t 4
	./memory -s -o 1 -b 8388608 -t 8
	
	./memory -s -o 1 -b 83886080 -t 1
	./memory -s -o 1 -b 83886080 -t 2
	./memory -s -o 1 -b 83886080 -t 4
	./memory -s -o 1 -b 83886080 -t 8
	
	./memory -r -o 100000 -b 8 -t 1
	./memory -r -o 100000 -b 8 -t 2
	./memory -r -o 100000 -b 8 -t 4
	./memory -r -o 100000 -b 8 -t 8
	
	./memory -r -o 1000 -b 8192 -t 1
	./memory -r -o 1000 -b 8192 -t 2
	./memory -r -o 1000 -b 8192 -t 4
	./memory -r -o 1000 -b 8192 -t 8
	
	./memory -r -o 1 -b 8388608 -t 1
	./memory -r -o 1 -b 8388608 -t 2
	./memory -r -o 1 -b 8388608 -t 4
	./memory -r -o 1 -b 8388608 -t 8
	
	./memory -r -o 1 -b 83886080 -t 1
	./memory -r -o 1 -b 83886080 -t 2
	./memory -r -o 1 -b 83886080 -t 4
	./memory -r -o 1 -b 83886080 -t 8
disk:
	$(info ****************** disk Benchmark *********************)
	gcc disk_benchmark.c -o disk -lpthread
	./disk -w -o 10000000 -b 8 -t 1
	./disk -w -o 10000000 -b 8 -t 2
	./disk -w -o 10000000 -b 8 -t 4
	./disk -w -o 10000000 -b 8 -t 8
	
	./disk -w -o 10000 -b 8192 -t 1
	./disk -w -o 10000 -b 8192 -t 2
	./disk -w -o 10000 -b 8192 -t 4
	./disk -w -o 10000 -b 8192 -t 8
	
	./disk -w -o 100000 -b 8388608 -t 1
	./disk -w -o 100 -b 8388608 -t 2
	./disk -w -o 10 -b 8388608 -t 4
	./disk -w -o 10 -b 8388608 -t 8
	
	./disk -w -o 10000 -b 83886080 -t 1
	./disk -w -o 10 -b 83886080 -t 2
	./disk -w -o 1 -b 83886080 -t 4	
	./disk -w -o 1 -b 83886080 -t 8
	./disk -s -o 100000 -b 8 -t 1
	./disk -s -o 100000 -b 8 -t 2
	./disk -s -o 100000 -b 8 -t 4
	./disk -s -o 100000 -b 8 -t 8
	
	./disk -s -o 100000 -b 8192 -t 1
	./disk -s -o 100000 -b 8192 -t 2
	./disk -s -o 10000 -b 8192 -t 4
	./disk -s -o 10000 -b 8192 -t 8
	
	./disk -s -o 100 -b 8388608 -t 1
	./disk -s -o 100 -b 8388608 -t 2
	./disk -s -o 10 -b 8388608 -t 4
	./disk -s -o 10 -b 8388608 -t 8
	
	./disk -s -o 10000 -b 83886080 -t 1
	./disk -s -o 10 -b 83886080 -t 2
	./disk -s -o 1 -b 83886080 -t 4
	./disk -s -o 1 -b 83886080 -t 8
	
	./disk -r -o 100000 -b 8 -t 1
	./disk -r -o 100000 -b 8 -t 2
	./disk -r -o 100000 -b 8 -t 4
	./disk -r -o 100000 -b 8 -t 8
	
	./disk -r -o 10000 -b 8192 -t 1
	./disk -r -o 1000 -b 8192 -t 2
	./disk -r -o 1000 -b 8192 -t 4
	./disk -r -o 1000 -b 8192 -t 8
	
	./disk -r -o 100 -b 8388608 -t 1
	./disk -r -o 100 -b 8388608 -t 2
	./disk -r -o 10 -b 8388608 -t 4
	./disk -r -o 10 -b 8388608 -t 8
	
	./disk -r -o 10 -b 83886080 -t 1
	./disk -r -o 10 -b 83886080 -t 2
	./disk -r -o 1 -b 83886080 -t 4
	./disk -r -o 1 -b 83886080 -t 8
