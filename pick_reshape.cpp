#include <stdlib.h>
#include <iostream>
#include <glut.h>
#include <string.h>
#include <time.h>
GLfloat color[6][3]={{0.8,0.0,0.0},{0.0,0.6,0.0},{0.0,0.0,0.6},{1.0,1.0,1.0},{0.4,0.8,0.0},{0.3,0.4,0.5}};
char col_name[4][7]={"Red!","green!","blue!","white!"},out[100];

int glob,choose,sel_col,sel_sq,score=0;
time_t seconds1;
void printme( char* str,float x,float y);

void printnum(int num,float x,float y)
{
	char* buf;
	buf = (char *)malloc(52000*sizeof(char));
	sprintf( buf, "%4d", num );
	buf[strlen(buf)]='!';
	printme(buf,x,y);
}

void rand_num()
{
	int LOW=0,HIGH=3,i,j;
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	sel_col = rand() % (HIGH - LOW + 1) + LOW;
	for(i=0;i<=36000;i++)
		//for(j=0;j<=1000;j++)
	time(&seconds1);
	srand((unsigned int) seconds1);
	sel_sq = rand() % (HIGH - LOW + 1) + LOW;
}
void rect(GLfloat x,GLfloat y)
{
	glBegin(GL_POLYGON);
		glVertex2f(x,y);
		glVertex2f(x,y+25);
		glVertex2f(x+14,y+25);	
		glVertex2f(x+14,y);		
	glEnd();
	glFlush();
}
void printme(char *string,float x,float y) 
{  
	char *c;float z=0.0;
	glRasterPos3f(x, y,z);
	for (c=string; *c !='!'; c++) 
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	glFlush();
}
void eval_score()
{
	if(glob==0 && sel_sq==0)
	{
		printme("correct!",25.0,20.0);
		score++;
	}
	else if(glob==1 && sel_sq==1)
	{
		printme("correct!",25.0,20.0);
		score++;
	}
	else if(glob==2 && sel_sq==2)
	{
		printme("correct!",25.0,20.0);
		score++;
	}
	else if(glob==3 && sel_sq==3)
	{
		printme("correct!",25.0,20.0);
		score++;
	}
}
void init()
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

void drawObjects(GLenum mode)
{
	if(mode == GL_SELECT) glLoadName(5);
	glColor3f(0.0,0.0,0.0);
	glRectf(0.0,0.0,100.0,100.0);
	if(mode == GL_SELECT) glLoadName(1);
	glColor3fv(color[0]);
	rect(15.0,40.0);
	if(mode == GL_SELECT) glLoadName(2);
	glColor3fv(color[1]);
	rect(32.0,40.0);
	if(mode == GL_SELECT) glLoadName(3);
	glColor3fv(color[2]);
	rect(49.0,40.0);
	if(mode == GL_SELECT) glLoadName(4);
	glColor3fv(color[3]);
	rect(65.0,40.0);
	eval_score();
	printnum(score,20.0,30.0);
	//printnum(score,20.0,20.0);
	/*if(glob==0)
		{
			glColor3fv(color[0]);
			printme("Red square!",25.0,20.0);
		}
	else if(glob==1)
		{	
			glColor3fv(color[2]);
			printme("Blue square!",25.0,20.0);
		}
	else if(glob==2)
		{	
			glColor3fv(color[1]);
			printme("Green square!",25.0,20.0);
		}
	else if(glob==3)
		{	
			glColor3fv(color[3]);
			printme("White square!",25.0,20.0);
		}
	else if(glob==99)
		{
			glColor3fv(color[5]);
			printme("Background!",25.0,20.0);
		}*/
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawObjects(GL_RENDER);
	glColor3fv(color[3]);
	printme("Click the!",15.0,90.0);
	glColor3fv(color[sel_col]);
	printme(col_name[sel_sq],22.0,90.0);
	glFlush();
}

void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLint ii, jj, names, *ptr;
   ptr = (GLint *) buffer; 
   for (i = 0; i < hits; i++) {	/*  for each hit  */
      names = *ptr;
	  ptr+=3;
      for (j = 0; j < names; j++) { /*  for each name */
         if(*ptr==1) 
			  glob=0;
		 else if(*ptr==2) 
			 glob=1;
		 else if(*ptr==3)
			 glob=2;
		 else if(*ptr==4)
			 glob=3;
		 else if(*ptr==5)
			 glob=99;
         ptr++;
      }
      printf ("\n");
   }
}

#define SIZE 512

void mouse(int button, int state, int x, int y)
{
   GLuint selectBuf[SIZE];
   GLint hits;
   GLint viewport[4];

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
   {
		glGetIntegerv (GL_VIEWPORT, viewport);

		glSelectBuffer (SIZE, selectBuf);
		glRenderMode(GL_SELECT);

		glInitNames();
		glPushName(0);

	    glMatrixMode (GL_PROJECTION);
		glPushMatrix ();
	    glLoadIdentity ();
/*  create 5x5 pixel picking region near cursor location	*/
		gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y), 
                  5.0, 5.0, viewport);
		gluOrtho2D (0.0, 100.0, 0.0, 100.0);
		drawObjects(GL_SELECT);
		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
	    glFlush ();
		hits = glRenderMode (GL_RENDER);
		processHits (hits, selectBuf);
		if(glob==1 || glob==0 || hits==0)
			drawObjects(GL_RENDER);
		glutPostRedisplay();
   }
} 


void reshape(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0.0, 100.0, 0.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

/* Main Loop */
int main(int argc, char** argv)
{
	
   rand_num();
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (1350, 700);
   glutInitWindowPosition (0,0);
   glutCreateWindow ("picking");
   init ();
   glutReshapeFunc (reshape);
   glutDisplayFunc(display); 
   glutMouseFunc (mouse);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
}
