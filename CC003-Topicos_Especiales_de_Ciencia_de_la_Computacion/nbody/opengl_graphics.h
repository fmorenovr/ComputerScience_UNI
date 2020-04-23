#include<GL/gl.h>
#include<GL/glut.h>
#include<math.h>

const double PI = 3.14159265359;

GLfloat scale = 1;
GLfloat movx = 0, movy = 0, movz = 0;
GLfloat ang_x=0, ang_y=0, ang_z=0;

//parámetros de gráfico
const int width=2,height=2;

void scale_ref(double range, GLfloat s){
	GLfloat tx = range/2;
	GLfloat ty = range/2;
	GLfloat tz = range/2;
	glTranslatef(tx,ty,0);
	glScalef(s,s,0);
	glTranslatef(-tx,-ty,0);
}

void rotate_ref(double range, GLfloat s, int t){
	GLfloat tx = range/2;
	GLfloat ty = range/2;
	GLfloat tz = range/2;
	glTranslatef(tx,ty,tz);
	switch(t){
		case 0:	glRotatef(s, 1.0f, 0.0f, 0.0f);	break;
		case 1:	glRotatef(s, 0.0f, 1.0f, 0.0f);	break;
		case 2:	glRotatef(s, 0.0f, 0.0f, 1.0f);	break;
	}
	glTranslatef(-tx,-ty,-tz);
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



void DrawCircle3D(float cx, float cy, float cz, float r, int num_segments){
float theta = 2 * PI / float(num_segments); 
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = r;//we start at angle = 0 
	float y = 0; 
    
	glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++){
		glVertex3f(x + cx, y + cy, cz);//output vertex        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd();  
}

void Teclas(unsigned char tecla, GLint x, GLint y){
	float dx = (float)10;
	float dy = (float)10;
	float dz = (float)10;
	float ang = (float)1;
	switch(tecla){
		case '+':	scale+=0.02;	break;
		case '-':	scale-=0.02;	break;
		case 'w':	movy-=dy;	break;
		case 's':	movy+=dy;	break;
		case 'a':	movx+=dx;	break;
		case 'd':	movx-=dx;	break;
		case '1':	movz+=dz;	break;
		case '2':	movz-=dz;	break;
		//rotation
		
		case 'q':	ang_x-=ang;	break;
		case 'e':	ang_x+=ang;	break;
		case 'z':	ang_y-=ang;	break;
		case 'x':	ang_y+=ang;	break;
		case 'c':	ang_z-=ang;	break;
		case 'v':	ang_z+=ang;	break;
	}
}

void TeclasEspeciales(GLint tecla, GLint x, GLint y){
	float dx = (float)width / 40;
	float dy = (float)height / 40;
	switch(tecla){
		case GLUT_KEY_UP:		movy-=dy;	break;
		case GLUT_KEY_DOWN:		movy+=dy;	break;
		case GLUT_KEY_LEFT:		movx+=dx;	break;
		case GLUT_KEY_RIGHT:	movx-=dx;	break;
	}
}

void mouseClick(int button, int state, int x, int y){
	float p_x = (float)movx/(2);
	float p_y = (float)movy/(2);
	float r_x = (float)width/4;
	float r_y = (float)height/4;
	
	switch(button){
		case GLUT_LEFT_BUTTON:		break;
		default:	break;
	}
}

void DrawSphere(double x, double y, double z, double r){
	glTranslatef(x,y,z);
		glutSolidSphere(r,20,20);
	glTranslatef(-x,-y,-z);
}
