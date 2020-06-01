/*
A simple graphics library for CSE 20211 by Douglas Thain
For complete documentation, see:
http://www.nd.edu/~dthain/courses/cse20211/fall2011/gfx
Version 3, 11/07/2012 - Now much faster at changing colors rapidly.
Version 2, 9/23/2011 - Fixes a bug that could result in jerky animation.
*/

#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "gfx.h"

/*
gfx_open creates several X11 objects, and stores them in globals
for use by the other functions in the library.
*/

static Display *gfx_display=0;
static Window  gfx_window;
static GC      gfx_gc;
static Colormap gfx_colormap;
static int      gfx_fast_color_mode = 0;

/* These values are saved by gfx_wait then retrieved later by gfx_xpos and gfx_ypos. */

static int saved_xpos = 0;
static int saved_ypos = 0;

/* Open a new graphics window. */

void gfx_open( int width, int height, const char *title )
{
	gfx_display = XOpenDisplay(0);
	if(!gfx_display) {
		fprintf(stderr,"gfx_open: unable to open the graphics window.\n");
		exit(1);
	}

	Visual *visual = DefaultVisual(gfx_display,0);
	if(visual && visual->class==TrueColor) {
		gfx_fast_color_mode = 1;
	} else {
		gfx_fast_color_mode = 0;
	}

	int blackColor = BlackPixel(gfx_display, DefaultScreen(gfx_display));
	int whiteColor = WhitePixel(gfx_display, DefaultScreen(gfx_display));

	gfx_window = XCreateSimpleWindow(gfx_display, DefaultRootWindow(gfx_display), 0, 0, width, height, 0, blackColor, blackColor);

	XSetWindowAttributes attr;
	attr.backing_store = Always;

	XChangeWindowAttributes(gfx_display,gfx_window,CWBackingStore,&attr);

	XStoreName(gfx_display,gfx_window,title);

	XSelectInput(gfx_display, gfx_window, StructureNotifyMask|KeyPressMask|ButtonPressMask);

	XMapWindow(gfx_display,gfx_window);

	gfx_gc = XCreateGC(gfx_display, gfx_window, 0, 0);

	gfx_colormap = DefaultColormap(gfx_display,0);

	XSetForeground(gfx_display, gfx_gc, whiteColor);

	// Wait for the MapNotify event

	for(;;) {
		XEvent e;
		XNextEvent(gfx_display, &e);
		if (e.type == MapNotify)
			break;
	}
}

/* Draw a single point at (x,y) */

void gfx_point( int x, int y )
{
	XDrawPoint(gfx_display,gfx_window,gfx_gc,x,y);
}

/* Draw a line from (x1,y1) to (x2,y2) */

void gfx_line( int x1, int y1, int x2, int y2 )
{
	XDrawLine(gfx_display,gfx_window,gfx_gc,x1,y1,x2,y2);
}

/* Change the current drawing color. */

void gfx_color( int r, int g, int b )
{
	XColor color;

	if(gfx_fast_color_mode) {
		/* If this is a truecolor display, we can just pick the color directly. */
		color.pixel = ((b&0xff) | ((g&0xff)<<8) | ((r&0xff)<<16) );
	} else {
		/* Otherwise, we have to allocate it from the colormap of the display. */
		color.pixel = 0;
		color.red = r<<8;
		color.green = g<<8;
		color.blue = b<<8;
		XAllocColor(gfx_display,gfx_colormap,&color);
	}

	XSetForeground(gfx_display, gfx_gc, color.pixel);
}

/* Clear the graphics window to the background color. */

void gfx_clear()
{
	XClearWindow(gfx_display,gfx_window);
}

/* Change the current background color. */

void gfx_clear_color( int r, int g, int b )
{
	XColor color;
	color.pixel = 0;
	color.red = r<<8;
	color.green = g<<8;
	color.blue = b<<8;
	XAllocColor(gfx_display,gfx_colormap,&color);

	XSetWindowAttributes attr;
	attr.background_pixel = color.pixel;
	XChangeWindowAttributes(gfx_display,gfx_window,CWBackPixel,&attr);
}

int gfx_event_waiting()
{
       XEvent event;

       gfx_flush();

       while (1) {
               if(XCheckMaskEvent(gfx_display,-1,&event)) {
                       if(event.type==KeyPress) {
                               XPutBackEvent(gfx_display,&event);
                               return 1;
                       } else if (event.type==ButtonPress) {
                               XPutBackEvent(gfx_display,&event);
                               return 1;
                       } else {
                               return 0;
                       }
               } else {
                       return 0;
               }
       }
}

/* Wait for the user to press a key or mouse button. */

char gfx_wait()
{
	XEvent event;

	gfx_flush();

	while(1) {
		XNextEvent(gfx_display,&event);

		if(event.type==KeyPress) {
			saved_xpos = event.xkey.x;
			saved_ypos = event.xkey.y;
			return XLookupKeysym(&event.xkey,0);
		} else if(event.type==ButtonPress) {
			saved_xpos = event.xkey.x;
			saved_ypos = event.xkey.y;
			return event.xbutton.button;
		}
	}
}

/* Return the X and Y coordinates of the last event. */

int gfx_xpos()
{
	return saved_xpos;
}

int gfx_ypos()
{
	return saved_ypos;
}

/* Flush all previous output to the window. */

void gfx_flush()
{
	XFlush(gfx_display);
}

/* Draw a filled rectangle; similar setup to gfx_rectangle, but "one pixel in" on all four sides */
void gfx_fill_rectangle( int x, int y, int w, int h )
{ 
	XFillRectangle(gfx_display, gfx_window, gfx_gc, x, y, w, h);
}

/* Dibuja un poligono lleno cuyos vertices se pasan como un arreglo de XPoint */
//Ejemplo de un triangulo lleno:
// XPoint reye[] = {{240,270},{230,290},{250,290}};
//  npuntos = 3;
void gfx_fill_polygon(XPoint *puntos, int npuntos){
	XFillPolygon(gfx_display, gfx_window, gfx_gc, puntos, npuntos, Convex, CoordModeOrigin);
}

void gfx_display_ascii(int x, int y , int f, int n) //Valor ASCII
{
    XPoint nueve[] = {{f+x,2*f+y},{2*f+x,f+y},{3*f+x,5*f+y}, {2*f+x, 6*f+y}};
    XPoint diez[] = {{5*f+x, f+y}, {6*f+x, 2*f+y}, {5*f+x, 6*f+y}, {4*f+x, 5*f+y}};
    XPoint once[] = {{2*f+x, 7*f+y}, {3*f+x, 8*f+y}, {2*f+x, 12*f+y}, {f+x, 11*f+y}};
    XPoint trece[] = {{4*f+x, 8*f+y}, {5*f+x, 7*f+y}, {6*f+x, 11*f+y}, {5*f+x, 12*f+y}};
    int npuntos = 4;
    
    if(n != 'H' && n!= 'J' && n!= 'K' && n != 'L' && n != 'M' && n != 'N' && n != 'U' && n != 'V' && n != 'W' && n != 'X' && n != 'Y' && n !='1' && n !='4'){
        gfx_fill_rectangle( f+x, 0+y, 2*f, f ); //1
    }

    if(n != 'H' && n!= 'J' && n!= 'K' && n != 'L' && n != 'M' && n != 'N' && n != 'U' && n != 'V' && n != 'W' && n != 'X' && n != 'Y' && n !='1' && n !='4' && n !='6'){
        gfx_fill_rectangle( 4*f+x, 0+y, 2*f, f ); //2        
    }    

    if(n != 'B' && n!= 'D' && n != 'I' && n != 'J' && n != 'T' && n != 'X' && n != 'Z' && n !='1' && n !='2' && n !='3' && n !='7')
        gfx_fill_rectangle( 0+x, f+y, f, 5*f ); //8

    if(n != 'C' && n!= 'E' && n!= 'F' && n != 'G' && n != 'I' && n != 'K' && n != 'L' && n != 'S' && n != 'T' && n != 'V' && n != 'X' && n != 'Z' && n !='5' && n !='6')
        gfx_fill_rectangle( 6*f+x, f+y, f, 5*f ); //3

    if(n!= 'B' && n!= 'D' && n != 'I' && n != 'S' && n != 'T' && n != 'X' && n != 'Y' && n != 'Z' && n !='1' && n !='3' && n !='4' && n !='5' && n !='7' && n !='9')
        gfx_fill_rectangle( 0+x, 7*f+y, f, 5*f ); //7

    if(n != 'C' && n!= 'E' && n!= 'F' && n != 'I' && n != 'K' && n != 'L' && n != 'P' && n != 'R' && n != 'T' && n != 'V' && n != 'X' && n != 'Y' && n != 'Z' && n !='2')    
        gfx_fill_rectangle( 6*f+x, 7*f+y, f, 5*f ); //4

    if(n != 'A' && n!= 'F' && n!= 'H' && n!= 'K' && n != 'M' && n != 'N' && n != 'P' && n != 'R' && n != 'T' && n != 'V' && n != 'W' && n != 'X' && n != 'Y' && n !='1' && n !='4' && n !='7' && n !='9'){
        gfx_fill_rectangle( f+x, 12*f+y, 2*f, f ); //6
    }
    if(n != 'A' && n!= 'F' && n!= 'H' && n!= 'K' && n != 'M' && n != 'N' && n != 'P' && n != 'R' && n != 'T' && n != 'V' && n != 'W' && n != 'X' && n != 'Y' && n !='1' && n !='4' && n !='7'){
        gfx_fill_rectangle( 4*f+x, 12*f+y, 2*f, f ); //5
    }

    if(n == 'M' || n== 'N' || n== 'X')
        gfx_fill_polygon(nueve, npuntos); //9
    if(n == 'B' || n== 'D' || n== 'I' || n== 'T')
        gfx_fill_rectangle( 3*f+x, f+y, f, 5*f ); //16
    if(n == 'K' || n== 'M' || n== 'V' || n== 'X' || n== 'Z' || n== '0' || n== '1' )
        gfx_fill_polygon(diez, npuntos); //10
    if(n == 'A' || n== 'E' || n== 'F' || n== 'H' || n== 'K' || n== 'P' || n== 'R' || n== 'S' || n== 'Y' || n== '2' || n== '4' || n== '5' || n== '6' || n== '8' || n== '9' )
        gfx_fill_rectangle( f+x, 6*f+y, 2*f, f ); //14
    if(n == 'A' || n== 'B' || n== 'G' || n== 'H' || n== 'P' || n== 'R' || n== 'S' || n== 'Y'  || n== '2' || n== '3' ||n== '4' || n== '5' || n== '6' || n== '8' || n== '9' )
        gfx_fill_rectangle( 4*f+x, 6*f+y, 2*f, f ); //15    
    if(n == 'V' || n == 'W' || n== 'X' || n== 'Z' || n== '0')
        gfx_fill_polygon(once, npuntos); //11
    if(n == 'B' || n== 'D' || n== 'I' || n== 'T' || n== 'Y')
        gfx_fill_rectangle( 3*f+x, 7*f+y, f, 5*f ); //17
    if(n == 'K' || n== 'N' || n== 'Q' || n== 'R' || n== 'W' || n== 'X')
        gfx_fill_polygon(trece, npuntos); //13    
}