void read_polygon(char *file_name)
{
    int line_max_length = 1024;
    char line[line_max_length];
    FILE *fp;
    char *str;
    int k = 0;

    int num_point;
    int num_coor;
    int COORs[1000];
    int x_coor, y_coor;
 
    //printf(">>READ POLYGONS\n");
    
    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("\n=>INFORMATION!:\n");
        fprintf(stderr, "Unable to open file %s!\n", file_name);
        printf( "File \"%s\" may not exist, please check whether file is present or not.\n\n", file_name );
    }
    while(fgets(line, line_max_length, fp) != NULL){
        str = strtok(line, ",() \n");
	num_coor = 0;
	num_point = 0;

        while (str != NULL){
	    COORs[num_coor] = atoi(str);
            str = strtok(NULL, ",\n ()");

            //str = strtok(NULL, ",\n ()");
	    num_coor++;
        }
        while(num_coor != 0){
	    x_coor = num_coor - 2;
	    y_coor = num_coor - 1;
	 
            polyVERTEXs[k].x = COORs[x_coor];
            polyVERTEXs[k].y = COORs[y_coor];
            k++;
            count_poly_point++;


	    //NEW
       POLYGONs[count_polygon].v[num_point].x = COORs[x_coor];
       POLYGONs[count_polygon].v[num_point].y = COORs[y_coor];
		
		POINTS[count_point].x = COORs[x_coor];
		POINTS[count_point].y = COORs[y_coor];
		count_point++;
		
		num_coor = num_coor - 2;
		num_point++;


        }
        poly_sideSET[count_polygon] = num_point;

	//NEW
	POLYGONs[count_polygon].n = num_point;
        count_polygon++;

    }
    fclose(fp);
}

void display_polygon(){
    	int num_point;
    	int num_side;
    
    	for(int i=0; i<count_polygon; i++){
		num_side = 0;
            	num_point = POLYGONs[i].n;
	    	XPoint poly_points[num_point];
            	for(int j=0; j<num_point; j++){
                	poly_points[j].x = POLYGONs[i].v[j].x;
                	poly_points[j].y = POLYGONs[i].v[j].y;
                	if(j!=num_point-1){
                    		draw_line(POLYGONs[i].v[j], POLYGONs[i].v[j+1], gc_black);
                    		num_side++;
                	}
               		else{
                    		draw_line(POLYGONs[i].v[j], POLYGONs[i].v[0], gc_black);
                    		num_side++;
                	}
		} 
        	XFillPolygon(dpy, child_win, gc_gray , poly_points, num_side, Complex, CoordModeOrigin);
	}
}
