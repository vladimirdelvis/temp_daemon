all: temp_daemon b.out

temp_daemon: source.c
	nvcc source.c -lsensors -lnvidia-ml -lserialport -o temp_daemon
b.out: source2.c
	nvcc source2.c -lsensors -lnvidia-ml -lserialport -o b.out
