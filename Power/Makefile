SZ_PATH=/users/gfwilki/Compression_Energy_Experiment/compressors/SZ_Files/SZ
ZFP_PATH=/users/gfwilki/Compression_Energy_Experiment/compressors/zfp
LIBPRESSIO_PATH=/users/gfwilki/libpressio
CC=gcc

SZ_FLAGS= -I$(SZ_PATH)/include/ -lm
ZFP_FLAGS= -I$(ZFP_PATH)/include/ -lm
LIBPRESSIO_FLAGS= -I$(LIBPRESSIO_PATH)/include/ -llibpressio

all: compress decompress

compress: compress.c
	$(CC) compress.c -Wall -g -o compress $(SZ_FLAGS) $(ZFP_FLAGS)$(LIBPRESSIO_FLAGS)

sz_decompress: decompress.c
	$(CC) decompress.c -Wall -g -o decompress $(SZ_FLAGS) $(ZFP_FLAGS) $(LIBPRESSIO_FLAGS)

clean:
	rm compress
	rm decompress