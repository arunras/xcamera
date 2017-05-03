int get_distance(POINT p, POINT q){
    return (sqrt(pow((p.x-q.x), 2) + pow((p.y-q.y), 2)));
}

int get_min(int a, int b){
    int min = (a>b) ? b : a;
    return min;
}

int get_max(int a, int b){
    int max = (a>b) ? a : b;
    return max;
}

// find orientation of ordered triplet (p, q, r).
int orientation(POINT p, POINT q, POINT r){
    int collinear = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (collinear == 0) //collinear
        return 0;
    else{
        if (collinear > 0)
            return 1; //clockwise
        else
            return 2; //counterclock wise
    }
}

// point q lies on line segment 'pr'
int point_on_segment(POINT p, POINT q, POINT r){
    if (q.x <= get_max(p.x,r.x) && q.x >= get_min(p.x,r.x) &&
        q.y <= get_max(p.y,r.y) && q.y >= get_min(p.y,r.y))
        return TRUE;
    return FALSE;
}

// returns true if line segment 'p1q1' and 'p2q2' intersect.
int line_intersect(POINT p1, POINT q1, POINT p2, POINT q2){
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    
    if (o1 != o2 && o3 != o4){
        return TRUE;
    }
    if (o1 == 0 && point_on_segment(p1, p2, q1)){
        return TRUE;
    }
    if (o2 == 0 && point_on_segment(p1, q2, q1)){
        return TRUE;
    }
    if (o3 == 0 && point_on_segment(p2, p1, q2)){
        return TRUE;
    }
    if (o4 == 0 && point_on_segment(p2, q1, q2)){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

/*
// Returns true if the point p lies inside the polygon[] with n vertices
bool isInside(Point polygon[], int n, Point p)
{
    // There must be at least 3 vertices in polygon[]
    if (n < 3)  return false;
 
    // Create a point for line segment from p to infinite
    Point extreme = {INF, p.y};
 
    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
        int next = (i+1)%n;
 
        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'
        if (doIntersect(polygon[i], polygon[next], p, extreme))
        {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(polygon[i], p, polygon[next]) == 0)
               return onSegment(polygon[i], p, polygon[next]);
 
            count++;
        }
        i = next;
    } while (i != 0);
 
    // Return true if count is odd, false otherwise
    return count&1;  // Same as (count%2 == 1)
}
*/


/*
int point_collinear(POINT p){
    int is_collinear = FALSE;
    int dist, dist1, dist2, dist3;
    
    for(int i = 0; i < side; i++){
        dist1 = get_distance(p, polySide[i].v1);
        dist2 = get_distance(p, polySide[i].v2);
        dist3 = get_distance(polySide[i].v1, polySide[i].v2);
        
        dist = (dist1 + dist2) - dist3;
        if(dist <= 5){
            is_collinear = FALSE;
            break;
        }
        else
            is_collinear = TRUE;
    }
    return is_collinear;
}
*/



int point_in_polygon(int n, POINT p, int num_vertex){
    int i, j, k;
    int count;
    int count_vertex = n;
    int is_point_in_poly = FALSE;
    float g;
    
    POINT poly_points[80];
    count = num_vertex - n;
    
    for(i = 0; i < n; i++){
        poly_points[i] = polyVERTEXs[count];
        count++;
    }
    
    for(j = 0, k = count_vertex - 1; j < count_vertex; k = j++) {
        g =(((float)poly_points[k].x - (float)poly_points[j].x) * ((float)p.y - (float)poly_points[j].y) / ((float)poly_points[k].y - (float)poly_points[j].y) + (float)poly_points[j].x);
        
        if(((poly_points[j].y >= p.y) != (poly_points[k].y >= p.y)) && ((float)p.x <= g)){
            if (is_point_in_poly == TRUE){
                is_point_in_poly = FALSE;
            }
            else{
                is_point_in_poly = TRUE;
            }
        }
    }
    return is_point_in_poly;
}

int check_position(POINT p)
{
	for(int i=0; i<count_point; i++){
        	if(POINTS[i].x==p.x && POINTS[i].y==p.y){
            		return FALSE;
        	}
    	}
	return TRUE;
}

//NEW**** check if the point is valid
int is_valid_point(POINT p)
{
    //Check if point has the same position
    /*
	if(check_position(p)){
        return FALSE;
    }
    */
    check_position(p);
    
    //Check if pont is in polygon
    //if(is_inside_polygon(p)){
    if(InsidePolygon(p)) {
        return FALSE;
    }else{
        return TRUE;
    }
}


/*
 Return the angle between two vectors on a plane
 The angle is from vector 1 to vector 2, positive anticlockwise
 The result is between -pi -> pi
 */
float Angle2D(int x1, int y1, int x2, int y2)
{
    double dtheta, theta1, theta2;
    
    theta1 = atan2(y1,x1);
    theta2 = atan2(y2,x2);
    dtheta = theta2 - theta1;
    while (dtheta > PI)
        dtheta -= TWOPI;
    while (dtheta < -PI)
        dtheta += TWOPI;
    
    return(dtheta);
}

// check if point p is inside any polygon
int InsidePolygon(POINT p)
{
    int n, next, k;
    double angle = 0;
    POINT p1, p2;
    
    for(int i=0; i<count_polygon; i++){
        n = POLYGONs[i].n;
        k = 0;
        for(int j=0; j<n; j++){
            next = (k+1)%n;

            p1.x = POLYGONs[i].v[j].x - p.x;
            p1.y = POLYGONs[i].v[j].y - p.y;
            p2.x = POLYGONs[i].v[next].x - p.x;
            p2.y = POLYGONs[i].v[next].y - p.y; 

            angle += Angle2D(p1.x, p1.y, p2.x, p2.y);
            k = next;

            //draw_line(p1, p2, gc_red);
        }
    }
    
    if (fabs(angle) < PI)
        return(FALSE);
    else
        return(TRUE);
}
//=====================***
