#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
 
#define WIDTH 640
#define HEIGHT 480

char playback = 'p';
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
}
DrawJumpingBall(double x,double y,double r)
{
	glColor3f(0.0,0.0,0.0);
	DrawArc(0.0-(x),90.0-x,x,y-(x*x*0.01),r);
	glColor3f(0.0,0.0,1.0);
	DrawArc(90.0-(x),180.0-(x),x,y-(x*x*0.01),r);
	glColor3f(1.0,1.0,0.0);
	DrawArc(180.0-(x),270.0-(x),x,y-(x*x*0.01),r);
	glColor3f(0.0,1.0,0.0);
	DrawArc(270.0-(x),360.0-(x),x,y-(x*x*0.01),r);
}
DrawBall(double x,double y,double r)
{
	glColor3f(0.0,0.0,0.0);
	DrawArc(0.0-(x),90.0-x,x,y,r);
	glColor3f(0.0,0.0,1.0);
	DrawArc(90.0-(x),180.0-(x),x,y,r);
	glColor3f(1.0,1.0,0.0);
	DrawArc(180.0-(x),270.0-(x),x,y,r);
	glColor3f(0.0,1.0,0.0);
	DrawArc(270.0-(x),360.0-(x),x,y,r);
}
 
void reshape(int width, int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH/2,WIDTH/2-1,-HEIGHT/2,HEIGHT/2-1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
 
void init(void)
{
	glClearColor(0.58,0.435,0.2,1.0);
	glPointSize(2.0);
}
 
void Timer(int ex)
{
	glutPostRedisplay();
	glutTimerFunc(30,Timer,0);
}
 
double k=20;
double r=100,flag=0;
void tennisBall(void)
{
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(0.5,0.5,1.0,1.0);
	glBegin(GL_POLYGON); 
	if (playback == 'p') 
	{
		DrawJumpingBall(k,200,r);
		if(flag==0)
		{
			if((k+r)<=240)
			{
				k=k+10;
		 	}
		 
			if((k+r)>=240)
			{
				flag=1;
		 	}
		}
		 
		if(flag==1)
		{
			k=k-10;
		 	if((k-r)<=-240)
			{
				flag=0;
			}
		}
	}
	 
	glEnd();
	glutSwapBuffers();
}
void display(void)
{
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(0.5,0.5,1.0,1.0);
	glBegin(GL_POLYGON); 
	if (playback == 'p') 
	{
		DrawBall(k,30,r);
		if(flag==0)
		{
			if((k+r)<=240)
			{
				k=k+10;
		 	}
		 
			if((k+r)>=240)
			{
				flag=1;
		 	}
		}
		 
		if(flag==1)
		{
			k=k-10;
		 	if((k-r)<=-240)
			{
				flag=0;
				if(r!=30)  r=r-5;
			}
		}
	}
	 
	glEnd();
	glutSwapBuffers();
}
void about()
{
	glLoadIdentity();
}
 void menu( int x)
{
	switch (x)
	{
		
		case 3:exit(0);break;
		case 2:glutDisplayFunc(about);break;
		case 1:glutDisplayFunc(tennisBall);	break;
	}
	return;
}
void stopball()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	DrawBall(00,00,50);	
	glutSwapBuffers();
}
void mykey(unsigned char key,int x,int y)
{ 
	if(key=='s'||key=='S')
	{
		glutDisplayFunc(stopball);
	}
	if (key=='p'||key=='P')
	{
		glutDisplayFunc(display);
	}
}
int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("Sidharth CG project");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutCreateMenu(menu);
	    glutAddMenuEntry("tennis ball",1);
		glutAddMenuEntry("Pause",2);
		glutAddMenuEntry("Exit",3);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(mykey);
	init();
	glutTimerFunc(0,Timer,0);
	glutMainLoop();
	return(1);
}

