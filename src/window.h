void display_window(int argc, char *argv[])
{
    printf("\n>>XLIB>>\n");
    dpy = XOpenDisplay(NULL);
    if(dpy==NULL){
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    
    //printf("Connected to X server  %s\n", XDisplayName(display_name) );
    
    screen_num = DefaultScreen( dpy );
    screen = DefaultScreenOfDisplay( dpy );
    color_map  = XDefaultColormap( dpy, screen_num );
    dpy_width  = DisplayWidth( dpy, screen_num ); //1920; 
    dpy_height = DisplayHeight( dpy, screen_num );

    /* 
    printf("Width : %d, Height : %d, Screen Number : %d\n",
           dpy_width, dpy_height, screen_num);
    */
    
    win_border = 10;
    win_x = 0; win_y = 0;
    win_width = dpy_width;
    win_height = dpy_height;
    
    win= XCreateSimpleWindow( dpy, RootWindow( dpy, screen_num),
                             win_x, win_y, win_width, win_height, win_border,
                             BlackPixel(dpy, screen_num),
                             WhitePixel(dpy, screen_num) );
    
    size_hints = XAllocSizeHints();
    wm_hints = XAllocWMHints();
    class_hints = XAllocClassHint();
    if( size_hints == NULL || wm_hints == NULL || class_hints == NULL )
    { printf("Error allocating memory for hints. \n"); exit(-1);}
    
    size_hints -> flags = PPosition | PSize | PMinSize  ;
    size_hints -> min_width = 60;
    size_hints -> min_height = 60;
    
    XStringListToTextProperty( &win_name_string,1,&win_name);
    XStringListToTextProperty( &icon_name_string,1,&icon_name);
    
    wm_hints -> flags = StateHint | InputHint ;
    wm_hints -> initial_state = NormalState;
    wm_hints -> input = False;
    
    class_hints -> res_name = (char *) "x_use_example";
    class_hints -> res_class = (char *) "examples";
    
    XSetWMProperties( dpy, win, &win_name, &icon_name, argv, argc,
                     size_hints, wm_hints, class_hints );
    
    XSelectInput( dpy, win,ExposureMask | StructureNotifyMask | ButtonPressMask );
    XMapWindow( dpy, win );
    
    
    /* child window */
    child_win_x = (dpy_width/2) - (child_win_width/2);
    child_win_y = (dpy_height/2) - (child_win_height/2) - 50;
    child_win = XCreateSimpleWindow( dpy, win,
                                    child_win_x, child_win_y, child_win_width, child_win_height, child_win_border,
                                    BlackPixel(dpy, screen_num),
                                    WhitePixel(dpy, screen_num));
    
    XSelectInput( dpy, child_win, ExposureMask | StructureNotifyMask | ButtonPressMask );
    XMapWindow( dpy, child_win );
    /* end child window */
    
    
    XFlush(dpy);
    
    gc = XCreateGC( dpy, win, valuemask, &gc_values);
    XSetForeground( dpy, gc, BlackPixel( dpy, screen_num ) );
    XSetLineAttributes( dpy, gc, 2, LineSolid, CapRound, JoinRound);
    
        
    gc_red = XCreateGC( dpy, win, valuemask, &gc_red_values);
    XSetLineAttributes( dpy, gc_red, 1, LineSolid, CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#FF0000",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color red\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_red, tmp_color1.pixel );
    
    gc_green = XCreateGC( dpy, win, valuemask, &gc_green_values);
    XSetLineAttributes( dpy, gc_green, 1, LineSolid, CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#ADFF2F",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color green\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_green, tmp_color1.pixel );
    
    gc_blue = XCreateGC( dpy, win, valuemask, &gc_blue_values);
    XSetLineAttributes(dpy, gc_blue, 1, LineSolid,CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#0000FF",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get blue blue\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_blue, tmp_color1.pixel );
    
    gc_yellow = XCreateGC( dpy, win, valuemask, &gc_yellow_values);
    XSetLineAttributes(dpy, gc_yellow, 1, LineSolid,CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#FFA500",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get blue yellow\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_yellow, tmp_color1.pixel );
    
    gc_black = XCreateGC( dpy, win, valuemask, &gc_black_values);
    XSetLineAttributes( dpy, gc_black, 2, LineSolid, CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#000000",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color black\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_black, tmp_color1.pixel );

    gc_gray = XCreateGC( dpy, win, valuemask, &gc_gray_values);
    XSetLineAttributes(dpy, gc_gray, 2, LineSolid,CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#BEBEBE",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color gray\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_gray, tmp_color1.pixel );

    gc_purple = XCreateGC( dpy, win, valuemask, &gc_purple_values);
    XSetLineAttributes( dpy, gc_purple, 1, LineSolid, CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#A020F0",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color purple\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_purple, tmp_color1.pixel );

    gc_cyan = XCreateGC( dpy, win, valuemask, &gc_cyan_values);
    XSetLineAttributes( dpy, gc_cyan, 1, LineSolid, CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#00FFFF",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color cyan\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_cyan, tmp_color1.pixel );

    gc_dark_green = XCreateGC( dpy, win, valuemask, &gc_dark_green_values);
    XSetLineAttributes( dpy, gc_dark_green, 1, LineSolid, CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#006400",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color dark green\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_dark_green, tmp_color1.pixel );

    gc_steel_blue = XCreateGC( dpy, win, valuemask, &gc_steel_blue_values);
    XSetLineAttributes( dpy, gc_steel_blue, 1, LineSolid, CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#4682B4",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color steel blue\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_steel_blue, tmp_color1.pixel );

    gc_gold = XCreateGC( dpy, win, valuemask, &gc_gold_values);
    XSetLineAttributes( dpy, gc_gold, 1, LineSolid, CapRound, JoinRound);
    if( XAllocNamedColor( dpy, color_map, "#FFD700",
                         &tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color gold\n"); exit(-1);}
    else
        XSetForeground( dpy, gc_gold, tmp_color1.pixel );
}


void draw_point(POINT p, GC point_color)
{
    XFillArc( dpy, child_win, point_color, p.x - win_height/250, p.y - win_height/250, win_height/100, win_height/100, 0, 360*64);
}

void draw_guard(POINT p, GC square_color)
{
    XDrawRectangle(dpy, child_win, square_color, p.x, p.y, SQUARE_SIZE, SQUARE_SIZE);
    XFillRectangle(dpy, child_win, square_color, p.x, p.y, SQUARE_SIZE, SQUARE_SIZE);
}

void draw_line(POINT p, POINT q, GC line_color)
{
    XDrawLine(dpy, child_win, line_color, p.x, p.y, q.x, q.y);
}

void clear_point(POINT p) {
    XClearArea( dpy, child_win, p.x - win_height/250, p.y - win_height/250, win_height/100, win_height/100, false);

}

void print_title()
{
    printf("\n==========>>SET COVER PROBLEM<<==========\n");
}

void print_instruction(char *a)
{
    printf("\n=>Usage:\n");
    printf( "[%s] [file] to load points from file. \n", a);
    printf( "[%s] to enter the points interactively. \n\n", a);
}

void print_camera(){
    if(cam_angle == 90 || cam_angle == 180){
        cout << "CAMERA Angle: [" << cam_angle << "]" << endl;
    }else{
        cout << "CAMERA Angle: [180]" << endl;
    }
    /*
    if(get_angle(cam_angle) == 4){
        cout << "CAMERA angle: [" << "180 degree]" << endl;
    }else if(get_angle(cam_angle) == 8){
        cout << "CAMERA angle: [" << "90 degree]" << endl;
    } 
    */
}
