char InputFile[100] ;      // buffers contenant les noms des fichier
char OutputFile[100];
char table[100];
char szFile[100];
int rawsize[2];         // rawsize[0] = largeur     rawsize[1] = hauteur
static bool quit = 0;
static bool raw = false;
static bool uint8def = true;
static float col1[3] = { 0.0f,1.0f,0.0f };
static int bpp = 0;     //bpp = 0 -> 24 bits      bpp = 1 -> 32 bits      bpp = 3 -> conversion 24/32
static int i=4;
static bool show_app_fixed_overlay = true;
static void ShowOverlay(bool* opened);
static int result =3;
void GetFileName();
int raw2source();
int bin2source();
#ifdef _WIN32
OPENFILENAME ofn ;      // nom du fichier à ouvrir via boite de dialogue
#endif