// returns 0 : OK       1 : NOK
int bin2source()
{
  unsigned char *data;
  FILE *file;
  int i, lenght;
  // open data file
  file = fopen(InputFile, "rb");
  if (file == NULL)
    return 1;

  // get file size
  fseek(file, 0, SEEK_END);
  lenght = ftell(file);
  fseek(file, 0, SEEK_SET);

  // allocate buffer
  data = (unsigned char *)malloc(lenght);

  // read file data
  fread(data, lenght, 1, file);
  fclose(file);

  file = fopen(OutputFile, "w");
  if (file == NULL)
  {
    free(data);
    return 1;
  }

  if (!rustsrc)
  {
    fprintf(file, "typedef unsigned char UINT8;\n");
    fprintf(file, "const UINT8 %s[%d] = {\n", table, lenght);
    for (i = 0; i < lenght; i++)
    {
      fprintf(file, "\t%i,\n", data[i]);
    }
    fprintf(file, "};\n");
    fclose(file);
    free(data);
    return 0;
  }
  else
  {
    fprintf(file, "lazy_static! {\n\tpub static ref PIXELS: Vec<u32> =  { vec![\n");
    for (i = 0; i < lenght; i++)
    {
      fprintf(file, "\t\t%i,\n", data[i]);
    }
    fprintf(file, "\t]};\n}");
    fclose(file);
    free(data);
    return 0;
  }
}
