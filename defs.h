char InputFile[100] ;      // buffers for file names
char OutputFile[100];
char table[100];
char szFile[100];
int rawsize[2];         // rawsize[0] = width     rawsize[1] = height
static bool quit = 0;
static bool raw = false;
static bool rustsrc = false;
static bool decodepng = false;
static bool show_main_window = true;
static float col1[3] = { 0.0f,1.0f,0.0f };
static int bpp = 0;     //bpp = 0 -> 24 bits      bpp = 1 -> 32 bits      bpp = 3 -> 24/32 conversion
static int display_w, display_h;
static bool show_app_fixed_overlay = true;
static void ShowPopup();
static int result = 4;
int raw2source();
int bin2source();
#ifdef _WIN32
void GetFileName();
OPENFILENAME ofn ;      // filename obtained via file requester (windows only)
#endif