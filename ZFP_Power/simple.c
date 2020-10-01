/* minimal code example showing how to call the zfp (de)compressor */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zfp.h>
#define NUM_TIMES 10

/* compress or decompress array */
int
compress(float* array, int nx, int ny, int nz, double tolerance, int decompress, int dim)
{
  int status = 0;    /* return value: 0 = success */
  zfp_type type;     /* array scalar type */
  zfp_field* field;  /* array meta data */
  zfp_stream* zfp;   /* compressed stream */
  void* buffer;      /* storage for compressed stream */
  size_t bufsize;    /* byte size of compressed buffer */
  bitstream* stream; /* bit stream to write to or read from */
  size_t zfpsize;    /* byte size of compressed stream */

  type = zfp_type_float;
 
  if(dim == 1)
  {
     field = zfp_field_1d(array, type, nx);
  }
  else if(dim == 2)
  {
     field = zfp_field_2d(array, type, nx, ny);
  }
  else if(dim == 3)
  {
     field = zfp_field_3d(array, type, nx, ny, nz);
  }
  else
  {
    printf("Something messed up with dimension!\n");
    exit(-99);
  }
  /* allocate meta data for the 3D array a[nz][ny][nx] */
  

  /* allocate meta data for a compressed stream */
  zfp = zfp_stream_open(NULL);

  /* set compression mode and parameters via one of four functions */
/*  zfp_stream_set_reversible(zfp); */
/*  zfp_stream_set_rate(zfp, rate, type, 3, zfp_false); */
/*  zfp_stream_set_precision(zfp, precision); */
  zfp_stream_set_accuracy(zfp, tolerance);

  /* allocate buffer for compressed data */
  bufsize = zfp_stream_maximum_size(zfp, field);
  buffer = malloc(bufsize);
int i;
if(decompress)
{

    for(i = 0; i < NUM_TIMES; i++)
    {
      /* associate bit stream with allocated buffer */
      stream = stream_open(buffer, bufsize);
      zfp_stream_set_bit_stream(zfp, stream);
      zfp_stream_rewind(zfp);

      /* compress or decompress entire array */
      
        /* compress array and output compressed stream */
        if(i == 0)
        {
                  zfpsize = zfp_compress(zfp, field);
        if (!zfpsize) {
          fprintf(stderr, "compression failed\n");
          status = 1;
        }
        }
        if (decompress) {
        /* read compressed stream and decompress array */
        //zfpsize = fread(buffer, 1, bufsize, stdin);
        if (!zfp_decompress(zfp, field)) {
          fprintf(stderr, "decompression failed\n");
          status = 1;
        }
      }
      
    }
}
else
{
  for(i = 0; i < NUM_TIMES; i++)
  {
    /* associate bit stream with allocated buffer */
    stream = stream_open(buffer, bufsize);
    zfp_stream_set_bit_stream(zfp, stream);
    zfp_stream_rewind(zfp);

    /* compress or decompress entire array */
    
      /* compress array and output compressed stream */
      zfpsize = zfp_compress(zfp, field);
      if (!zfpsize) {
        fprintf(stderr, "compression failed\n");
        status = 1;
      }
    
    }
}

  /* clean up */
  zfp_field_free(field);
  zfp_stream_close(zfp);
  stream_close(stream);
  free(buffer);
  free(array);

  return status;
}

int main(int argc, char* argv[])
{
/*
For this function we will let
argv[4] = decompression option
argv[1] = data path
argv[2] = data dimensions
argv[3] = error bound
*/
  char *data_path;
  char *data_dimensions_string;
  int data_dimensions[5];
  long long int data_size = 1;
  double error_bound;
  int i;
  int dim = 0;
  /* use -d to decompress rather than compress data */
  int decompress = (argc == 5 && !strcmp(argv[4], "-d"));


  if(argc == 5 || argc == 4)
  {
      data_path = argv[1];
      data_dimensions_string = argv[2];
      char *pt;
      pt = strtok(data_dimensions_string, ",");
      int count = 0;
      while (pt != NULL) {
        data_dimensions[count] = atoi(pt);
        count++;
        pt = strtok (NULL, ",");
      }
      //Determine Data Size
      for (i = 0; i < 5; i++){
        if (data_dimensions[i] != 0){
          data_size = data_size * data_dimensions[i];
          dim++;
        } 
      }

      error_bound = atof(argv[3]);
  }
  /* allocate 100x100x100 array of doubles */
  int nx = data_dimensions[4];
  int ny = data_dimensions[3];
  int nz = data_dimensions[2];
  float * data = malloc(data_size* sizeof(float));
  FILE *fp = fopen(data_path, "rb");
  fread(data, 4, data_size, fp);
  fclose(fp);
  compress(data, nx, ny, nz, error_bound, decompress, dim);
    return 0;
}
