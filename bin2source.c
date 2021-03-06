#include <stdlib.h>
#include <stdio.h>

char InputFile[100] ;      // buffers for file names
char OutputFile[100];
char table[100];

// returns 0 : OK       1 : NOK
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
  if ( file == NULL )  { free( data ); return 1; }

  fprintf(file,"typedef unsigned char UINT8;\nconst UINT8 %s[%d] = {\n",table,lenght);
  for (i=0; i<lenght; i++) {
    fprintf(file,"\t%i,\n",data[i]);
  }
  fprintf(file,"};\n");
  fclose( file );
  free( data );
  return 0;
}
