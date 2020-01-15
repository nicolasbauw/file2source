// rawsize[0] = largeur     rawsize[1] = hauteur        bpp = 0 -> 24 bits      bpp = 1 -> 32 bits      bpp = 3 -> conversion 24/32
// retour 0 : OK        retour 1 : NOK      retour 2 : larheur ou hauteur entr�e =0
int raw2source()
{
  unsigned char * data;
  FILE * file;
  int i,rawbpp;
  int alpha_color_R = col1[0]*255;
  int alpha_color_G = col1[1]*255;
  int alpha_color_B = col1[2]*255;

  if (rawsize[0] ==0 || rawsize[1] == 0) return 2;

  switch (bpp) {
    case 0:
        rawbpp = 3;
        break;
    case 1:
        rawbpp = 4;
        break;
    case 3:
        rawbpp = 4;
        break;
    }

  // open source file
  file = fopen( InputFile, "rb" );
  if ( file == NULL ) return 1;

  // allocate buffer
  data = (unsigned char*)malloc( rawsize[0] * rawsize[1] * rawbpp );

  // read data
  fread( data, rawsize[0] * rawsize[1] * rawbpp, 1, file );
  fclose( file );

  // open destination file
  file=fopen(OutputFile, "w");
  if ( file == NULL ) { free( data ); return 1; }

  // sans conversion en RGBA
  if (uint8def) fprintf(file,"typedef unsigned char UINT8;\n");
  if ( bpp !=3 ) {fprintf(file,"// picture resolution = %d * %d * %dbpp\nconst UINT8 %s[%d] = {\n",rawsize[0],rawsize[1],rawbpp,table,rawsize[0] * rawsize[1] * rawbpp);
  for (i=0; i<rawsize[0] * rawsize[1] * rawbpp; i++) {
    fprintf(file,"\t%i,\n",data[i]);
  }
}
  // conversion RGBA
  else if (bpp == 3) {fprintf(file,"// picture resolution = %d * %d * %dbpp\ttransparent color rgb values = %d,%d,%d\nconst UINT8 %s[%d] = {\n",rawsize[0],rawsize[1],rawbpp,alpha_color_R,alpha_color_G,alpha_color_B,table,rawsize[0] * rawsize[1] * rawbpp);
  for (i=0; i<rawsize[0] * rawsize[1] * rawbpp; i+=3) {
    fprintf(file,"\t%i,\n\t%i,\n\t%i,\n",data[i],data[i+1],data[i+2]);
    if (data[i] == alpha_color_R && data[i+1] == alpha_color_G && data[i+2] == alpha_color_B) fprintf(file,"\t0,\n");
    else fprintf(file,"\t255,\n");
  }}

  // fin du programme
  fprintf( file, "};\n");
  fclose( file );
  free( data );
  return 0;
}
