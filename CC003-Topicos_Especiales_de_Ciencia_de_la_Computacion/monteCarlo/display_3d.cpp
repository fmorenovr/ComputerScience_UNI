#define GLUT_DISABLE_ATEXIT_HACK
#include<GL/gl.h>
#include<GL/glut.h>
#include<math.h>
#include<vector>
#include<stdio.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include<omp.h>
#include"montecarlo_vol.h"

using namespace std;
#define PI 3.1415926

GLfloat scale = 1;
GLfloat movx = 0, movy = 0;

GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid [NEW]
GLfloat angleCube = 0.0f;     // Rotational angle for cube [NEW]
int refreshMills = 15;        // refresh interval in milliseconds [NEW]

//parámetros de gráfico
const int width=800,height=600,res=8;
const int long_x=400, long_y=300;
const int radius=width/long_x*res/2;
const int s_mit=10;
const int s_mov=3;
const int max_food=50;
int number_of_cells=1;

//parámetros de simulación
const int nn=1;
const int nnp=10000;

//funciones gráficas

void scale_ref(GLfloat s){
	GLfloat tx = width/2*res;
	GLfloat ty = height/2*res;
	glTranslatef(tx,ty,0);
	glScalef(s,s,0);
	glTranslatef(-tx,-ty,0);
	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]
}

void DrawCircle(float cx, float cy, float r, int num_segments){
float theta = 2 * PI / float(num_segments); 
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = r;//we start at angle = 0 
	float y = 0; 
    
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++){ 
		glVertex2f(x + cx, y + cy);//output vertex        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd();  
}

void draw_points(){
	int p;
	
	
}

void begin_sim(int value){
	glutPostRedisplay();
	glutTimerFunc(100,begin_sim,0);
}

void Teclas(unsigned char tecla, GLint x, GLint y){
	float dx = (float)width / 40 * res;
	float dy = (float)height / 40 * res;
	switch(tecla){
		case '+':	scale+=0.2;	break;
		case '-':	scale-=0.2;	break;
		case 'w':	movy-=dx;	break;
		case 's':	movy+=dy;	break;
		case 'a':	movx+=dx;	break;
		case 'd':	movx-=dx;	break;
	}
}

void TeclasEspeciales(GLint tecla, GLint x, GLint y){
	float dx = (float)width / 40 * res;
	float dy = (float)height / 40 * res;
	switch(tecla){
		case GLUT_KEY_UP:		movy-=dy;	break;
		case GLUT_KEY_DOWN:		movy+=dy;	break;
		case GLUT_KEY_LEFT:		movx+=dx;	break;
		case GLUT_KEY_RIGHT:	movx-=dx;	break;
	}
}

void mouseClick(int button, int state, int x, int y){
	float p_x = (float)movx/(res*2);
	float p_y = (float)movy/(res*2);
	float r_x = (float)width/4;
	float r_y = (float)height/4;
	int x_=(float)long_x/width*x;
	int y_=long_y - (float)long_y/height*y;
	x_=(float)(x_-r_x)/scale+r_x-p_x;
	y_=(float)(y_-r_y)/scale+r_y-p_y;
	switch(button){
		case GLUT_LEFT_BUTTON:		break;
		default:	break;
	}
}

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
   glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]
 
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
 
   // Render a pyramid consists of 4 triangles
   glLoadIdentity();                  // Reset the model-view matrix
   glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
   glRotatef(angleCube, 1.0f, 1.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]
 
   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
 
      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
 
      // Back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f, -1.0f, -1.0f);
 
      // Left
      glColor3f(1.0f,0.0f,0.0f);       // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-1.0f,-1.0f, 1.0f);
   glEnd();   // Done drawing the pyramid
 
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
   
   // Update the rotational angle after each refresh [NEW]
   anglePyramid += 0.2f;
   angleCube -= 0.15f;
}

/* Called back when timer expired [NEW] */
void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

int main(int argc, char** argv){
	srand(time(NULL));
	glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Volumen de una esfera con Monte Carlo");          // Create window with the given title
    
    set_nPoints(5000);
    set_nCircles(1);
    start();
    
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutMainLoop();                 // Enter the infinite event-processing loop
    
	/*glutCreateWindow("Volumen de una esfera con Monte Carlo");
	
	//funciones de la librería montecarlo_vol.h
	set_nPoints(100000);
	set_nCircles(1);
		
	glutKeyboardFunc(Teclas);
	glutSpecialFunc(TeclasEspeciales);
	glutMouseFunc(mouseClick);
	
	glutDisplayFunc(display);
	glutTimerFunc(5,begin_sim,0);
	glutMainLoop();*/
	return 0;
}
