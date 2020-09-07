#include <libpressio.h>
#include <sz.h>
#include <zfp.h>
#include <string.h>
#include <stdlib.h>

#define NUM_RUNS 2

int main(int argc, char *argv[])
{
  double error_bound;
  char compressor_name[100];
  char path_to_data[100];
  if(argc < 4)
  {
    printf("The input is ./compress \"compressor\" ERROR_LEVEL /path/to/data/\n");
    exit(-1);
  }
  else if(argc == 4)
  {
     strcpy(compressor_name, argv[1]);
     error_bound = atof(argv[2]);
     strcpy(path_to_data, argv[3]);
  }

  struct pressio* library;
  struct pressio_compressor* compressor;
  struct pressio_options* sz_options;
  if(strcmp(compressor_name, "sz") == 0)
  {
    library = pressio_instance();
    compressor = pressio_get_compressor(library, "sz");
    sz_options = pressio_compressor_get_options(compressor);

    pressio_options_set_integer(sz_options, "sz:error_bound_mode", ABS);
    pressio_options_set_double(sz_options, "sz:abs_err_bound", error_bound);
    if(pressio_compressor_check_options(compressor, sz_options)) {
      printf("%s\n", pressio_compressor_error_msg(compressor));
      exit(pressio_compressor_error_code(compressor));
    }
    if(pressio_compressor_set_options(compressor, sz_options)) {
      printf("%s\n", pressio_compressor_error_msg(compressor));
      exit(pressio_compressor_error_code(compressor));
    }
  }
  else if(strcmp(compressor_name, "zfp") == 0)
  {
    library = pressio_instance();
    scompressor = pressio_get_compressor(library, "zfp");
    sz_options = pressio_compressor_get_options(compressor);

    pressio_options_set_double(sz_options, "zfp:accuracy", error_bound);
    if(pressio_compressor_check_options(compressor, sz_options)) {
      printf("%s\n", pressio_compressor_error_msg(compressor));
      exit(pressio_compressor_error_code(compressor));
    }
    if(pressio_compressor_set_options(compressor, sz_options)) {
      printf("%s\n", pressio_compressor_error_msg(compressor));
      exit(pressio_compressor_error_code(compressor));
    }
  }
  else
  {
    printf("Compressor %s not currently implemented.\n", compressor_name);
    exit(-2);
  }



  if(fopen(path_to_data) == NULL)
  {
    printf("Data path %s is invalid.\n", path_to_data);
    exit(-3);
  }
  size_t dims[] = {26, 1800, 3600};
  struct pressio_data * description = pressio_data_new_empty(pressio_float_dtype, 3, dims);
  struct pressio_data* input_data = pressio_io_data_path_read(NULL, path_to_data);


  //creates an output dataset pointer
  struct pressio_data* compressed_data = pressio_data_new_empty(pressio_byte_dtype, 0, NULL);

  

  //compress the data
  int counter;
  for(counter = 0; counter < NUM_RUNS; counter++)
  {
      compressed_data = pressio_data_new_empty(pressio_byte_dtype, 0, NULL);
      if(pressio_compressor_compress(compressor, input_data, compressed_data)) {
        printf("%s\n", pressio_compressor_error_msg(compressor));
        exit(pressio_compressor_error_code(compressor));
      }
      pressio_data_free(compressed_data);
  }

  pressio_data_free(compressed_data);
  pressio_data_free(input_data);

  //free options and the library
  pressio_options_free(sz_options);
  pressio_compressor_release(compressor);
  pressio_release(library);
  return 0;
}
