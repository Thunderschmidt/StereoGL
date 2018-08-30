#ifndef STEREOGL
#define STEREOGL


////////////////////////////////////////////////////////////////////////////////
////////////////////////////        TIMER         //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void  init_timer();
void  proceed_timer();
void limit_fmult(float limit);

float get_fps();
float get_fmult();
int   get_chrono();
////////////////////////////////////////////////////////////////////////////////
////////////////////////////        MATH         ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
typedef struct VECTOR
{
   float x, y, z;
} VECTOR;
//
//class MATR_STACK  //Zur Simulation von OpenGL-Matrix-Stackberechnungen
//{
//   private:
//   int total;
//   MATRIX_f actual;
//   MATRIX_f **stack;
//   public:
//   void mul(MATRIX_f *m);
//   void mul_alg(MATRIX_f *m);
//   void push();
//   void pop();
//   void loadIdentity();
//   void translate(VECTOR *v);
//   MATRIX_f get();
//   MATR_STACK(int maxstackmatrices);
//   ~MATR_STACK(){delete stack;}
//};
//
//VECTOR trans_matrix_to_vector(MATRIX_f *m);
//bool accelerate(float soll, float *ist, float a);
//void translate_matrix_v(MATRIX_f *m, VECTOR *pos);
void glMultMatrix_allegro(MATRIX_f *m);
MATRIX_f matr(float x, float y, float z, float xrot, float yrot, float zrot);
//VECTOR vect(float x, float y, float z);
void invert_matrix(MATRIX_f *in, MATRIX_f *out);
//void glMultMatrix_allegro_inv(MATRIX_f *m);
//void get_matrix_delta(MATRIX_f *m_act, MATRIX_f *m_old, MATRIX_f *m_delta);



////////////////////////////////////////////////////////////////////////////////
////////////////////////////       STEREO-VIEW       ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define LEFT_EYE 0
#define RIGHT_EYE 1


class STEREO
{
   private:
   float distance_to_monitor;
   float half_eye_seperation;
   float monitor_width;
   float half_monitor_width;
   float monitor_height;
   float half_monitor_height;
   float far_clip;
   float clipscale;
   float near_clip;
   float eye_seperation;
   float scale;

   public:
   STEREO();
   void init_lighting();
   void set_eye(bool eye);
   void position_camera(MATRIX_f *camera_matrix);

   void  set_eye_seperation(float value){eye_seperation=value; half_eye_seperation=value/2;}
   float get_eye_seperation(){return(eye_seperation);}
   void  set_monitor_height(float value){monitor_height=value;half_monitor_height=value/2;}
   float get_monitor_height(){return(monitor_height);}
   void  set_monitor_width(float value){monitor_width=value;half_monitor_width=value/2;}
   float get_monitor_width(){return(monitor_width);}
   void  set_distance_to_monitor(float value){distance_to_monitor=value;clipscale=near_clip/distance_to_monitor;}
   float get_distance_to_monitor(){return(distance_to_monitor);}
   void  set_far_clip(float value){far_clip=value;}
   float get_far_clip(){return(far_clip);}
   void  set_near_clip(float distance_to_face){if(distance_to_face > 0){near_clip=distance_to_face;clipscale=near_clip/distance_to_monitor;}}
   void  set_near_clip_to_monitor(){near_clip=distance_to_monitor;clipscale=1.0;}
   float get_near_clip(){return(near_clip);}
   void  set_scale(float value){scale=value;}
   float get_scale(){return(scale);}
   float get_frustum_angle_x_360();
   float get_frustum_angle_y_360();
};

////////////////////////////////////////////////////////////////////////////////
//////////////////////////       STEREO-COLOR        ///////////////////////////
////////////////////////////////////////////////////////////////////////////////

void load_color_table(char file[]);  //initialize graphic before calling this function
void color16(char lumi);
void color16(char lumi, unsigned char alpha);
void color256(unsigned char lumi);
void color256(unsigned char lumi, unsigned char alpha);
void convert_to_stereo_bitmap(BITMAP *bmp, bool eye);
inline bool get_eye();
char* get_table_file();

////////////////////////////////////////////////////////////////////////////////
////////////////////////////     FONT-DRAWING     //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void StGL_font_load(const char filename[]);
void StGL_font_draw(char string[]);

#endif
