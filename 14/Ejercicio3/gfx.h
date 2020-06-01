/*
A simple graphics library for CSE 20211 by Douglas Thain
For course assignments, you should not change this file.
For complete documentation, see:
http://www.nd.edu/~dthain/courses/cse20211/fall2011/gfx
Version 3, 11/07/2012 - Now much faster at changing colors rapidly.
Version 2, 9/23/2011 - Fixes a bug that could result in jerky animation.
*/
#if defined(__cplusplus)
extern "C" {
#endif
#ifndef GFX_H
#define GFX_H
#include <X11/Xlib.h>
#include <stdbool.h>
/* Open a new graphics window. */
void gfx_open( int width, int height, const char *title );

/* Draw a point at (x,y) */
void gfx_point( int x, int y );

/* Draw a line from (x1,y1) to (x2,y2) */
void gfx_line( int x1, int y1, int x2, int y2 );

/* Change the current drawing color. */
void gfx_color( int red, int green, int blue );

/* Clear the graphics window to the background color. */
void gfx_clear();

/* Change the current background color. */
void gfx_clear_color( int red, int green, int blue );

/* Wait for the user to press a key or mouse button. */
char gfx_wait();

/* Return the X and Y coordinates of the last event. */
int gfx_xpos();
int gfx_ypos();

/* Return the X and Y dimensions of the window. */
int gfx_xsize();
int gfx_ysize();

/* Check to see if an event is waiting. */
int gfx_event_waiting();

/* Flush all previous output to the window. */
void gfx_flush();

/* Dibuja un caracter de 17 segmentos entre A y Z o 0 y 9 según su valor ascii, en la posición x, y.
factor es un numero entero entre 1 y n que le da el tamaño al caracter */
void gfx_display_ascii(int x, int y , int factor, int ascii);

/* Draw a filled rectangle; similar to gfx_rectangle, but its size is "one pixel in" at all four sides */
void gfx_fill_rectangle( int x, int y, int w, int h );

/* Dibuja un poligono lleno cuyos vertices se pasan como un arreglo de XPoint */
//     static XPoint reye[] = {{240,270},{230,290},{250,290}}; y npuntos = 3
void gfx_fill_polygon(XPoint *puntos, int npuntos);

#endif

#if defined(__cplusplus)
}
#endif