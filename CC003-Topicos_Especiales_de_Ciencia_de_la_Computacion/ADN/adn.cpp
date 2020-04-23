#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH 1000
#define HEIGHT 900
#define PI 3.1415926

void *fonts[]={
  GLUT_BITMAP_9_BY_15,
  GLUT_BITMAP_TIMES_ROMAN_10,
  GLUT_BITMAP_TIMES_ROMAN_24,
  GLUT_BITMAP_HELVETICA_18,
  GLUT_BITMAP_HELVETICA_12
};

float theta=1;

//impresion de texto
void output(int x, int y, char *string, void *font){
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}
//dibuja hebra
void drawHelixStrand(float cx, float cy, float r, float angle=0){
  float x, y, z, theta;
  int i, n = 620;
  angle = angle * PI / 180.0;
  glBegin(GL_LINE_STRIP);
  for(i=0; i<n; i++){
    theta = 2.0 * PI * i / n;
    x = cx - (r * sinf(1 * theta + angle));
    y = cy + i;
    z = r * cosf(1 * theta + angle);
    glVertex3f(x, y, z);
  }
  glEnd();
}
//dibuja fosfato
void drawSphere(float x, float y, float z, float r=7){
  glTranslatef(x, y, z);
  glutSolidSphere(r, 20, 20);
  glTranslatef(-x, -y, -z);
}
//dibuja linea
void drawHelixLine(float cx, float cy, float r, float angle=180){
  float x1, x2, y1, y2, z1, z2, theta;
  int i, n = 620, k=0;
  GLubyte colors[2][3];
  angle = angle * PI / 180.0;
  for(i=0; i<n; i+=n/14){
    theta = 2.0 * PI * i / n;
    x1 = cx - (r * sinf(1 * theta));
    y1 = cy + i;
    z1 = r * cosf(1 * theta);

    x2 = cx - (r * sinf(1 * theta + angle));
    y2 = cy + i;
    z2 = r * cosf(1 * theta + angle);

    switch(k){
      case 0:
        colors[0][0] = 46; colors[0][1] = 204; colors[0][2] = 113;		//turquesa
        colors[1][0] = 249; colors[1][1] = 148; colors[1][2] = 6;		//naranja
        break;
    	case 1:
    	  colors[0][0] = 249; colors[0][1] = 191; colors[0][2] = 59;		//amarillo
        colors[1][0] = 155; colors[1][1] = 89; colors[1][2] = 182;		//morado
        break;
    	case 2:
        colors[0][0] = 249; colors[0][1] = 148; colors[0][2] = 6;
        colors[1][0] = 46; colors[1][1] = 204; colors[1][2] = 113;
        break;
    	case 3:
        colors[0][0] = 155; colors[0][1] = 89; colors[0][2] = 182;
        colors[1][0] = 249; colors[1][1] = 191; colors[1][2] = 59;
    }
    glBegin(GL_LINE_STRIP);

    glColor3ubv(colors[0]);
    glVertex3f(x1, y1, z1);
    glVertex3f((x1+x2)/2, (y1+y2)/2, (z1+z2)/2);
    glColor3ubv(colors[1]);
    glVertex3f((x1+x2)/2, (y1+y2)/2, (z1+z2)/2);
    glVertex3f(x2, y2, z2);

    glEnd();

    glColor3ub(52, 73, 94);
    drawSphere(x1, y1, z1);
    drawSphere(x2, y2, z2);

    k++;
    if (k>3) k=0;
  }
}


void dna(){
  float cx = -500, cy = 50, r=100;
  glLineWidth(5.0);
  glPushMatrix();   
  glRotatef(-90, 0, 0, 1);
  glPushMatrix();
  glTranslatef(cx, cy, 0);
  glRotatef(theta, 0.0, 1.0, 0.0);

  glColor3ub(52, 152, 219);
  drawHelixStrand(0, cy, r, 0);
  glColor3ub(231, 76, 60);
  drawHelixStrand(0, cy, r, 138);
  drawHelixLine(0, cy, r, 138);

  glTranslatef(-cx, -cy, 0); 

  glPopMatrix();

  glPopMatrix();

  theta+=0.75;
  glPushMatrix();
  glTranslatef(50, -100, 0);
  drawSphere(35, 400, 0);
  output(70, 395, "Fosfato Base", fonts[2]);

  glBegin(GL_LINES);
  glColor3ub(46, 204, 113);
  glVertex2f(25, 360);
  glVertex2f(50, 360);
  glEnd();
  glColor3ub(52, 73, 94);
  output(70, 355, "Adenina", fonts[2]);

  glBegin(GL_LINES);
  glColor3ub(249, 148, 6);
  glVertex2f(25, 320);
  glVertex2f(50, 320);
  glEnd();
  glColor3ub(52, 73, 94);
  output(70, 315, "Timina", fonts[2]);

  glBegin(GL_LINES);
  glColor3ub(249, 191, 59);
  glVertex2f(25, 280);
  glVertex2f(50, 280);
  glEnd();
  glColor3ub(52, 73, 94);
  output(70, 275, "Citosina", fonts[2]);

  glBegin(GL_LINES);
  glColor3ub(155, 89, 182);
  glVertex2f(25, 240);
  glVertex2f(50, 240);
  glEnd();
  glColor3ub(52, 73, 94);
  output(70, 235, "Guanina", fonts[2]);
  glPopMatrix();
}

void display(void){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1000, 0.0, 650,-2000,1500);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(1, 1, 1, 1);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  dna();
  glFlush();
  glutSwapBuffers();
}

void reshape (int width ,int height){
  const float ar_origin = (float) WIDTH / (float) HEIGHT;
  const float ar_new = (float) width / (float) height;

  float scale_w = (float) width / (float) WIDTH;
  float scale_h = (float) height / (float) HEIGHT;
  if (ar_new > ar_origin) {
    scale_w = scale_h;
  } else {
    scale_h = scale_w;
  }

  float margin_x = 0;
  float margin_y = 0;

  glViewport(margin_x, margin_y, WIDTH * scale_w, HEIGHT * scale_h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH / ar_origin, 0, HEIGHT / ar_origin, 0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize(1000,900);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Simulacion ADN");
  glutDisplayFunc(display);
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 0;
}
