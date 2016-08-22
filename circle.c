#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
double factor = ((3.14159265)/180);
void DrawArc(double start_angle,double end_angle,double x,double y,double r)
{
	double angle;
	start_angle = start_angle * factor;
	end_angle = end_angle * factor;
	glBegin(GL_POLYGON);
	glVertex2d(x,y);
	for ( angle = start_angle; angle <= end_angle; angle+=factor)
	{
		glVertex2d(x+(r*cos(angle)),y+(r*sin(angle)));
	}
	glVertex2d(x,y);
	glEnd();
	glFlush();
}
DrawBall(double x,double y,double r)
{
	glColor3f(0.0,0.0,0.0);
	DrawArc(0.0,90.0,x,((0.2*(x-250))/0.2)-(((0.5*pow((x-250),2))/(2*pow(2,2)))),r);
	glColor3f(0.0,0.0,1.0);
	DrawArc(90.0,180.0,x,((0.2*(x-250))/0.2)-(((0.5*pow((x-250),2))/(2*pow(2,2)))),r);
	glColor3f(1.0,1.0,0.0);
	DrawArc(180.0,270.0,x,((0.2*(x-250))/0.2)-(((0.5*pow((x-250),2))/(2*pow(2,2)))),r);
	glColor3f(0.0,1.0,0.0);
	DrawArc(270.0,360.0,x,((0.2*(x-250))/0.2)-(((0.5*pow((x-250),2))/(2*pow(2,2)))),r);
}
double k=250,l=250;
double r=50,flag=0;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	DrawBall(k,l,r);
	if(flag==0)
	{
		if((k+r)<=500)
		{
			k=k+10;
	 	}
		 
		if((k+r)>=500)
		{
			flag=1;
		}
	}
		 
	if(flag==1)
	{
		k=k-10;
		if((k-r)<=0)
		{
			flag=0;
			if(r!=30)  r=r-5;
		}
	}
}
void Timer(int ex)
{
	glutPostRedisplay();
	glutTimerFunc(30,Timer,0);
}
void myinit()
{
	//glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,1.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
void main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("circle");
	glutDisplayFunc(display);
	myinit();
	glutTimerFunc(0,Timer,0);
	glutMainLoop();
}
