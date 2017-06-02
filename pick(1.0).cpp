#include <stdlib.h>
#include <stdio.h>
#include <glut.h>
#include<string.h>
int glob;
void printme(char *string,float x,float y,float z) 
{  
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c !='!'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	glFlush();
}
void init()
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
  // gluOrtho2D (0.0,100.0,0.0, 100.0);
}

void reshape(int w,int h)
{
	glViewport(0.0,0.0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-4.0,4.0,-4.0*(GLfloat)h/(GLfloat)w,4.0*(GLfloat)w/(GLfloat)h,-0.5,0.5);
	glMatrixMode(GL_MODELVIEW);
}
void drawObjects(GLenum mode)
{
	if(mode == GL_SELECT) glLoadName(1);
	glColor3f(1.0, 0.0, 0.0);
	glRectf(10.0, 30.0, 30.0, 50.0);
	if(mode == GL_SELECT) glLoadName(2);
	glColor3f(0.0, 0.0, 1.0);
	glRectf(-1.0, -0.5, 0, 0.5);
	if(mode == GL_SELECT) glLoadName(3);
	glColor3f(0.0, 0.0, 1.0);
	glRectf(-1.0, -0.5, 0, 0.5);
	if(mode == GL_SELECT) glLoadName(4);
	glColor3f(0.0, 0.0, 1.0);
	glRectf(-1.0, -0.5, 0, 0.5);


	if(glob==1)
		{
			glColor3f(1.0,0.0,0.0);
			printme("Red square!",-1.5,-1.5,0);
		}
	else if(glob==0)
		{	
			glColor3f(0.0,0.0,1.0);
			printme("Blue square!",-1.5,-1.5,0);
		}
	else //(glob==3)
		{
			glColor3f(0.0,0.7,0.0);
			printme("Background!",-1.5,-1.5,0);
		}

	//glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawObjects(GL_RENDER);
	glColor3f(1.0,1.0,1.0);
	printme("Click on the!",20.0,80.0,0);
	glColor3f(0.0,0.0,1.0);
	printme("Red Square!",45.0,80.0,0);
	glFlush();
}

/*  processHits prints out the contents of the 
 *  selection array.
 */
void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLint ii, jj, names, *ptr;
	if(hits==0)
	{
		printf ("hits = %d\n", hits);
		glob=3;
		glutPostRedisplay();
	}
   ptr = (GLint *) buffer; 
   for (i = 0; i < hits; i++) {	/*  for each hit  */
      names = *ptr;
	  ptr+=3;
      for (j = 0; j < names; j++) { /*  for each name */
         if(*ptr==1) 
		  {		
			  printf ("red rectangle\n");
			  glob=1;
		 }
         else 
		 {
			 printf ("blue rectangle\n");
			 glob=0;
		 }
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
		gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),5.0, 5.0, viewport);
		gluOrtho2D (0.0, 100.0, 0.0, 100.0);
		drawObjects(GL_SELECT);
		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush ();
		hits = glRenderMode (GL_RENDER);
		processHits (hits, selectBuf);
		if(glob==1 || glob==0 || hits==0)
			drawObjects(GL_RENDER);
   //printme("Red square!",-1.5,-1.5,0);
		glutPostRedisplay();
   }
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
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize ( 800, 700);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("picking");
  // glutFullScreen(); 
   glutDisplayFunc(display); 
   init ();
   glutMouseFunc (mouse);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
}
