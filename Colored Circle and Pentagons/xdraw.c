#include <X11/Xlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define BUFFERSIZE 20

char color_array[10][8] = { "red", "green", "blue", "yellow", "white", "pink", "brown", "purple", "gray", "orange" };
Display *display;
Window root, window;
long fgcolor, bgcolor;
int color1, color2, color3;
int screen;
XGCValues gcval;
GC draw;
Colormap cmap;
XColor color, ignore;
long eventmask = ButtonPressMask | ExposureMask | KeyPressMask;
XEvent event;
//get three random colors
void setThreeRandomColor() 
{
  int i;
  color1 = rand() % 10;
  do
    color2 = rand() % 10;
  while (color1 == color2);
  do
    color3 = rand() % 10;
  while ((color1 == color3) || (color2 == color3));
}
//set color for a pen
void setDraw(char v_color[8])
{
   cmap = DefaultColormap(display, screen);
  XAllocNamedColor(display, cmap, v_color, &color, &ignore);
  fgcolor = color.pixel;
  gcval.foreground = fgcolor;
  gcval.background = bgcolor;
  gcval.line_width = 3;
  draw = XCreateGC(display, window, GCForeground | GCBackground | GCLineWidth, &gcval);
}
main(argc,argv)
int argc;
char **argv;
{
  int cpointx, cpointy, x1, y1, pointx, pointy;
  int clickCount = 0;
  double big_rec_ras, small_rec_ras;
  char buffer[BUFFERSIZE];
  int bufsize=BUFFERSIZE;  
  KeySym keysym;
  long statinout;
  int charcount;
    if (!(display = XOpenDisplay(argv[1]))) {
  perror("XOpenDisplay");
    }
root = RootWindow(display,screen = DefaultScreen(display));
    fgcolor = BlackPixel(display,screen);
    bgcolor = WhitePixel(display,screen);
    window = XCreateSimpleWindow(display,root,0,0,600,400,2,fgcolor,bgcolor);
  //select input events
    XSelectInput(display,window,eventmask);
    XMapWindow(display,window);   
    for (;;) {
    XWindowEvent(display,window,eventmask,&event);
    // XCheckWindowEvent(display,window,eventmask,&event);  
    switch (event.type) 
      {
        case Expose:
          //XClearWindow(display,window);
          XClearArea( display, window,  0,0, 800, 500, 0);
          break;
        case ButtonPress:
          pointx = event.xbutton.x;
          pointy = event.xbutton.y;
        
        if ((clickCount++ % 2)==0)
            {
              //first point
              setDraw("black");
              XFillArc(display, window, draw, pointx-2, pointy-2,4,4,0, 360*64);
              x1 = pointx;
              y1 = pointy;
            }
          else
            {
              big_rec_ras = sqrt (pow(pointx-x1,2)+pow(pointy-y1,2));
              small_rec_ras = big_rec_ras / (sqrt(2));          
              //get three colors randomly
              setThreeRandomColor();
              //big rectangle
              setDraw(color_array[color1]);
              XPoint v[4];
              v[2].x = pointx-(pointy-y1); v[2].y = pointy-(x1-pointx);
              v[1].x = pointx+(pointy-y1); v[1].y = pointy+(x1-pointx);
              v[3].x = x1+(x1-v[1].x); v[3].y = y1+(y1-v[1].y);
              v[0].x = x1+(x1-v[2].x);v[0].y = y1+(y1-v[2].y);
              XFillPolygon(display,window,draw,v,4,Complex,CoordModeOrigin);
              //big rectangle border
              setDraw("black");
              int i;
              for (i=0;i<4;i++) {
                XDrawLine(display,window,draw,
                 v[i].x,v[i].y,v[(i+1)%4].x,v[(i+1)%4].y);
                }
              //big circle
              setDraw(color_array[color2]);
              XFillArc(display, window, draw, x1 - big_rec_ras, y1 - big_rec_ras, 2 * big_rec_ras, 2 * big_rec_ras, 0, 360 * 64);
              //circle border
              setDraw("black");
              XDrawArc(display, window, draw, x1 - big_rec_ras, y1 - big_rec_ras, 2 * big_rec_ras, 2 * big_rec_ras, 0, 360 * 64);
              //small rectangle
              setDraw(color_array[color3]);
              XFillRectangle(display, window, draw, x1 - small_rec_ras, y1 - small_rec_ras, small_rec_ras * 2, small_rec_ras * 2);
              //small rectangle border
              setDraw("black");
              XDrawRectangle(display, window, draw, x1 - small_rec_ras, y1 - small_rec_ras, small_rec_ras * 2, small_rec_ras * 2);          
              //small dot
              setDraw("black");
              XFillArc(display, window, draw, x1-2, y1-2,4,4,0, 360*64);
            }
          break;
        break;
          case KeyPress:
            charcount = XLookupString(&event,buffer,bufsize, &keysym, &statinout);
            buffer[charcount]='\0';
            if (strcmp (buffer, "c") == 0 )  
            XClearWindow(display,window);
            break;
        default:
        fprintf(stderr,"Unexpected event: %d\n",event.type);
      }
    }
}
