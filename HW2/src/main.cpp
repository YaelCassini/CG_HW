// Author: Li Peiyao
// Date: 2018

// main.cpp : 定义控制台应用程序的入口点。
#include<stdio.h>
#include "GL/glut.h"

float fTranslate=0.5f;//平移控制变量定义及初始化
float fRotate=0.0f;//旋转控制变量定义及初始化
float fScale = 1.0f; //缩放控制变量定义及初始化

void Draw_Table(float sca);
void Draw_TableLegs(float sca);
void Draw_Leg(float x, float y, float z, float l, float w, float h);
void reshape(int width, int height);
void idle();
void redraw();

//绘制桌子
void Draw_Table(float sca)
{
	//设置颜色
	glColor3f(1.0f, 1.0f, 1.0f);

	//绘制桌面
	glPushMatrix();
	    glScalef(5.0*sca, 4.0*sca, 1.0*sca);
	    glutWireCube(1.0);
	glPopMatrix();

	//绘制四个桌腿
	glPushMatrix();
	    glTranslatef(0.0, 0.0, -2.0*sca);
	    Draw_TableLegs(sca);
    glPopMatrix();

	glEnd();
}

//绘制四个桌腿
void Draw_TableLegs(float sca)
{
	for(int i=-1;i<=1;i=i+2)
		for(int j=-1;j<=1;j=j+2)
			Draw_Leg(i*1.5*sca, j*1.0*sca, 0.0, 1.0*sca, 1.0*sca, 3.0*sca);
}

//绘制一个桌腿
void Draw_Leg(float x, float y, float z, float l, float w, float h)
{
	glPushMatrix();
	   glTranslatef(x, y, z);
	   glScalef(l, w, h);
	   glutWireCube(1.0);
	glPopMatrix();
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{
    //线框模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();	// Reset The Current Modelview Matrix

	//绘制左边不断平移的桌子
	glPushMatrix();
	    glTranslatef(-3.2, 0.0f, -6.0f);
	    glTranslatef(0.0f, fTranslate, 0.0f);
	    Draw_Table(0.4);
	glPopMatrix();

	//绘制中间不断旋转的桌子
	glPushMatrix();
	    glTranslatef(0.0f, 0.0f, -6.0f);
	    glRotatef(fRotate, 0, 1.0f, 0);	
	    Draw_Table(0.4);
	glPopMatrix();

	//绘制右边不断缩放的桌子
	glPushMatrix();
	    glTranslatef(3.2f, 0.0f, -6.0f);
	    glScalef(fScale, fScale, fScale);
	    Draw_Table(0.4);
	glPopMatrix();

	//更新控制变量
	fTranslate += 0.001f;
	fRotate += 0.1f;
	fScale -= 0.0005f;

	//当平移/缩放进行到一定程度时将控制变量恢复初始值
	if (fTranslate > 0.5f) fTranslate = -0.5f;
	if (fScale < 0.1f)     fScale = 1.0f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Exercise2");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutMainLoop();

	return 0;
}


