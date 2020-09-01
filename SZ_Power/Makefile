SZ_PATH=/users/gfwilki/Compression_Energy_Experiment/compressors/SZ_Files/SZ
LIBPRESSIO_PATH=/users/gfwilki/libpressio
CC=gcc

SZ_FLAGS= -I$(SZ_PATH)/include/ -lm
LIBPRESSIO_FLAGS= -I$(LIBPRESSIO_PATH)/include/ -llibpressio

all: sz_compress sz_decompress

sz_compress: sz_compress.c
	$(CC) sz_compress.c -Wall -g -o sz_compress $(SZ_FLAGS) $(LIBPRESSIO_FLAGS)

sz_decompress: sz_decompress.c
	$(CC) sz_decompress.c -Wall -g -o sz_compress $(SZ_FLAGS) $(LIBPRESSIO_FLAGS)

clean:
	rm sz_compress
	rm sz_decompress