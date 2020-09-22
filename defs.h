char InputFile[100] ;      // buffers for file names
char OutputFile[100];
char table[100];
char szFile[100];
static bool quit = 0;
static bool show_main_window = true;
static float col1[3] = { 0.0f,1.0f,0.0f };
static int display_w, display_h;
static bool show_app_fixed_overlay = true;
static void ShowPopup();
static int result =3;
int bin2source();
#ifdef _WIN32
void GetFileName();
OPENFILENAME ofn ;      // filename obtained via file requester (windows only)
#endif