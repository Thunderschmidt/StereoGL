#include <stdio.h>
#include <math.h>
#include <string.h>
#include <allegro.h>
#include <alleggl.h>
#include <GL/glu.h>
#include "StereoGL.h"

//////////////////////////////////////////////////////////////

BITMAP *mysha;
BITMAP *texture;
GLuint gl_texture;
MATRIX_f camera_matrix=identity_matrix_f;
STEREO stereo;
float r=0;
GLfloat glma[16];

//////////////////////////////////////////////////////////////


void draw_box()
{
   glColor4f(1, 1, 1, 1);
   glTexEnvf(GL_TEXTURE_ENV, GL_BLEND, GL_DECAL);
   glBindTexture(GL_TEXTURE_2D, gl_texture);
   
   glBegin(GL_QUADS);
   
   glEnable (GL_TEXTURE_2D);
   glTexCoord2f(0, 0); glVertex3f(-0.5,-0.5,-0.5);  //links
   glTexCoord2f(0, 1); glVertex3f(-0.5,0.5,-0.5);
   glTexCoord2f(1, 1); glVertex3f(-0.5,0.5,0.5);
   glTexCoord2f(1, 0); glVertex3f(-0.5,-0.5,0.5);
   glDisable (GL_TEXTURE_2D);

   color16(15);
   glVertex3f(-0.5, -0.5, -0.5); //vorne
   glVertex3f(0.5, -0.5, -0.5);
   glVertex3f(0.5, 0.5, -0.5);
   glVertex3f(-0.5, 0.5, -0.5);
   
   glVertex3f(0.5,-0.5,-0.5);  //rechts
   glVertex3f(0.5,-0.5,0.5);
   glVertex3f(0.5,0.5,0.5);
   glVertex3f(0.5,0.5,-0.5);

   color16(7);
   glVertex3f(-0.5,-0.5,-0.5); //unten
   glVertex3f(-0.5,-0.5,0.5);
   glVertex3f(0.5,-0.5,0.5);
   glVertex3f(0.5,-0.5,-0.5);

   glVertex3f(-0.5,0.5,-0.5);  //oben
   glVertex3f(0.5,0.5,-0.5);
   glVertex3f(0.5,0.5,0.5);
   glVertex3f(-0.5,0.5,0.5);
   
   color16(15);
   glVertex3f(-0.5, -0.5, 0.5); //hinten
   glVertex3f(-0.5, 0.5, 0.5);
   glVertex3f(0.5, 0.5, 0.5);
   glVertex3f(0.5, -0.5, 0.5);

   glEnd();

}
   GLfloat glm2[16];

void stereo_render(bool eye)
/*  In dieser Funkion wird alles Stereoskopische gezeichnet.
 *  Sie wird deshalb auch zweimal pro Frame aufgerufen.
 *  Einmal mit eye=0 und einmal mit eye=1;
 */
{
   int i, j;
   stereo.set_eye(eye);
   stereo.position_camera(&camera_matrix);
   glRotatef(r, 0.0, 1.0, 0.0);
   glRotatef(r*2, 1.0, 0.0, 0.0);
   draw_box();
}

char buf[512];
void render()
{
   glViewport(0,  0, SCREEN_W, SCREEN_H); //113
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	stereo_render(LEFT_EYE);
	glClear(GL_DEPTH_BUFFER_BIT );
	stereo_render(RIGHT_EYE);


	////////////////////////////////////////////////////////////////////////////

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glViewport(0, 0, SCREEN_W, SCREEN_H);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluOrtho2D(0 , SCREEN_W, 0, SCREEN_H);
//	glScalef(2, 2, 0);
   glColor4ub(255, 255, 255, 128);
   glPushMatrix();
 	glDisable(GL_DEPTH_WRITEMASK);
 	glDisable(GL_DEPTH_TEST);
 	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
 	
	glScalef(16, 16, 0);
  glTranslatef(3, SCREEN_H/16-8, 0);

   StGL_font_draw("stereo gl\n");
//	glScalef(1/6, 1/6, 0);
	glScalef(0.2, 0.2, 0);

 	sprintf(buf, "object size       : %.2f m\n", 1/stereo.get_scale());
   StGL_font_draw(buf);
 	sprintf(buf, "head-object dist. : %.2f m\n", camera_matrix.t[2]/stereo.get_scale());
   StGL_font_draw(buf);
   sprintf(buf, "s: scale          : 1:%.1f \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", stereo.get_scale());
   StGL_font_draw(buf);
   glColor4ub(255, 255, 0, 128);
 	sprintf(buf, "e: eye seperation       : %2.1f cm\n", stereo.get_eye_seperation()*100);
   StGL_font_draw(buf);
 	sprintf(buf, "d: head/monitor distance: %.1f cm\n", stereo.get_distance_to_monitor()*100);
   StGL_font_draw(buf);
 	sprintf(buf, "n: near clip            : %.1f cm\n", stereo.get_near_clip()*100);
   StGL_font_draw(buf);
 	sprintf(buf, "w: monitor width        : %.1f cm\n", stereo.get_monitor_width()*100);
   StGL_font_draw(buf);
   sprintf(buf, "h: monitor height       : %.1f cm\n", stereo.get_monitor_height()*100);
   StGL_font_draw(buf);
   sprintf(buf, "   camera frustum angle : %.1f deg\n", stereo.get_frustum_angle_x_360());
   StGL_font_draw(buf);
   glPopMatrix();

 	glEnable(GL_DEPTH_TEST);
   glEnable(GL_DEPTH_WRITEMASK);

   glLoadIdentity();
	glFlush();
	allegro_gl_flip();
}

void user_input()
{
   poll_keyboard();
   if(key[KEY_S])
   {
      if(key_shifts & KB_SHIFT_FLAG)stereo.set_scale(stereo.get_scale()/(1+1*get_fmult()));
      else stereo.set_scale(stereo.get_scale()*(1+1*get_fmult()));
   }
   if(key[KEY_E])
   {
      if(key_shifts & KB_SHIFT_FLAG)stereo.set_eye_seperation(stereo.get_eye_seperation()-0.02*get_fmult());
      else stereo.set_eye_seperation(stereo.get_eye_seperation()+0.02*get_fmult());
   }
   if(key[KEY_D])
   {
      if(key_shifts & KB_SHIFT_FLAG)stereo.set_distance_to_monitor(stereo.get_distance_to_monitor()/1.01);
      else stereo.set_distance_to_monitor(stereo.get_distance_to_monitor()*1.01);
   }
   if(key[KEY_N])
   {
      if(key_shifts & KB_SHIFT_FLAG)stereo.set_near_clip(stereo.get_near_clip()/1.01);
      else stereo.set_near_clip(stereo.get_near_clip()*1.01);
   }
   if(key[KEY_W])
   {
      if(key_shifts & KB_SHIFT_FLAG)stereo.set_monitor_width(stereo.get_monitor_width()/1.01);
      else stereo.set_monitor_width(stereo.get_monitor_width()*1.01);
   }
   if(key[KEY_H])
   {
      if(key_shifts & KB_SHIFT_FLAG)stereo.set_monitor_height(stereo.get_monitor_height()/1.01);
      else stereo.set_monitor_height(stereo.get_monitor_height()*1.01);
   }
   if(key[KEY_UP])
   {
      camera_matrix.t[2]-=4*get_fmult();
   }
   if(key[KEY_DOWN])
   {
      camera_matrix.t[2]+=4*get_fmult();
   }
   clear_keybuf();
}

void init_gfx()
{
   allegro_gl_clear_settings();
   set_color_depth(32);
   allegro_gl_set (AGL_COLOR_DEPTH, 32);
   allegro_gl_set (AGL_Z_DEPTH, 32);
   allegro_gl_set (AGL_DOUBLEBUFFER, 1);
   allegro_gl_set (AGL_RENDERMETHOD, 1);
   allegro_gl_set (AGL_FULLSCREEN, TRUE);
   allegro_gl_use_mipmapping(FALSE);
   set_gfx_mode(GFX_OPENGL_FULLSCREEN, 1024, 768, 0, 0);
	glPolygonMode(GL_FRONT, GL_FILL);            //Fülle die sichtbaren Polygone aus
   glPolygonMode(GL_BACK, GL_POINT);            //errechne für die unsichtbaren Polys nur die Punkte
	glCullFace(GL_BACK);                         //zeichne nur die Vorderseite der Polygone
	glEnable(GL_CULL_FACE);                      //aktiviere BackFaceCulling
	glFrontFace(GL_CW);                          //die sichtbaren Polygone sind die linksgedrehten
	glShadeModel(GL_FLAT);                       //heißt: kein Gouraud-Shading
	glAlphaFunc(GL_GREATER, 0.5);                //Pixel mit einem Alpha unter 0.5 werden ignoriert
   glEnableClientState (GL_VERTEX_ARRAY);       //wird noch nicht gebraucht
   glBlendFunc(GL_ONE, GL_ONE);                 //Blending-Methode. RGB-Werte werden zusammenaddiert
   glEnable (GL_LINE_SMOOTH);                           //Schaltet Linien-Antialiasing ein
   glEnable (GL_POINT_SMOOTH);                          //Schaltet Punkt-Antialiasing ein
   glEnable(GL_BLEND);                                  //Schaltet Blenden-Effekte ein
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  //aktiviert den Alpha-Kanal
   glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);          //?
//   glLineWidth (1.0);                                   //Linienstärke = 0.2 Ppixel...
//   glPointSize(3.0);
   glEnable(GL_DEPTH_TEST);                             //Schalte Tiefentest ein
//   glPolygonOffset(1, 1);
   glClearColor(0.1, 0.1, 0.1, 1.0);

   if (!allegro_gl_get(AGL_RENDERMETHOD)) allegro_message("error: hardware-rendering is not performed. \n\nTry installing the vendor's newest graphics-card-drivers");
}



int main(void)
{
   int i;
   allegro_init();
   install_allegro_gl();
   init_gfx();
   install_keyboard();
   mysha = load_bitmap("mysha.pcx", NULL);
   if (!mysha)
   {
         allegro_message ("Error loading texture bitmap!");
         exit (1);
   }
	texture = create_sub_bitmap(mysha, 64, 64, 64, 64);
   gl_texture=allegro_gl_make_texture(texture);
   destroy_bitmap(texture);
   set_keyboard_rate(1, 10);
   StGL_font_load("font.3do");
   init_timer();
   limit_fmult(0.06);
   stereo.set_monitor_width(0.475);
   stereo.set_monitor_height(0.295);
   stereo.set_distance_to_monitor(0.55);
   stereo.set_near_clip(0.10);
   stereo.set_far_clip(25.50);
   stereo.set_near_clip(0.01);
   camera_matrix=identity_matrix_f; 
   camera_matrix.t[2]=10;  //kamera ist 10 m vom objekt entfernt
   ///////////
      		   glMultMatrix_allegro(&identity_matrix_f); //hä?????????????????? wenn diese funktion nicht aufgerufen wird, wird nichts angezeigT das macht gar keinen sinn!!!!!

   while (!key[KEY_ESC])				
	{
         r+=30*get_fmult();
         proceed_timer();
         user_input();
         render();
	}
   ///////////
	allegro_exit();
	return 0;
}
END_OF_MAIN();

