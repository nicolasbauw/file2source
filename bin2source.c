#include "lodepng/lodepng.h"

// returns 0 : OK       1 : NOK       3 : PNG decoding error
int bin2source()
{
  // For PNG decoding
  unsigned error;
  unsigned char *image = 0;
  unsigned width, height;
  size_t pngsize;

  unsigned char *data;
  FILE *file;
  int i, length;
  // open data file
  file = fopen(InputFile, "rb");
  if (file == NULL)
    return 1;

  // get file size
  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);

  // allocate buffer
  data = (unsigned char *)malloc(length);

  // read file data
  fread(data, length, 1, file);
  fclose(file);

  file = fopen(OutputFile, "w");
  if (file == NULL)
  {
    free(data);
    return 1;
  }

  if (decodepng)
  {
    error = lodepng_decode32(&image, &width, &height, data, pngsize);
    if (error)
      return 3;

    // We re-use the data pointer which will now contain decoded data
    free(data);
    data = image;
    // length for RGBA bitmap
    length = width * height * 4;
  }

  if (pngasraw)
  {
    fwrite(data, length, 1, file);
  }
  else
  {
    fprintf(file, "typedef unsigned char UINT8;\nconst UINT8 %s[%d] = {\n", table, length);
    for (i = 0; i < length; i++)
    {
      fprintf(file, "\t%i,\n", data[i]);
    }
    fprintf(file, "};\n");
  }
  fclose(file);
  if (!decodepng)
  {
    free(data);
  }
  if (decodepng)
  {
    free(image);
  }
  return 0;
}
