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
#include"opengl_graphics.h"

using namespace std;
#define PI 3.1415926

int counter = 0;

int refreshMills = 1;        // refresh interval in milliseconds [NEW]

//parámetros de simulación
const double G=1;		//gravitational constant
const double delta=2.7;	//minimal distance between bodies
const int nbodies=500;
const int dimension=2;
const double dt=0.2;

const int range=500;

//define objects

class body{
	public:
	double m,ek,ep,r;
	double x,y,z;
	double vx,vy,vz;
	double ax,ay,az;
	double color[3];
	
	body(){}
	
	void init_pos(double x, double y, double z, double m, double r){
		this->x=x;
		this->y=y;
		this->z=z;
		this->m=m;this->r=r;
	}
	
	void init_vel(double vx, double vy, double vz){
		this->vx=vx;
		this->vy=vy;
		this->vz=vz;
	}
	
	void set_color(float r, float g, float b){
		color[0]=r;
		color[1]=g;
		color[2]=b;
	}
	
	void reboot(){
		ax=ay=az=0;
		ep=0;
	}
	
	void energy(){
		ek=0.5*m*vx*vx;
		ep*=m;
	}
	
	void calculate(body b){
		double d=sqrt(pow(x-b.x,2)+pow(y-b.y,2)+pow(z-b.z,2));
		if(d<delta) d=delta;
		ax=ax+G*b.m*(b.x-x)/pow(d,3);
		ay=ay+G*b.m*(b.y-y)/pow(d,3);
		az=az+G*b.m*(b.z-z)/pow(d,3);
		ep+=G*b.m*0.5/d;
	}
	void update(){
		//update velocities
		vx=vx+ax*dt;
		vy=vy+ay*dt;
		vz=vz+az*dt;
		//update positions
		x=x+vx*dt+0.5*ax*dt*dt;
		y=y+vy*dt+0.5*ay*dt*dt;
		z=z+vz*dt+0.5*az*dt*dt;
	}
};

body *cuerpo = new body[nbodies];

void init_nbody(){
	double v1,v2,v3,v,d,x,y;
	#pragma omp parallel for
	for(int i=0; i<nbodies-1; i++){
		if(dimension==3)
			cuerpo[i].init_pos(randf(0,range),randf(0,range),randf(0,range),7,1);
		else if(dimension==2)
			cuerpo[i].init_pos(randf(0,range),randf(0,range),range/2,8,2);
		x=cuerpo[i].x-range/2;
		y=cuerpo[i].y-range/2;
		d=sqrt(pow(x,2)+pow(y,2));
		v=pow(1,rand())*randf(10,15)*exp(((x*x+y*y)/pow(range,6)));
		v1=v*(-y/d);
		v2=v*(x/d);
		v3=0;
		cuerpo[i].init_vel(v1,v2,v3);
		cuerpo[i].set_color(randf(0.5,1),0.0,randf(0.5,1));
	}
	cuerpo[nbodies-1].init_pos(range/2,range/2,range/2,50000,5);
	cuerpo[nbodies-1].init_vel(0,0,0);
	cuerpo[nbodies-1].set_color(1.0,0.0,0.0);
	
}

void sim(){
	for(int i=0; i<nbodies; i++){
		cuerpo[i].reboot();
		for(int j=0; j<nbodies; j++){
			if(j!=i){
				cuerpo[i].calculate(cuerpo[j]);
			}
		}
		cuerpo[nbodies-1].vx=0;cuerpo[nbodies-1].ax=0;
		cuerpo[nbodies-1].vy=0;cuerpo[nbodies-1].ay=0;
		cuerpo[nbodies-1].vz=0;cuerpo[nbodies-1].az=0;
		cuerpo[i].energy();
		cuerpo[i].update();
	}
}

/* Initialize OpenGL Graphics */
void initGL(){
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
    gluOrtho2D(0,range,0,range);	//plano cartesiano
    
    sim();
    
	scale_ref(range,scale);
	glTranslatef(movx,movy,0);
	rotate_ref(range,ang_x,0);
	rotate_ref(range,ang_y,1);
	rotate_ref(range,ang_z,2);
	
 	for(int i=nbodies-1;i>-1;i--){
 		glColor3f(cuerpo[i].color[0], cuerpo[i].color[1], cuerpo[i].color[2]);
 		DrawSphere(cuerpo[i].x, cuerpo[i].y, cuerpo[i].z, cuerpo[i].r);
 		//printf("%f %f %f \n",cuerpo[i].color[0], cuerpo[i].color[1], cuerpo[i].color[2]);
	}
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
    
    
    // Update the rotational angle after each refresh [NEW]
   // anglePyramid += 0.2f;
    //angleCube -= 0.15f;
}

/* Called back when timer expired [NEW] */
void timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

void reshape(GLsizei w, GLsizei h) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (h == 0) h = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)w / (GLfloat)h;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, w, h);
 
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
    glutInitWindowSize(800, 800);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Simulación de n cuerpos");          // Create window with the given title
    init_nbody();
    glutKeyboardFunc(Teclas);
	glutSpecialFunc(TeclasEspeciales);
	glutMouseFunc(mouseClick);
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    //glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
    glutMainLoop();                 // Enter the infinite event-processing loop
    
	return 0;
}
