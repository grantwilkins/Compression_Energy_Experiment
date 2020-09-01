ZFP_PATH=/users/gfwilki/Compression_Energy_Experiment/compressors/zfp
LIBPRESSIO_PATH=/users/gfwilki/libpressio
CC=gcc

ZFP_FLAGS= -I$(ZFP_PATH)/include/ -lm
LIBPRESSIO_FLAGS= -I$(LIBPRESSIO_PATH)/include/ -llibpressio

all: zfp_compress zfp_decompress

zfp_compress: zfp_compress.c
	$(CC) zfp_compress.c -Wall -g -o zfp_compress $(ZFP_FLAGS) $(LIBPRESSIO_FLAGS)

zfp_decompress: zfp_decompress.c
	$(CC) zfp_decompress.c -Wall -g -o zfp_compress $(ZFP_FLAGS) $(LIBPRESSIO_FLAGS)

clean:
	rm zfp_compress
	rm zfp_decompress