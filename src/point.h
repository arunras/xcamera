// get index of max candiateset
int get_max_candidate(){
    int max_size = 0;
    int index = 0;
    for(int i=0; i<CANDIDATEset.size(); i++){
        if(CANDIDATEset[i].size() > max_size){
            max_size = (int) CANDIDATEset[i].size();
            index = i;
        }
    }
    return index;
}

//generate the cover set of SAPMPLEs, CANDIDATEs, and find the GUARDs and COVERs
void generate_cover()
{
	int num_point;
	int is_intersect = false;
    int count_group = 1;

    vector <POINT> CoverSet;
    vector <POINT> Samples(SAMPLEs);

    //while (GUARDs.size()<NUM_CANDIDATE_POINT){
    while (Samples.size()>0) { //NUM_UNCOVER){
        if(CANDIDATEs.size()==0){break;}
        CANDIDATEset.clear();

	    for(int i=0; i<CANDIDATEs.size(); i++){ // for each candidate 
            CoverSet.clear();
		    for(int j=0; j<Samples.size(); j++){ // for each  sample
			    for(int k=0; k<count_polygon; k++){ // for each polygon
				    num_point = POLYGONs[k].n;
				    for(int m=0; m<num_point; m++){ // for each point in polygon
                        if(m!=num_point-1){
						    is_intersect = line_intersect(CANDIDATEs[i].p, Samples[j], POLYGONs[k].v[m], POLYGONs[k].v[m+1]);	
                	    }else{
						    is_intersect = line_intersect(CANDIDATEs[i].p, Samples[j], POLYGONs[k].v[m], POLYGONs[k].v[0]);	
                	    }
					    if(is_intersect) { goto next_point; }
				    }	
			    }		

			    if(!is_intersect){
                    if(point_projected(CANDIDATEs[i], Samples[j])){
                        CoverSet.push_back(Samples[j]);
                    }
			    }	
                next_point:;
		    }
        
            CANDIDATEset.push_back(CoverSet);
	    }	

        if(GUARDs.size()%5==0){
            cout << endl; 
            cout << "===GROUP[" << count_group << "]=========================================" << endl;
        }

        //int max_size = 0;
        int index = 0;
        index = get_max_candidate();
        GUARDs.push_back(CANDIDATEs[index]);

        //draw_guard(GUARDs.back().p, gc_red); 
        // draw guards
        if(CANDIDATEset[index].size()!=0){
            draw_point(GUARDs.back().p, gc_red); 
            //draw_direction(GUARDs.back());
            cout << "Guard[" << count_guard << "]=> ";
            cout << "Direction: [" << GUARDs.back().direction << "]; ";
            cout << "SIZE: [" << CANDIDATEset[index].size() << "];\t";
            cout << "Weight: [" << CANDIDATEset[index][0].weight << "]" << endl;
            count_guard++;
        }else{
            break;
        }

        //draw covered points 
        for (int n=0; n<CANDIDATEset[index].size(); ++n) {
            switch (CANDIDATEset[index][n].weight){
                case 1: 
                    draw_point(CANDIDATEset[index][n], gc_blue);
                    break;
                case 2: 
                    draw_point(CANDIDATEset[index][n], gc_green);
                    break;
                case 4: 
                    draw_point(CANDIDATEset[index][n], gc_yellow);
                    break;
                case 8: 
                    draw_point(CANDIDATEset[index][n], gc_purple);
                    break;
                case 16: 
                    draw_point(CANDIDATEset[index][n], gc_cyan);
                    break;
                case 32: 
                    draw_point(CANDIDATEset[index][n], gc_dark_green);
                    break;
                default:
                    draw_point(CANDIDATEset[index][n], gc_steel_blue);
                    break;
            }

            draw_line(GUARDs.back().p, CANDIDATEset[index][n], gc_gold);
            XFlush(dpy);
        }
        //cout << endl; 
        
        // remove covered sample points
        for (int n = 0; n < CANDIDATEset[index].size(); ++n) {
            Samples.erase(remove(Samples.begin(), Samples.end(), CANDIDATEset[index][n]), Samples.end());
            count_cover++;
        }
        // remove the guard position
        CANDIDATEs.erase(CANDIDATEs.begin() + index);

        // increase point weight of each guard group
        if(GUARDs.size()%5==0){
            for(int i=0; i<Samples.size(); i++){
                Samples[i].weight *= 2;
            }
            count_group++;
        }
    }
   
    cout << endl; 
    cout << "Total GUARDs: " << count_guard << endl;
    cout << "Total COVERs: " << count_cover << "/" << NUM_SAMPLE_POINT << endl;
    cout << "Computation is DONE!" << endl << endl;
}

// generate all sample points randomly
void generate_sample_points(int n)
{
    srand((unsigned)time(NULL));
    POINT p; 
    for (int i=0; i<n; ++i) {
        p.x = rand() % RANGE_X + RAND_MIN;
        p.y = rand() % RANGE_Y + RAND_MIN;
        //p.x = 900;
        //p.y = 200;
        p.weight = 1;
        //if(is_valid_point(p)){
        if(!InsidePolygon(p)){
            add_sample(p);
        }else {
            i--; 
        }
        //count_point++;
    }
}

// generate all candidate points randomly
void generate_candidate_points(int n)
{
    GUARD g;
    for (int i=0; i<n; ++i) {
        g.p.x = rand() % RANGE_X + RAND_MIN;
        g.p.y = rand() % RANGE_Y + RAND_MIN;
        //g.p.x = 900;
        //g.p.y = 100;
        g.direction = set_direction();
        if(is_valid_point(g.p)){
		    add_candidate(g);
        }else {
            i--; 
        }
        //count_point++;
    }
}

// call functions generate_sample and generate_candidate points
void generate_points()
{
    generate_sample_points(NUM_SAMPLE_POINT);
    generate_candidate_points(NUM_CANDIDATE_POINT);
}

// display sample points
void display_samples()
{
	for(int i=0; i<SAMPLEs.size(); i++){
        //if(InsidePolygon(SAMPLEs[i])){
		    draw_point(SAMPLEs[i], gc_black);	
            XFlush(dpy);
        //}
        //cout << "point_projection: " << point_projected(CANDIDATEs[i], SAMPLEs[i]) << endl << endl;
	}
}

// display candidate points
void display_candidates()
{
	for(int i=0; i<CANDIDATEs.size(); i++){
		draw_point(CANDIDATEs[i].p, gc_green);	
        //cout << "direction[" << i << "]: " << CANDIDATEs[i].direction << endl << endl;
        draw_direction(CANDIDATEs[i]);
	}
}

// display guard points
void display_guards()
{
	for(int i=0; i<GUARDs.size(); i++){
		draw_point(GUARDs[i].p, gc_red);	
        cout << "direction[" << i << "]: " << CANDIDATEs[i].direction << endl << endl;
        XFlush(dpy);
	}
}

// display all points
void display_points()
{
    display_samples();
    //display_candidates();
    //display_guards();
}

// add 1 sample point to the SAMPLEs set
void add_sample(POINT p){
  SAMPLEs.push_back(p);
}

// add 1 candidate point to the CANDIDATEs set
void add_candidate(GUARD g){
    CANDIDATEs.push_back(g);
}

// add 1 guard point to the GUARDs set
void add_guard(GUARD g){
    GUARDs.push_back(g);
}

int get_angle(int angle){
    if(angle==90){
        return 8;
    }else if(angle==180){
        return 4;
    }else{
        return 4;
    }
}
// set direction to candidate
int set_direction()
{
    int angle = get_angle(cam_angle);
    if(angle == 4){
        //4: 180 degree
        return (Direction)(rand() % angle);     
    }else if(angle == 8) {
        //8: 90 degree
        return (Direction)(rand() % angle + 4); 
    }else{
        return (Direction)(rand() % angle);     
    }
}

bool operator==(const POINT & lhs, const POINT & rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
}

//check if the point p is projected by candidate q
bool point_projected(GUARD g, POINT p)
{
    //return TRUE; // 360 degree
    int dr = g.direction; //direction
    switch (dr){
        case 0: //N 
            return (p.y < g.p.y) ? true : false;
            break;
        case 1: //S 
            return (p.y > g.p.y) ? true : false;
            break;
        case 2: //W
            return (p.x < g.p.x) ? true : false;
            break;
        case 3: //E
            return (p.x > g.p.x) ? true : false;
            break;
        case 4: //NE 
            return ((p.x > g.p.x) && (p.y < g.p.y)) ? true : false;
            break;
        case 5: //SE 
            return ((p.x > g.p.x) && (p.y > g.p.y)) ? true : false;
            break;
        case 6: //SW
            return ((p.x < g.p.x) && (p.y > g.p.y)) ? true : false;
            break;
        case 7: //NW
            return ((p.x < g.p.x) && (p.y < g.p.y)) ? true : false;
            break;
    }
    return 0;
}

// draw direction of guard
void  draw_direction(GUARD g)
{
   //todo: check each direction
    POINT p;
    int dr = g.direction; //direction
    switch (dr){
        case 0: //N
            p.x = g.p.x;
            p.y = Y_MIN; 
            draw_line(g.p, p, gc_red); 
            break;
        case 1: //S
            p.x = g.p.x;
            p.y = Y_MAX; 
            draw_line(g.p, p, gc_red); 
            break;
        case 2: //W
            p.x = X_MIN;
            p.y = g.p.y; 
            draw_line(g.p, p, gc_red); 
            break;
        case 3: //E
            p.x = X_MAX;
            p.y = g.p.y; 
            draw_line(g.p, p, gc_red); 
            break;
        case 4: //NE
            p.x = X_MAX;
            p.y = Y_MIN; 
            draw_line(g.p, p, gc_red); 
            break;
        case 5: //SE
            p.x = X_MAX;
            p.y = Y_MAX; 
            draw_line(g.p, p, gc_red); 
            break;
        case 6: //SW
            p.x = X_MIN;
            p.y = Y_MAX; 
            draw_line(g.p, p, gc_red); 
            break;
        case 7: //NW
            p.x = X_MIN;
            p.y = Y_MIN; 
            draw_line(g.p, p, gc_red); 
            break;
    }
}
