/*
 ===========================================
 Project: XCamera                           |
 Course: Term-Project (I9800)  	            |
 Name: Arun Rasmey                          |
 Date: Spring 2017                          |
 ===========================================
 ======================================================================================
 To compile in Mac: g++ -o app main.cpp -I/usr/X11R6/include -L/usr/X11R6/lib -lX11
 ======================================================================================
 */

#include "util.h"
#include "module.h"
#include "polygon.h"
#include "point.h"
#include "geometry.h"
#include "window.h"

int main(int argc, char *argv[]) //argc=argument count, argv=argument vector
{
    if(argc==3){
        cam_angle = atoi(argv[2]);
    }

    char *file_name = argv[1];
    //char *file_name = (char *) "/Users/arun/WorkSpace/xrobit/src/obstacle";

    display_window(argc, argv);
    //print_title();
    
    print_camera();        

    read_polygon(file_name);
    
    while(1)
    {
        XNextEvent( dpy, &event );
        if(event.xany.window == child_win)
        {
            switch( event.type )
            {
                case Expose:

                    display_polygon();
		            generate_points();
	        	    display_points();
                    XFlush(dpy);
                    generate_cover();
		            //============*******
                    //test
                    //print_guard_covers();
                    break;
                    
                case ConfigureNotify:
                    win_width = event.xconfigure.width;
                    win_height = event.xconfigure.height;
                    break;
                    
                default:
                    break;
            }
        }
    }
    //XCloseDisplay(dpy);
    return 0;
}
