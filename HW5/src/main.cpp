// Author: Li Peiyao
// Date: 2018

// glutEx1.cpp : 定义控制台应用程序的入口点。
//

//#include<stdio.h>
#include <stdlib.h>
#include "GL/glut.h"

float fTranslate;
float fRotate;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;
bool bWire = false;

int wHeight = 0;
int wWidth = 0;

void Draw_Leg();

//ADD
//状态控制量
int light_flag = 0;
bool spot_open = false;
bool light_open = false;

//ADD
//颜色变量设置
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat color0[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat color1[] = { 1.0f,0.0f,0.0f };
GLfloat color2[] = { 0.0f,1.0f,0.0f };
GLfloat color3[] = { 1.0f,1.0f,0.0f };
GLfloat color4[] = { 0.0f,1.0f,1.0f };
GLfloat color5[] = { 0.0f,0.0f,1.0f };
GLfloat color6[] = { 0.92f,0.89f,0.41f,1.0f };
/*
GLfloat light_x = 0.0f;
GLfloat light_y = 0.0f;
GLfloat light_z = 0.0f;

GLfloat spot_x = 0.0f;
GLfloat spot_y = 0.0f;
GLfloat spot_z = 0.0f;
*/

//点光源位置及朝向初始化
GLfloat light_pos[] = { 5.0f,5.0f ,5.0f,1.0f };
GLfloat light_dir[] = { 0.0f,-1.0f,0.0f };
//聚光灯位置及朝向初始化
GLfloat spot_pos[] = { 0.0f,5.0f ,0.0f,1.0f };
GLfloat spot_dir[] = { 0.0f,-1.0f,0.0f };
//聚光灯角度初始化
GLfloat spot_angle = 5.0f;

void Draw_Table() // This function draws a triangle with RGB colors
{
	//通过设置材料使得桌面和四条腿的颜色各不相同，
	//分别为：(1, 0, 0), (0, 1, 0), (1, 1, 0), (0, 1, 1), (0, 0, 1)
	//ADD
	//镜面反射高光颜色
	GLfloat specular[] = { 0.6f,0.6f,0.6f,1.0f };

	glPushMatrix();
	//ADD
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, 50);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color6);
	glTranslatef(0, 0, 4 + 1);
	glRotatef(90, 1, 0, 0);
	glutSolidTeapot(1);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, color1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, color2);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, color3);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, color4);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, color5);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	//TEST
	/*
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_SPECULAR, color0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color0);
	glTranslatef(light_pos[0], light_pos[1], light_pos[2]);
	glScalef(1, 1, 1);
	glutSolidCube(1.0);
	glPopMatrix();
	*/
}

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void updateView(int width, int height)
{
	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width / (GLfloat)height;
	if (bPersp) {
		gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
		//glFrustum(-3, 3, -3, 3, 3,100);
	}
	else {
		glOrtho(-3, 3, -3, 3, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }

	case ' ': {bAnim = !bAnim; break; }
	case 'o': {bWire = !bWire; break; }

	case 'a': {
		eye[0] += 0.2f;
		center[0] += 0.2f;
		break;
	}
	case 'd': {
		eye[0] -= 0.2f;
		center[0] -= 0.2f;
		break;
	}
	case 'w': {
		eye[1] -= 0.2f;
		center[1] -= 0.2f;
		break;
	}
	case 's': {
		eye[1] += 0.2f;
		center[1] += 0.2f;
		break;
	}
	case 'z': {
		eye[2] -= 0.2f;
		center[2] -= 0.2f;
		break;
	}
	case 'x': {
		eye[2] += 0.2f;
		center[2] += 0.2f;
		break;
	}
	//ADD
	//点光源打开/关闭
	case 'n': {
		light_open = !light_open;
		break;
	}
	case 'j': {//点光源向左移动
		//light_x += 0.2f;
		light_pos[0] -= 0.2f;
		break;
	}
	case 'l': {//点光源向右移动
		//light_x -= 0.2f;
		light_pos[0] += 0.2f;
		break;
	}
	case 'i': {//点光源向上移动
		//light_y += 0.2f;
		light_pos[1] += 0.2f;
		break;
	}
	case 'k': {////点光源向下移动
		//light_y -= 0.2f;
		light_pos[1] -= 0.2f;
		break;
	}
	case 'm': {////点光源向前移动
		//light_z += 0.2f;
		light_pos[2] += 0.2f;
		break;
	}
	case ',': {////点光源向后移动
		//light_z -= 0.2f;
		light_pos[2] -= 0.2f;
		break;
	}
	case 'u': {//环境光颜色切换
		light_flag = (light_flag + 1) % 4;
		//light_flag = !light_flag;
		break;
	}
    //聚光灯打开
	case 'c': {
		spot_open = !spot_open;
		break;
	}
	case 'f': {//聚光灯左移
		//spot_x -= 0.05f;
		spot_pos[0] -= 0.2f;
		break;
	}
	case 'h': {//聚光灯右移
		//spot_x += 0.05f;
		spot_pos[0] += 0.2f;
		break;
	}
	case 't': {//聚光灯上移
		//spot_y -= 0.05f;
		spot_pos[1] += 0.2f;
		break;
	}
	case 'g': {//聚光灯下移
		//spot_y += 0.05f;
		spot_pos[1] -= 0.2f;
		break;
	}
	case 'v': {//聚光灯前移
		//spot_z += 0.05f;
		spot_pos[2] += 0.2f;
		break;
	}
	case 'b': {//聚光灯后移
		//spot_z -= 0.05f;
		spot_pos[2] -= 0.2f;
		break;
	}
	case 'r': {//聚光灯角度变大
		if (spot_angle <= 89.0f)
			spot_angle += 0.2f;
		break;
	}
	case 'y': {//聚光灯角度变小
		if (spot_angle >= 1.0f)
			spot_angle -= 0.2f;
		break;
	}

	}
	updateView(wHeight, wWidth);
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

	//ADD
	//printf("%d\n", light_flag);
	//根据控制变量的值不同，改变环境光的颜色
	switch (light_flag)
	{
	case 0:
		color0[0] = color0[1] = color0[2] = color0[3] = 1.0f;
		break;
	case 1:
		color0[0] = color0[3] = 0.0f;
		color0[1] = color0[2] = 1.0f;
		break;
	case 2:
		color0[1] = color0[3] = 0.0f;
		color0[0] = color0[2] = 1.0f;
		break;
	case 3:
		color0[2] = color0[3] = 0.0f;
		color0[0] = color0[1] = 1.0f;
		break;
	}
	/*
	if (light_flag)
		color0[1] = color0[3] = 1.0f;
	else
		color0[1] = color0[3] = 0.0f;
    */

	//ADD改变颜色时只改变部分成分，不然将无法显示镜面反射的高光
	glLightfv(GL_LIGHT0, GL_AMBIENT, color0);             //设置环境光成分
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);            //设置镜面光成分
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);             //设置漫射光成分

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);         //光源方向
	
	//是否打开点光源
	if (light_open)glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);


	glLightfv(GL_LIGHT1, GL_AMBIENT, white);             //设置环境光成分
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);            //设置镜面光成分
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);             //设置漫射光成分

	glLightfv(GL_LIGHT1, GL_POSITION, spot_pos);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_angle);            //裁减角度
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);          //光源方向
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.);                  //聚集度
	//是否打开聚光灯
	if (spot_open)glEnable(GL_LIGHT1);
	else glDisable(GL_LIGHT1);

	//glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Table();						// Draw triangle

	if (bAnim) fRotate += 0.5f;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}



