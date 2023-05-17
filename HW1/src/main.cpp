// Author: Li Peiyao
// Date: 2020

#include "GL/glut.h"
#include<stdio.h>
#include<math.h>
#define PI 3.1415926535

//表示向量的结构体
struct Vector
{
	GLfloat x;
	GLfloat y;
};

//表示点的结构体
struct Point
{
	GLfloat x;
	GLfloat y;
};


void display();  //绘制函数
void DrawStar(Point* P, Point* Q);  //绘制五角星函数
void DrawStar_Part(Point P, Point Q);  //绘制五角星的五分之一四边形
void Rotation(Point* P, Point* Q, float angle);  //旋转五角星的方向变量


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//绘制红色的国旗
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.9, 0.6, 0.5);
	glVertex3f(0.9, 0.6, 0.5);
	glVertex3f(0.9, -0.6, 0.5);
	glVertex3f(-0.9, -0.6, 0.5);
	glEnd();
	

	//给红旗上的五个五角星规定位置坐标和初始方向向量
	//此时的坐标是以国旗总长为30个单位，宽为20个单位的坐标系为基准的
	//其中国旗正中心坐标为（0，0）
	Point P[5] = { {-10,5},{-5,8},{-3,6},{-3,3},{-5,1} };
	Point Q[5] = { {-10,8},{-4,8},{-4,6},{-3,4},{-4,1} };

	//绘制五个五角星
	for (int i = 0; i < 5; i++)
	{
		//将原本的坐标系转化为图形窗口坐标系
		P[i].x = P[i].x / 15.0*0.9;
		Q[i].x = Q[i].x / 15.0*0.9;
		P[i].y = P[i].y / 10.0*0.6;
		Q[i].y = Q[i].y / 10.0*0.6;
		//绘制五角星
		DrawStar(&P[i],&Q[i]);
	}

	glutSwapBuffers();
}

//绘制五角星
void DrawStar(Point* P, Point* Q)
{
	
	for (int i = 0; i < 5; i++)
	{
		//绘制一部分
		DrawStar_Part(*P,*Q);
		//旋转作为基准的PQ向量
		Rotation(P,Q,2.0*PI/5.0);
	}
}

//旋转向量
void Rotation(Point* P,Point* Q,float angle)
{
	//根据几何关系计算旋转前后PQ的相对位置
	Vector PQ, PM, MQ;
	PQ.x = Q->x - P->x;
	PQ.y = Q->y - P->y;

	PM.x = PQ.x*cos(angle);
	PM.y = PQ.y*cos(angle);
	MQ.x = PQ.y*sin(angle);
	MQ.y = -PQ.x*sin(angle);
	
	//得出旋转后Q点坐标
	Q->x = P->x + PM.x + MQ.x;
	Q->y = P->y + PM.y + MQ.y;
}


//绘制五角星的五分之一（四边形）
void DrawStar_Part(Point P, Point Q)
{
	//计算四边形中关键角的角度
	float angle1 = 2.0 * PI / 10;//∠MPH
	float angle2 = 2.0 * PI / 20;//∠MQH
	//求向量之间的比例（PH/PQ）
	float scale = tan(angle2) / (tan(angle2) + tan(angle1));

	//表示点与向量的局部变量
	Point M, N;
	Vector PH, HM, PM, HN;
	Vector PQ = { Q.x - P.x,Q.y - P.y };

	//根据PQ向量，计算MN两点的位置
	PH.x = PQ.x * scale;
	PH.y = PQ.y * scale;
	HM.x = -tan(angle1) * PH.y;
	HM.y = tan(angle1) * PH.x;
	HN.x = tan(angle1) * PH.y;
	HN.y = -tan(angle1) * PH.x;

	M.x = P.x + PH.x + HM.x;
	M.y = P.y + PH.y + HM.y;
	N.x = P.x + PH.x + HN.x;
	N.y = P.y + PH.y + HN.y;

	//绘制四边形
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(P.x, P.y, 0.5);
	glVertex3f(M.x, M.y, 0.5);
	glVertex3f(Q.x, Q.y, 0.5);
	glVertex3f(N.x, N.y, 0.5);

	glEnd();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(750, 750);
	glutCreateWindow("Simple GLUT App");

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}