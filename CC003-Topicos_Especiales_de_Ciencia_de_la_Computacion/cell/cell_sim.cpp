#include<GL/gl.h>
#include<GL/glut.h>
#include<math.h>
#include<fstream>
#include<vector>
#include<stdio.h>
#include<time.h>
#include<algorithm>
#include<iostream>
#include<omp.h>
using namespace std;
#define PI 3.1415926

GLfloat scale = 1;
GLfloat movx = 0, movy = 0;

//parámetros de gráfico
const int width=408,height=804,res=4;
const int long_x=204, long_y=402;
const int radius=width/long_x*res/2;
const int s_mit=10;
const int s_mov=3;
const int max_food=50;
const int max_pulse=2;
int number_of_cells=1;
long tiempo=0;

//parámetros de célula
const int init_x = 102, init_y = 201;
const int max_life = 5000000;
const int max_mit_init = 50; // max number of mitosis

typedef struct cell{
	bool draw;
	bool pre_draw;
	int time_life;
	int max_mit;
	int num_mit;
	float rad;
	bool mitosis, move;
	int to_mit, to_mov;
	int mit_s, mov_s;
	float grown_rate;
	bool blocked;	//usado para simulación con bloques
}cell;

typedef struct pulse{
	bool draw;
}pulse;

pulse p[long_x][long_y];
cell c[long_x][long_y];
float food[long_x][long_y];

void DrawFilledCircle(GLfloat x, GLfloat y, GLfloat rad, int triangleAmount){
	int i;
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(x + (rad * cos(i *  twicePi / triangleAmount)), 
			    y + (rad * sin(i * twicePi / triangleAmount)));
		}
	glEnd();
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

void draw_container(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_LINE_LOOP);
		glVertex2f(0,0);
		glVertex2f(0,res*height);
		glVertex2f(res*width,res*height);
		glVertex2f(res*width,0);
		glVertex2f(0,0);
	glEnd();
}

void draw_cells(){
	float rad;
	int x,y,t_step;
	float color;
	for(int i=0; i<long_x;i++)
		for(int j=0;j<long_y;j++){
			x=radius*(1+2*i);
			y=radius*(1+2*j);
			if(c[i][j].blocked){
				glColor3f(1,1,1);
				DrawFilledCircle(x,y,radius,10);
			}
			else if(c[i][j].draw){
				rad=c[i][j].rad;
				color = (float)max_life/(max_life+c[i][j].time_life);
				glColor3f(color,color,0);
				if(c[i][j].mitosis){
					t_step=c[i][j].mit_s*2*rad/s_mit;
					c[i][j].rad/=pow(2,0.5/s_mit);
					switch(c[i][j].to_mit){
						case 1: DrawFilledCircle(x-t_step,y-t_step,rad,10); break;
						case 2: DrawFilledCircle(x,y-t_step,rad,10); break;
						case 3: DrawFilledCircle(x+t_step,y-t_step,rad,10); break;
						case 4: DrawFilledCircle(x-t_step,y,rad,10); break;
						case 6: DrawFilledCircle(x+t_step,y,rad,10); break;
						case 7: DrawFilledCircle(x-t_step,y+t_step,rad,10); break;
						case 8: DrawFilledCircle(x,y+t_step,rad,10); break;
						case 9: DrawFilledCircle(x+t_step,y+t_step,rad,10); break;
						default: break;
					}
				}
				if(c[i][j].move){
					t_step=c[i][j].mov_s*2*rad/s_mov;
					color = (float)max_life/(max_life+c[i][j].time_life);
					glColor3f(color,color,0);
					switch(c[i][j].to_mov){
						case 1: DrawFilledCircle(x-t_step,y-t_step,rad,10); break;
						case 2: DrawFilledCircle(x,y-t_step,rad,10); break;
						case 3: DrawFilledCircle(x+t_step,y-t_step,rad,10); break;
						case 4: DrawFilledCircle(x-t_step,y,rad,10); break;
						case 6: DrawFilledCircle(x+t_step,y,rad,10); break;
						case 7: DrawFilledCircle(x-t_step,y+t_step,rad,10); break;
						case 8: DrawFilledCircle(x,y+t_step,rad,10); break;
						case 9: DrawFilledCircle(x+t_step,y+t_step,rad,10); break;
						default: break;
					}
				}
				else{
					DrawFilledCircle(x,y,rad,10);
				}
			}
			else if(p[i][j].draw){
				glColor3f(0,color,0);
				DrawFilledCircle(x,y,1.5f*radius,10);
			}
			else if(!c[i][j].pre_draw){
				float color = (float)food[i][j]/(max_food+1)*2;
				glColor3f(color,color/4,color/4);
				DrawFilledCircle(x,y,1.5f*radius,10);
			}
		}
}
void draw_pulse(){
	float color = 1;
	for(int i=0; i<long_x;i++)
		for(int j=0;j<long_y;j++){
			if(p[i][j].draw && !c[i][j].blocked){
				int x=radius*(1+2*i);
				int y=radius*(1+2*j);
				glColor3f(0,color,0);
				DrawFilledCircle(x,y,1.5f*radius,10);
			}
		}
}

void draw_food(){
	for(int i=0; i<long_x;i++)
		for(int j=0;j<long_y;j++){
			if(!c[i][j].blocked){
				int x=radius*(1+2*i);
				int y=radius*(1+2*j);
				float color = (float)food[i][j]/(max_food+1)*2;
				glColor3f(color,color/4,color/4);
				DrawFilledCircle(x,y,1.5f*radius,10);
			}
		}
}

void scale_ref(GLfloat s){
	GLfloat tx = width/2*res;
	GLfloat ty = height/2*res;
	glTranslatef(tx,ty,0);
	glScalef(s,s,0);
	glTranslatef(-tx,-ty,0);
}

void malla(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	//para no perder las dimensiones
	gluOrtho2D(0,res*width,0,res*height);	//plano cartesiano
	
	//glScalef(scale,scale,0);
	scale_ref(scale);
	glTranslatef(movx,movy,0);
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();	//para no perder las dimensiones
	//draw_food();
	//draw_pulse();
	draw_cells();
	draw_container();
	glFlush();
}

int check_direction(float x, float y){
	float s=atan2(y,x)*180/PI;
	if(s<0)
		s+=360;
	if(s<22.5 || s>337.5)
		return 6;
	else if (s<67.5)
		return 9;
	else if(s<112.5)
		return 8;
	else if(s<157.5)
		return 7;
	else if(s<202.5)
		return 4;
	else if(s<247.5)
		return 1;
	else if(s<292.5)
		return 2;
	else
		return 3;
}

int look_for_mitosis(int x, int y){
	// tomaremos en cuenta la posición del teclado númerico
	bool flag=false;
	int deep=1;
	int x_end,y_end,x_ini,y_ini;
	int rep[2],r;
	int s;
	vector <int> t1;
	vector <int> t2;
	
	x_end=(x+deep)*(x+deep<long_x)+(long_x-1)*(x+deep>=long_x);
	y_end=(y+deep)*(y+deep<long_y)+(long_y-1)*(y+deep>=long_y);
	x_ini=(x-deep)*(x>deep);
	y_ini=(y-deep)*(y>deep);
	
	for(int i=x_ini ; i<=x_end ; i++)
		for(int j=y_ini ; j<=y_end ; j++)
			if(!c[i][j].draw && (i!=x || j!=y) && !c[i][j].pre_draw && !c[i][j].blocked){
				t1.push_back(i);
				t2.push_back(j);
			}
	if(t1.size()>0){
		r=rand()%(t1.size());
		rep[0]=t1[r];
		rep[1]=t2[r];
		s=check_direction(rep[0]-x,rep[1]-y);
		//printf("dir of %d,%d to %d,%d -> %d\n",x,y,rep[0]-x,rep[1]-y,s);
		return s;
	}
	return 5;
}

void reserve_space(int i,int j,int s,bool acction){
	switch(s){
		case 1: c[i-1][j-1].pre_draw=acction;
				break;
		case 2: c[i][j-1].pre_draw=acction;
				break;
		case 3: c[i+1][j-1].pre_draw=acction;
				break;
		case 4: c[i-1][j].pre_draw=acction;
				break;
		case 6: c[i+1][j].pre_draw=acction;
				break;
		case 7: c[i-1][j+1].pre_draw=acction;
				break;
		case 8: c[i][j+1].pre_draw=acction;
				break;
		case 9: c[i+1][j+1].pre_draw=acction;
				break;
		default: break;
	}
}

void update_cell(int i, int j, int type){
	int s;
	c[i][j].pre_draw=false;
	if(type == 0){		// 0 = mit , 1 = mov
		c[i][j].mitosis=false;
		c[i][j].num_mit++;
		c[i][j].rad=radius;
		s=c[i][j].to_mit;
		if(c[i][j].num_mit == c[i][j].max_mit){
			c[i][j].max_mit*=0.9;
			c[i][j].num_mit=0;
		}
	}
	else{
		c[i][j].move=false;
		s=c[i][j].to_mov;
	}
	switch(s){
		case 1: c[i-1][j-1]=c[i][j];
				break;
		case 2: c[i][j-1]=c[i][j];
				break;
		case 3: c[i+1][j-1]=c[i][j];
				break;
		case 4: c[i-1][j]=c[i][j];
				break;
		case 6: c[i+1][j]=c[i][j];
				break;
		case 7: c[i-1][j+1]=c[i][j];
				break;
		case 8: c[i][j+1]=c[i][j];
				break;
		case 9: c[i+1][j+1]=c[i][j];
				break;
		default: break;
	}
	//printf("cell: %d,%d to %d\n",i,j,s);
	if(type==0)
		c[i][j].time_life=0;
	else
		c[i][j].draw=false;
}

/*int check_food(int x, int y){
	int deep=1;
	int x_end,y_end,x_ini,y_ini;
	int r[2];
	int s;
	vector <int> t1;
	vector <int> t2;
	
	x_end=(x+deep)*(x+deep<long_x)+(long_x-1)*(x+deep>=long_x);
	y_end=(y+deep)*(y+deep<long_y)+(long_y-1)*(y+deep>=long_y);
	x_ini=(x-deep)*(x>deep);
	y_ini=(y-deep)*(y>deep);
	float dx,dy,ddx=0,ddy=0;
	//se influye por la dirección de la comida
	for(int i=x_ini ; i<=x_end ; i++)
		#pragma omp parallel for
		for(int j=y_ini ; j<=y_end ; j++){
			//if(!c[i][j].draw && (i!=x || j!=y) && !c[i][j].pre_draw){
			#pragma omp atomic
			ddx+=(float)(i-x)*food[i][j];
			#pragma omp atomic
			ddy+=(float)(j-y)*food[i][j];
			if(p[i][j].draw){
				dx=(float)(x-i)/1280;
				dy=(float)(y-j)/1280;
				#pragma omp atomic
				ddx+=-100*dx*exp(-(dx*dx+dy*dy));
				#pragma omp atomic
				ddy+=-100*dy*exp(-(dx*dx+dy*dy));
			}
		}
	//se influencia por los pulsos
	for(int i=0 ; i<long_x ; i++)
		#pragma omp parallel for
		for(int j=0 ; j<long_y ; j++)
			if(p[i][j].draw){
				dx=(float)(x-i)/1280;
				dy=(float)(y-j)/1280;
				ddx+=-100*dx*exp(-(dx*dx+dy*dy));
				ddy+=-100*dy*exp(-(dx*dx+dy*dy));
				printf("ddx= %.4f\n",ddx);
				printf("ddy= %.4f\n",ddy);
			}
	
	//consigue la dirección
	if(ddx==0 && ddy==0)
		s=5;
	else
		s=check_direction(ddx,ddy);
	//comprueba si se puede mover en dicha dirección
	bool move=false;
	int i=x,j=y;
	for(int ii=0;ii<1;ii++){	
		switch(s){
			case 1: move=!(c[i-1][j-1].draw || c[i-1][j-1].pre_draw || c[i-1][j-1].blocked);
					break;
			case 2: move=!(c[i][j-1].draw || c[i][j-1].pre_draw || c[i][j-1].blocked);
					break;
			case 3: move=!(c[i+1][j-1].draw || c[i+1][j-1].pre_draw || c[i+1][j-1].blocked);
					break;
			case 4: move=!(c[i-1][j].draw || c[i-1][j].pre_draw || c[i-1][j].blocked);
					break;
			case 6: move=!(c[i+1][j].draw || c[i+1][j].pre_draw || c[i+1][j].blocked);
					break;
			case 7: move=!(c[i-1][j+1].draw || c[i-1][j+1].pre_draw || c[i-1][j+1].blocked);
					break;
			case 8: move=!(c[i][j+1].draw || c[i][j+1].pre_draw || c[i][j+1].blocked);
					break;
			case 9: move=!(c[i+1][j+1].draw || c[i+1][j+1].pre_draw || c[i+1][j+1].blocked);
					break;
			default: break;
		}
		if(move)
			return s;
		else{//última oportunidad de moverse
			s=(rand()%4+1)+5*(rand()%2);
			//printf("Next move: %d\n",s);
		}
	}
	return 5;
}*/

int check_food(int x, int y){
	int deep=1;
	int x_end,y_end,x_ini,y_ini;
	int r[2];
	int s;
	vector <int> t1,sx;
	vector <int> t2,sy;
	
	x_end=(x+deep)*(x+deep<long_x)+(long_x-1)*(x+deep>=long_x);
	y_end=(y+deep)*(y+deep<long_y)+(long_y-1)*(y+deep>=long_y);
	x_ini=(x-deep)*(x>deep);
	y_ini=(y-deep)*(y>deep);
	for(int i=x_ini ; i<=x_end ; i++)
		for(int j=y_ini ; j<=y_end ; j++)
			if(!c[i][j].draw && (i!=x || j!=y) && !c[i][j].pre_draw && !c[i][j].blocked){
				t1.push_back(i);
				t2.push_back(j);
			}
	
	if(t1.size()>0){
		float fd=food[x][y];
		s=-1;
		for(int i=0; i<t1.size() ; i++){
			if(fd<food[t1[i]][t2[i]]){
				s=i;
				fd=food[t1[i]][t2[i]];
				r[0]=t1[i];
				r[1]=t2[i];
			}
		}
		if(s!=-1){
			s=check_direction(r[0]-x,r[1]-y);
			return s;
		}
		else
			return 5;
	}
	else
		return 5;
}

void move(int i, int j, int s){
	
	switch(s){
		case 1: c[i-1][j-1]=c[i][j];
				break;
		case 2: c[i][j-1]=c[i][j];
				break;
		case 3: c[i+1][j-1]=c[i][j];
				break;
		case 4: c[i-1][j]=c[i][j];
				break;
		case 6: c[i+1][j]=c[i][j];
				break;
		case 7: c[i-1][j+1]=c[i][j];
				break;
		case 8: c[i][j+1]=c[i][j];
				break;
		case 9: c[i+1][j+1]=c[i][j];
				break;
		default: break;
	}
}

void put_pulse(int lx, int ly){
	p[lx][ly].draw=true;
}

void begin_sim(int value){
	double start = omp_get_wtime();
	//#pragma omp parallel for
		for(int i=0; i<long_x;i++){
			for(int j=0;j<long_y;j++){
				if(c[i][j].draw && !c[i][j].blocked){
					//célula envejece
					c[i][j].time_life++;
					//comprueba si está lo suficientemente grande para hacer mitosis
					if(c[i][j].rad>=radius*sqrt(2) && !c[i][j].mitosis && !c[i][j].move){
						c[i][j].to_mit=look_for_mitosis(i,j);
						if(c[i][j].to_mit!=5){
							c[i][j].mitosis=true;
							reserve_space(i,j,c[i][j].to_mit,true);
						}
					}
					if(!c[i][j].mitosis){
						if(food[i][j]>0){
							//célula crece
							if(c[i][j].rad<radius*sqrt(2)){	//si la célula está muy grande ya no se alimenta tan rápido
								c[i][j].rad+=(float)(c[i][j].grown_rate<food[i][j]?c[i][j].grown_rate:food[i][j])*(0.95f+1.0f*(rand()%10)/10);
								food[i][j]-=c[i][j].grown_rate;
							}
							else{
								food[i][j]-=c[i][j].grown_rate/50;
							}
						}	
						else
							c[i][j].time_life+=max_life/250;	//envejece mas rápido si no hay comida
							
						food[i][j]=food[i][j]<0?0:food[i][j];
							
						if(!c[i][j].move){
							c[i][j].to_mov=check_food(i,j);			//busca donde hay mas comida
							if(c[i][j].to_mov!=5){
								c[i][j].move=true;
								reserve_space(i,j,c[i][j].to_mov,true);
							}
						}
					}
					
					if(c[i][j].move)
						c[i][j].mov_s++;
					
					if(c[i][j].mitosis)
						c[i][j].mit_s++;
						
					if(c[i][j].mit_s>s_mit){
						c[i][j].mit_s=0;
						update_cell(i,j,0);
		//				#pragma omp atomic
						number_of_cells++;
					}
					if(c[i][j].mov_s>s_mov){
						c[i][j].mov_s=0;
						update_cell(i,j,1);
					}
					if(c[i][j].time_life>max_life && !c[i][j].mitosis){
						c[i][j].draw=false;
						c[i][j].pre_draw=false;
						if(c[i][j].mitosis)
							reserve_space(i,j,c[i][j].to_mov,false);
						if(c[i][j].move)
							reserve_space(i,j,c[i][j].to_mit,false);
	//					#pragma omp atomic
						number_of_cells--;
					}
				}
			}
		}
//	printf("Tiempo de simulación: %9.0lf ms with %d cells \n",(omp_get_wtime()-start)*1000,number_of_cells);
//	tiempo++;
	glutPostRedisplay();
	glutTimerFunc(1,begin_sim,0);
//	printf("tiempo=%ld\n",tiempo);
}

void put_food(int lx, int ly){
	int x,y;
	int ep;
	if(!c[lx][ly].blocked)
		for(int i=0; i<long_x;i++)
//			#pragma omp parallel for
			for(int j=0;j<long_y;j++){
				x=i-lx;
				y=j-ly;
				ep=pow(x,2)+pow(y,2);
				food[i][j]+=exp(ep/(-pow(2,6)))*max_food/4;
				//food[i][j]+=sin(ep*tiempo)*exp(ep/(-pow(8,4)))*max_food/10;
				food[i][j]=food[i][j]>max_food*.75f?max_food*.75f:food[i][j];
				//food[i][j]=food[i][j]<0.01?0.01:food[i][j];
			}
		
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
	//printf("movy: %f\n",movy);
	//float p_x = (float)width/long_x/8*movx;
	//float p_y = (float)height/long_y/8*movy;
	float p_x = (float)movx/(radius*2);
	float p_y = (float)movy/(radius*2);
	float r_x = (float)long_x/2;
	float r_y = (float)long_y/2;
	//int x_=((float)long_x/width*(x-p_x))/(scale);
	//int y_=(long_y - (float)long_y/height*(y+p_y))/scale;
	int x_=(float)long_x/width*x;
	int y_=long_y - (float)long_y/height*y;
	x_=(float)(x_-r_x)/scale+r_x-p_x;
	y_=(float)(y_-r_y)/scale+r_y-p_y;
	if(state == 0)		//state = 0 al presionar click, state = 1 al soltar el click
		switch(button){
			case GLUT_LEFT_BUTTON:	//printf("x_: %d\tx: %d\n",x_,x);
									//printf("y_: %d\ty: %d\n",y_,y);
									put_food(x_,y_);	break;
			case GLUT_RIGHT_BUTTON:	put_pulse(x_,y_);	break;
			default:	break;
		}
}

void blocks(string x){
	int i,j,k,m;
	if(x=="")
//		#pragma omp parallel for
		for(j=0;j<long_y;j++)
			for(i=0;i<long_x;i++)
				c[i][j].blocked=false;
	else{
		ifstream myfile(x.c_str());
		string line;
		/*int lines=0,cols;
		if (myfile.is_open()){
    		while (!myfile.eof() ){
      			getline(myfile,line);
    			lines++;
    			cols=line.length();
  			}
  			myfile.close();
		}*/
		myfile.close();
		myfile.open(x.c_str());
		//reajustamos el phantom
		int f_x,f_y,l=0;
		/*f_x=ceil((float)long_x/cols);
		f_y=ceil((float)long_y/lines);*/
		//printf("lines=%d cols=%d\n",lines,cols);
		//printf("sx=%d sy=%d\n",f_x,f_y);
		char letra;
		//for(j=long_y-1;j>=0;j-=f_y){
		for(j=0;j<long_y;j++){
			//repite hasta completar la altura
			//for(i=0;i<long_x;i+=f_x){
			for(i=0;i<long_x;i++){
				myfile.get(letra);
				//l++;
				if(letra == ' ')
					c[i][j].blocked=true;
				else
					c[i][j].blocked=false;
				/*for(k=0;k<f_x;k++){
					c[i+k][j].blocked=c[i][j].blocked;
					for(m=0;m<f_y;m++){
						c[i+k][j-m].blocked=c[i][j].blocked;
					}
				}*/
			}
			myfile.get(letra);
			myfile.get(letra);
			//printf("\n");
		}
		//printf("leido=%d\n",l);
		myfile.close();
	}
	/*FILE *g;
	g=fopen("silhouette.txt","w");
	for(i=0;i<long_y;i++){
		for(j=0;j<long_x;j++)
			if(c[j][i].blocked)
				fprintf(g," ");
			else
				fprintf(g,"@");
		fprintf(g,"\n");
	}
	fclose(g);*/
}

int main(int argc, char **argv){
	//necessary for ubuntu compiler
	glutInit(&argc, argv);
	
	srand(time(NULL));
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width,height);
	glutInitWindowPosition(400,0);
	glutCreateWindow("Simulación de Células");
	
	glutKeyboardFunc(Teclas);
	glutSpecialFunc(TeclasEspeciales);
	glutMouseFunc(mouseClick);
	//inicia phantom o bloqueo
	blocks("silhouette.txt");
	
	
	put_food(init_x,init_y);
	c[init_x][init_y].draw = true;
	c[init_x][init_y].rad = radius;
	c[init_x][init_y].move = false;
	c[init_x][init_y].pre_draw = true;
	c[init_x][init_y].time_life = 0;
	c[init_x][init_y].num_mit = 0;
	c[init_x][init_y].max_mit = max_mit_init;
	c[init_x][init_y].rad=radius;
	c[init_x][init_y].mitosis = false;
	c[init_x][init_y].grown_rate = 0.2;
	
	draw_container();
	glutDisplayFunc(malla);
	glutTimerFunc(5,begin_sim,0);
	glClearColor(0,0,0,0);
	glutMainLoop();
	return 0;
}
