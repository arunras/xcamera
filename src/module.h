//=====[FUNCTIONS]=========================================================================

bool operator==(const POINT &, const POINT &);

//polygon
void read_polygon(char *file_name);
void display_polygon();

//point
void add_sample(POINT p);
void add_candidate(GUARD p);
void add_guard(POINT p);
bool point_projected(GUARD g, POINT p);
void draw_direction(GUARD g);

void generate_sample_points(int n);
void generate_candidate_points(int n);
void generate_points();
void generate_cover();

void display_samples();
void display_candidates();
void display_guards();
void display_points();

void clear_candidates();

int get_angle(int angle);

//geometry
int set_direction();
int get_distance(POINT p, POINT q);
int get_min(int a, int b);
int get_max(int a, int b);
int orientation(POINT p, POINT q, POINT r);
int point_on_segment(POINT p, POINT q, POINT r);
int point_collinear(POINT p);
int line_intersect(POINT p1,POINT p2,POINT p3, POINT p4);
int point_in_polygon(int n, POINT p, int num_vertex);
int check_position(POINT p);
int is_valid_point(POINT p);
int valid_point(POINT p);

//void candidate_in_polygon(POINT p);
//int is_sameple_point (int x, int y);

int InsidePolygon(POINT p);
float Angle2D(int x1, int y1, int x2, int y2);

//window
void display_window(int argc, char *argv[]);
void draw_point(POINT p, GC point_color);
void draw_guard(POINT p, GC point_color);
void draw_line(POINT p, POINT q, GC line_color);
void clear_point(POINT p);

void print_title();
void print_instruction(char *a);
void print_camera();        
//=====[end FUNCTIONS]=========================================================================


