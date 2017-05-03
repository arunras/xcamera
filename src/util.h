#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <time.h>
#include <string>

using namespace std;


#define NUM_SAMPLE_POINT    1000
#define NUM_CANDIDATE_POINT 1000
#define NUM_CANDIDATE_PER_ROUND 5
#define CAM_ANGLE 8 // 4 is 180degree; 8 is 90degree

#define CHILD_WIN_WIDTH     1050	//CHILD_WIN_SIZE
#define CHILD_WIN_HEIGHT    650		//CHILD_WIN_SIZE

#define X_MIN 0
#define X_MAX CHILD_WIN_WIDTH
#define Y_MIN 0
#define Y_MAX CHILD_WIN_HEIGHT

#define MAX_POINT   1000
#define MAX_POLYGON 100

#define RANGE_X		CHILD_WIN_WIDTH - 10 //1040
#define RANGE_Y		CHILD_WIN_HEIGHT - 10 //640
#define RAND_MIN	10

#define SQUARE_SIZE     10

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define FALSE       0
#define TRUE		1
#define _INFINITY	1000000
#define PI          3.14159265359
#define TWOPI       PI*2

#define NUM_UNCOVER 50 //0.05
int cam_angle = 180;

enum Direction
{
    N = 0,
    S = 1,
    W = 2,
    E = 3,
    NE = 4,
    SE = 5,
    SW = 6,
    NW = 7
};

typedef struct point
{
    int x;
    int y;
    int weight;
} POINT;

typedef struct guard
{
    POINT p;
    POINT v1;
    POINT v2;
    int direction;
} GUARD;

typedef struct polygon 
{
	int n;	   
	POINT v[MAX_POINT];
} POLYGON;

typedef struct side
{
    POINT v1;
    POINT v2;
} SIDE;

vector <POINT> SAMPLEs;         // set of all sample points
vector <GUARD> CANDIDATEs;      // set of all candidate points 
vector <GUARD> GUARDs;          // set of chosen guard 
vector <vector<POINT> > GUARDset;   // set of subset chosen guard 
vector <vector<POINT> > CANDIDATEset; // set of subset covered


POLYGON POLYGONs[MAX_POLYGON];

POINT POINTS[NUM_SAMPLE_POINT];

//GUARD GUARDS[NUM_CANDIDATE_POINT];

POINT polyVERTEXs[NUM_SAMPLE_POINT];
SIDE  polySide[500];

//tobe removed
int pointSET[NUM_SAMPLE_POINT];
int poly_sideSET[80];

int count_polygon = 0;
int count_sample = 0;
int count_guard = 0;
int count_candidate = 0;
int count_cover = 0;
int count_point = 0;

int count_poly_point  = 0;

//Tobe removed
int side = 0;




//=====[XLib variables declaration]==================================================================
Display *dpy;
unsigned int dpy_width;
unsigned int dpy_height;
char *display_name = NULL;

Screen *screen;
int screen_num;

Window win;
int win_x=0, win_y=0;
unsigned int win_width, win_height;
int win_border=2;

Window child_win;
int child_win_x=400, child_win_y=100;
unsigned int child_win_width = CHILD_WIN_WIDTH, child_win_height=CHILD_WIN_HEIGHT;
int child_win_border=2;

// GUARD    :   gc_red
// SAMPLE   :   gc_black
// CANDIDATE:   gc_green
// COVER    :   gc_blue
// POLYGON  :   gc_gray
// LINE     :   gc_yellow
GC gc, gc_red, gc_green, gc_blue, gc_yellow, gc_black, gc_white, gc_gray;
GC gc_purple, gc_cyan, gc_dark_green, gc_steel_blue, gc_gold;
XGCValues gc_values, gc_red_values, gc_green_values, gc_blue_values, gc_yellow_values, gc_black_values, gc_white_values, gc_gray_values;
XGCValues gc_purple_values, gc_cyan_values, gc_dark_green_values, gc_steel_blue_values, gc_gold_values;
Colormap color_map;
XColor tmp_color1, tmp_color2;
unsigned long valuemask = 0;

XEvent event;

XWMHints *wm_hints;
XClassHint *class_hints;
XSizeHints *size_hints;
XTextProperty win_name, icon_name;
char *win_name_string = (char *) "XCamera - Arun Rasmey";
char *icon_name_string = (char *) "Icon for Example Window";
//=====[end XLib variables declaration]==================================================================
