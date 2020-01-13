// retour 0 : OK        retour 1 : NOK
int bin2source()
{
  unsigned char * data;
  FILE * file;
  int i,lenght;
  // open data file
  file = fopen( InputFile, "rb" );
  if ( file == NULL ) return 1;

  // get file size
  fseek(file,0,SEEK_END);
  lenght=ftell(file);
  fseek(file,0,SEEK_SET);

  // allocate buffer
  data = (unsigned char*)malloc( lenght );

  // read file data
  fread( data, lenght, 1, file );
  fclose( file );

  file=fopen(OutputFile, "w");
  if ( file == NULL ) return 1;

  if (uint8def) fprintf(file,"typedef unsigned char UINT8;\n");
  fprintf(file,"const UINT8 %s[%d] = {\n",table,lenght);
  for (i=0; i<lenght; i++) {
    fprintf(file,"\t%i,\n",data[i]);
  }
  fprintf(file,"};\n");
  fclose( file );
  free( data );
  return 0;
}
