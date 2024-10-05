#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <Windows.h>
#include "GL/glut.h"
#include "Point.h"
#pragma warning(disable:4996)
Pointi _start(0,0);
Pointi _end(0,0);

Pointd P0(100, 200); // 시작점
Pointd P1(350, 200);
Pointd derP0(200, 200);
Pointd derP1(200, 200);

bool mouseLeftDown = false;
bool mouseRightDown = false;
bool bre = true;
bool hermit = false;

void set_Pixel(int x, int y) {
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
void bresenham(GLint startX, GLint startY, GLint endX, GLint endY) {
	GLint _dx_Dis = startX - endX;
	GLint _dy_Dis = startY - endY;
	GLint _dx = fabs(_dx_Dis);
	GLint _dy = fabs(_dy_Dis);
	GLint _twoDx = 2 * _dx;
	GLint _twoDy = 2 * _dy;
	GLint _twoDxMinusDy = 2 * (_dx - _dy);
	GLint _twoDyMinusDx = 2 * (_dy - _dx);
	GLint p;
	GLint x, y; // 브레젠헴 알고리즘 계산을 위한 변수들을 미리 생성.

	if (_dy < _dx) {
		p = _twoDy - _dx;
		if (startX > endX) {
			x = endX;
			y = endY;
			endX = startX;
		}
		else {
			x = startX;
			y = startY;
		}
		while (x < endX) {
			x++;
			if (p < 0) {
				p += _twoDy;
			}
			else {
				y++;
				p += _twoDyMinusDx;
			}
			set_Pixel(x, y);
		}
	}
	else {
		p = _twoDx - _dy;
		if (startY > endY) {
			x = endX;
			y = endY;
			endY = startY;
		}
		else {
			x = startX;
			y = startY;
		}
		set_Pixel(x, y);
		while (y < endY) {
			y++;
			if (p < 0) {
				p += _twoDx;
			}
			else {
				x++;
				p += _twoDxMinusDy;
			}
			set_Pixel(x, y);
		}
	}


}

void Hermite(int n) {
	float _H1, _H2, _H3, _H4;

	double _deltaT = 1.0 / n;

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= n; i++) {
		double T = i * _deltaT;

		_H1 = 2.0*pow(T, 3) - 3.0*pow(T, 2) + 1.0;
		_H2 = -2.0*pow(T, 3) + 3.0*pow(T, 2);
		_H3 = pow(T, 3) - 2.0*pow(T, 2) + T;
		_H4 = pow(T, 3) - pow(T, 2);

		glVertex2f(_H1*P0.x + _H2 * P1.x + _H3 * derP0.x + _H4 * derP1.x,
			_H1*P0.y + _H2 * P1.y + _H3 * derP0.y + _H4 * derP1.y);
	}
	glEnd();
}

void init() {
	gluOrtho2D(0, 500, 500,0);//2D 좌표기준 left,right,bottom,top 화면의 좌표 기준을 만들어줌
	glClearColor(1.0, 1.0, 1.0, 0);
	glShadeModel(GL_FLAT);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (bre == true) {
		bresenham(_start.GetX(), _start.GetY(), _end.GetX(), _end.GetY());
		glEnd();
		glFlush();
		bre = false;
	}
	if (hermit == true) {
		glClear(GL_COLOR_BUFFER_BIT);
		P0.SetX(_start.GetX());
		P0.SetY(_start.GetY());
		P1.SetX(_end.GetX());
		P1.SetY(_end.GetY());
		//derP0.SetX(P0.GetX() + 30);
		//derP1.SetX(P1.GetX() + 30);
		glLineWidth(1.5);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(P0.x, P0.y);
		glVertex2f(P0.x + derP0.x / 4, P0.y + derP0.y / 4);
		glVertex2f(P1.x, P1.y);
		glVertex2f(P1.x - derP1.x / 4, P1.y - derP1.y / 4);
		glEnd();

		glColor3f(0.0, 0.0, 1.0);
		glPointSize(10.0f);

		glBegin(GL_POINTS);
		glVertex2f(P0.x, P0.y);
		glVertex2f(P0.x + derP0.x / 4, P0.y + derP0.y / 4);
		glVertex2f(P1.x, P1.y);
		glVertex2f(P1.x - derP1.x / 4, P1.y - derP1.y / 4);
		glEnd();

		Hermite(20);

		glFlush();
		glutSwapBuffers();
	}
	
}
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseLeftDown = true;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mouseLeftDown = false;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mouseRightDown = true;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		mouseRightDown = false;
	}
}
double distance(int x1, int y1, int x2, int y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
void motion(int x, int y)
{
	if (mouseLeftDown)
	{
		if (distance(P0.x + derP0.x / 4, P0.y + derP0.y / 4, x, y) < 20)
		{
			derP0.x = (x - P0.x) * 4;
			derP0.y = (y - P0.y) * 4;
		}

		if (distance(P1.x - derP1.x / 4, P1.y - derP1.y / 4, x, y) < 20)
		{
			derP1.x = (P1.x - x) * 4;
			derP1.y = (P1.y - y) * 4;
		}
	}

	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
	case 'A':
		hermit = true;

	default:
		break;
	}
	glutPostRedisplay(); // 화면갱신
}
int main(int argc,char** argv) {
	
	printf("Input 2 Point(int type):");
	scanf("%d%d%d%d", &_start.x, &_start.y, &_end.x, &_end.y);
	bre = true;
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Computer Graphics");
	init();
	glutDisplayFunc(Display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}