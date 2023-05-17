// Author: Li Peiyao
// Date: 2018

// This assignment may cost you some efferts, so I give you some important HINTS, hope that may help you.
// Enjoy the coding and thinking, do pay more attention to the library functions used in OPENGL, such as how they are used? what are the parameters used? and why?

// 实验报告里面多写点感想，即对函数的理解，以及调用的顺序，步骤等。思考为什么是这样子调用的，为什么参数是这样子设置的？。。。等等你觉得值得研究的问题。
#include <stdlib.h>
#include "GL/glut.h"


float fTranslate;
float fRotate    = 0.0f;
float fScale     = 1.0f;	// set inital scale value to 1.0f
float tRotate = 0.0f;       //add and initialize an additional parameter to control the rotation of teapot

bool bPersp = false;
bool bAnim = false;
bool bWire = false;
bool tAnim = false;         //add and initialize an additional parameter to control the rotation of teapot

int wHeight = 0;
int wWidth = 0;

//add an array to express the location of the teapon
float place[] = { 0,0,5 };

//todo
//hint: some additional parameters may needed here when you operate the teapot

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene()
{
	glPushMatrix();
	//change
	//glTranslatef(0, 0, 4+1);
	//change the code to move the teapon
	glTranslatef(place[0], place[1], place[2]);
	//initialize the angle between the table and the teapon
	glRotatef(90, 1, 0, 0); //notice the rotation here, you may have a TRY removing this line to see what it looks like.
	//todo; hint: when operate the teapot, you may need to change some parameters
	//add a statement to implement the rotation of the teapon
	glRotatef(tRotate, 0, 1, 0);
	glutSolidTeapot(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

}

void updateView(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width/(GLfloat)height;

	if (bPersp){
		//add a statement to change the projection mode if necessary
		gluPerspective(45, whRatio, 1, 100);
		//todo when 'p' operation, hint: use FUNCTION gluPerspective
	}
	else
		glOrtho(-3 ,3, -3, 3,-100,100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};
//add the array place[] at the beginning of the code
//todo; hint: you may need another ARRAY when you operate the teapot


void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; }

	case ' ': {bAnim = !bAnim; break;}
	case 'o': {bWire = !bWire; break;}

	case 'a': {//todo, hint: eye[] and center[] are the keys to solve the problems
		center[0] += 0.1f;
		eye[0] += 0.1f;
		break;
			  }
	case 'd': {//todo
		center[0] -= 0.1f;
		eye[0] -= 0.1f;
		break;
			  }
	case 'w': {//todo
		center[1] -= 0.1f;
		eye[1] -= 0.1f;
		break;
			  }
	case 's': {//todo
		center[1] += 0.1f;
		eye[1] += 0.1f;
		break;
			  }
	case 'z': {//todo
		center[2] += 0.1f;
		eye[2] += 0.1f;
		break;
			  }
	case 'c': {//todo
		center[2] -= 0.1f;
		eye[2] -= 0.1f;
		break;
			  }

			  //茶壶相关操作
	case 'l': {//todo, hint:use the ARRAY that you defined, and notice the teapot can NOT be moved out the range of the table.
		//add statements
		place[0] += 0.1f;
		if (place[0] > 1.5f)place[0] = 1.5f;
		break;
			  }
	case 'j': {//todo
		//add statements
		place[0] -= 0.1f;
		if (place[0] < -1.5f)place[0] = -1.5f;
		break;
			  }
	case 'i': {//todo
		//add statements
		place[1] += 0.1f;
		if (place[1] > 1.5f)place[1] = 1.5f;
		break;
			  }
	case 'k': {//todo
		//add statements
		place[1] -= 0.1f;
		if (place[1] < -1.5f)place[1] = -1.5f;
		break;
			  }
	case 'e': {//todo
		//add statements
		tAnim = !tAnim; 
		break;
			  }
	}
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);				// 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = {5,5,5,1};

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene();						// Draw Scene

	if (bAnim) fRotate    += 0.5f;
	//add statements change the rotation parameterof the teapon
	if (tAnim)tRotate += 0.5f;
	//todo; hint: when you want to rotate the teapot, you may like to add another line here =)

	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("Ex 3");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


