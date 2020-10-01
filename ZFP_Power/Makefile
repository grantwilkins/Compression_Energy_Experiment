ZFP_PATH=/home/grant/Compression_Energy_Experiment/compressors/zfp
CC=gcc

ZFP_FLAGS= -I$(ZFP_PATH)/include/ -L$(ZFP_PATH)/lib/ -lzfp -lm

all: simple

simple: simple.c
	$(CC) simple.c -Wall -g -o simple $(ZFP_FLAGS)

clean:
	rm simple
