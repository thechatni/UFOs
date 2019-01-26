/***
CTIS164 - Template Source Program
----------
STUDENT :
SECTION :
HOMEWORK:
----------
PROBLEMS: If your program does not function correctly,
explain here which parts are not running.
***/

#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD  10 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532
//int cx = -470;
//int cy = 125;
/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

						  //
						  // to draw circle, center at (x,y)
						  // radius r
						  //

bool forward[5] = { true,true,true,true,true };
bool timer = false;
int timePeriod = 0, min = 0;
int cx1 = -470, cx2 = -470, cx3 = -470, cx4 = -470, cx5 = -470;

int r1, r2, r3, r4, r5;
int winner = 0;
int winindex;

int win()
{

	if (cx1+123 > cx2+123 &&cx1+123 > cx3+123 &&cx1+123 > cx4+123 &&cx1+123 > cx5+123)
	{
		winner = 1;
		winindex = cx1;
	}
	else if (cx2+123 > cx3+123 &&cx2+123 > cx4+123 &&cx2+123 > cx5+123)
	{
		winner = 2;
		winindex = cx2;
	}
	else if (cx3+123 > cx4+123 &&cx3+123 > cx5+123)
	{
		winner = 3;
		winindex = cx3;
	}
	else if (cx4+123 > cx5+123)
	{
		winner = 4;
		winindex = cx4;
	}
	else
	{
		winner = 5;
		winindex = cx5;
	}
	return(winner);

}
int behind()
{
	if (cx1< winindex && forward[0]==false)
	{
		winner = 1;
		winindex = cx1;
	}
	if (cx2  < winindex  && forward[1] == false)
	{
		winner = 2;
		winindex = cx2;
	}
	if (cx3  < winindex  && forward[2] == false)
	{
		winner = 3;
		winindex = cx3;
	}
	if (cx4  < winindex  && forward[3] == false)
	{
		winner = 4;
		winindex = cx4;
	}
	if (cx5  < winindex  && forward[4] == false)
	{
		winner = 5;
		winindex = cx5;
	}
	return(winner);
}

void displayBack()
{
	glColor3ub(345, 173, 75);
	glRectf(-500, 200, 500, 300);

	glColor3ub(3, 30, 168);
	glBegin(GL_LINES);

	for (int i = 100; i >= -200; i = i - 100)
	{
		glVertex2f(-500, i);
		glVertex2f(500, i);

	}
	glEnd();




	//glVertex2f(350, -300);
	//glVertex2f(200, -300);
}
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r*cos(angle), y + r*sin(angle));
	}
	glEnd();
}

void print(int x, int y, char *string, void *font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i<len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

//
// To display onto window using OpenGL commands
//
void reverseBike(int cx, int cy, int num, int x)
{

	glColor3ub(169, 0, 0);
	//wheels

	circle_wire(cx, cy, 20);
	circle_wire(cx, cy, 21);

	circle_wire(cx - 100, cy, 20);
	circle_wire(cx - 100, cy, 21);

	//frame of the bike
	glColor3ub(57, 158, x);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);

	glVertex2f(cx, cy);  //quad
	glVertex2f(cx - 30, cy + 30);
	glVertex2f(cx - 80, cy + 30);


	glVertex2f(cx - 40, cy);

	glEnd();






	/*pedals
	glColor3ub(3, 8, 168);
	glLineWidth(4);
	glBegin(GL_LINES);

	glVertex2f(cx + 40, cy);
	glVertex2f(cx + 45, cy+10);

	glEnd();
	*/

	glColor3ub(3, 8, 168);

	glBegin(GL_LINES);

	glVertex2f(cx - 80, cy + 30);
	glVertex2f(cx - 100, cy);

	glEnd();
	glLineWidth(5);
	glBegin(GL_LINES);

	glColor3ub(3, 8, 168);

	glVertex2f(cx - 30, cy + 30);
	glVertex2f(cx - 30, cy + 43);

	glEnd();
	glLineWidth(5);
	glColor3ub(168, 3, 36);
	glBegin(GL_LINES);

	glVertex2f(cx - 80, cy + 30);
	glVertex2f(cx - 80, cy + 50);
	glVertex2f(cx - 80, cy + 50);
	glVertex2f(cx - 65, cy + 55);
	glVertex2f(cx - 80, cy + 50);
	glVertex2f(cx - 65, cy + 45);




	glEnd();

	glLineWidth(6);
	glColor3ub(168, 3, 36);
	glBegin(GL_LINE_LOOP);

	glVertex2f(cx - 30, cy + 43);
	glVertex2f(cx - 23, cy + 43);
	glVertex2f(cx - 37, cy + 43);

	glEnd();

	//backWheel
	glLineWidth(3);
	glColor3ub(168, 3, 36);
	glBegin(GL_LINES);

	glVertex2f(cx, cy);
	glVertex2f(cx + 15, cy - 18);
	glVertex2f(cx, cy);
	glVertex2f(cx, cy - 20);
	glVertex2f(cx, cy);
	glVertex2f(cx + 18, cy);
	glVertex2f(cx, cy);
	glVertex2f(cx, cy + 20);
	glVertex2f(cx, cy);
	glVertex2f(cx - 15, cy - 18);

	glEnd();
	//frontWheel
	glLineWidth(3);
	glColor3ub(168, 3, 36);
	glBegin(GL_LINES);

	glVertex2f(cx - 100, cy);
	glVertex2f(cx - 100 - 15, cy - 18);
	glVertex2f(cx - 100, cy);
	glVertex2f(cx - 100, cy - 20);
	glVertex2f(cx - 100, cy);
	glVertex2f(cx - 100 - 18, cy);
	glVertex2f(cx - 100, cy);
	glVertex2f(cx - 100, cy + 20);
	glVertex2f(cx - 100, cy);
	glVertex2f(cx - 115, cy - 18);
	glVertex2f(cx - 100, cy);
	glVertex2f(cx - 123, cy);
	glEnd();

	//flag
	glColor3ub(42, 52, 50);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex2f(cx, cy);
	glVertex2f(cx, cy + 38);
	glEnd();
	glColor3ub(42, 52, 50);

	glBegin(GL_TRIANGLES);
	glVertex2f(cx - 3, cy + 36);
	glVertex2f(cx - 3, cy + 65);
	glVertex2f(cx + 30, cy + 53);
	glEnd();

	glColor3ub(164, 244, 78);
	vprint(cx - 3, cy + 47, GLUT_BITMAP_9_BY_15, "0%d", num);


}


void myBike(int cx, int cy, int num, int b)
{
	glColor3ub(169, 0, 0);
	//wheels

	circle_wire(cx, cy, 20);
	circle_wire(cx, cy, 21);

	circle_wire(cx + 100, cy, 20);
	circle_wire(cx + 100, cy, 21);

	//frame of the bike
	glColor3ub(57, 158, b);
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);

	glVertex2f(cx, cy);  //quad
	glVertex2f(cx + 30, cy + 30);
	glVertex2f(cx + 80, cy + 30);


	glVertex2f(cx + 40, cy);

	glEnd();






	/*pedals
	glColor3ub(3, 8, 168);
	glLineWidth(4);
	glBegin(GL_LINES);

	glVertex2f(cx + 40, cy);
	glVertex2f(cx + 45, cy+10);

	glEnd();
	*/

	glColor3ub(3, 8, 168);

	glBegin(GL_LINES);

	glVertex2f(cx + 80, cy + 30);
	glVertex2f(cx + 100, cy);

	glEnd();
	glLineWidth(5);
	glBegin(GL_LINES);

	glColor3ub(3, 8, 168);

	glVertex2f(cx + 30, cy + 30);
	glVertex2f(cx + 30, cy + 43);

	glEnd();
	glLineWidth(5);
	glColor3ub(168, 3, 36);
	glBegin(GL_LINES);

	glVertex2f(cx + 80, cy + 30);
	glVertex2f(cx + 80, cy + 50);
	glVertex2f(cx + 80, cy + 50);
	glVertex2f(cx + 65, cy + 55);
	glVertex2f(cx + 80, cy + 50);
	glVertex2f(cx + 65, cy + 45);




	glEnd();

	glLineWidth(6);
	glColor3ub(168, 3, 36);
	glBegin(GL_LINE_LOOP);

	glVertex2f(cx + 30, cy + 43);
	glVertex2f(cx + 23, cy + 43);
	glVertex2f(cx + 37, cy + 43);

	glEnd();

	//backWheel
	glLineWidth(3);
	glColor3ub(168, 3, 36);
	glBegin(GL_LINES);

	glVertex2f(cx, cy);
	glVertex2f(cx - 15, cy - 18);
	glVertex2f(cx, cy);
	glVertex2f(cx, cy - 20);
	glVertex2f(cx, cy);
	glVertex2f(cx - 18, cy);
	glVertex2f(cx, cy);
	glVertex2f(cx, cy + 20);
	glVertex2f(cx, cy);
	glVertex2f(cx + 15, cy - 18);

	glEnd();
	//frontWheel
	glLineWidth(3);
	glColor3ub(168, 3, 36);
	glBegin(GL_LINES);

	glVertex2f(cx + 100, cy);
	glVertex2f(cx + 100 - 15, cy - 18);
	glVertex2f(cx + 100, cy);
	glVertex2f(cx + 100, cy - 20);
	glVertex2f(cx + 100, cy);
	glVertex2f(cx + 100 - 18, cy);
	glVertex2f(cx + 100, cy);
	glVertex2f(cx + 100, cy + 20);
	glVertex2f(cx + 100, cy);
	glVertex2f(cx + 115, cy - 18);
	glVertex2f(cx + 100, cy);
	glVertex2f(cx + 123, cy);
	glEnd();

	//flag
	glColor3ub(42, 52, 50);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex2f(cx, cy);
	glVertex2f(cx, cy + 38);
	glEnd();
	glColor3ub(42, 52, 50);

	glBegin(GL_TRIANGLES);
	glVertex2f(cx + 3, cy + 36);
	glVertex2f(cx + 3, cy + 65);
	glVertex2f(cx - 30, cy + 53);
	glEnd();

	glColor3ub(164, 244, 78);
	vprint(cx - 15, cy + 47, GLUT_BITMAP_9_BY_15, "0%d", num);


}


void display() {

	//
	// clear window to black
	//

	int l;
	int cy = 125;
	int cy1 = 25;
	int cy2 = -75;
	int cy3 = -175;
	int cy4 = -275;




	glClearColor(0.6, 0.4, 0, 0.8);
	glClear(GL_COLOR_BUFFER_BIT);


	displayBack();
	if (forward[0] == true)
		myBike(cx1, cy, 1, 50);
	else if (forward[0] == false)
		reverseBike(cx1, cy, 1, 50);
	if (forward[1] == true)
		myBike(cx2, cy1, 2, 100);
	else if (forward[1] == false)
		reverseBike(cx2, cy1, 2, 100);
	if (forward[2] == true)
		myBike(cx3, cy2, 3, 140);
	else if (forward[2] == false)
		reverseBike(cx3, cy2, 3, 140);
	if (forward[3] == true)
		myBike(cx4, cy3, 4, 0);
	else if (forward[3] == false)
		reverseBike(cx4, cy3, 4, 0);
	if (forward[4] == true)
		myBike(cx5, cy4, 5, 255);
	else if (forward[4] == false)
		reverseBike(cx5, cy4, 5, 255);


	if (forward[0] == true && forward[1] == true && forward[2] == true && forward[3] == true && forward[4] == true)
		l = win();
	else
		l = behind();

	vprint(-50, 250, GLUT_BITMAP_8_BY_13, "Winner = %d", l);

	glutSwapBuffers();



}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 32)
	{
		timer = !timer;
	}
	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		cx1 = -470, cx2 = -470, cx3 = -470, cx4 = -470, cx5 = -470;
		for (int i = 0; i < 5; i++)
		{
			forward[i] = true;
		}
		timer = false;
	}
	// to refresh the window it calls display() 
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.

	if (timer == true)
	{
		timePeriod++;
		if (timePeriod == 100)
		{
			min++;
			timePeriod = 0;
		}

		r1 = rand() % 10 + 2;
		r2 = rand() % 10 + 2;
		r3 = rand() % 10 + 2;
		r4 = rand() % 10 + 2;
		r5 = rand() % 10 + 2;

		if (cx1 < (WINDOW_WIDTH / 2) - 123 && forward[0] == true)
		{
			cx1 += r1;
		}

		if (cx2 < (WINDOW_WIDTH / 2) - 123 && forward[1] == true)
		{
			cx2 += r2;
		}

		if (cx3 < (WINDOW_WIDTH / 2) - 123 && forward[2] == true)
		{
			cx3 += r3;
		}

		if (cx4 < (WINDOW_WIDTH / 2) - 123 && forward[3] == true)
		{
			cx4 += r4;
		}

		if (cx5 < (WINDOW_WIDTH / 2) - 123 && forward[4] == true)
		{
			cx5 += r5;
		}


		if (cx1 >= (WINDOW_WIDTH / 2) - 123)
		{
			forward[0] = false;
		}
		if (cx2 >= (WINDOW_WIDTH / 2) - 123)
		{
			forward[1] = false;
		}
		if (cx3 >= (WINDOW_WIDTH / 2) - 123)
		{
			forward[2] = false;
		}
		if (cx4 >= (WINDOW_WIDTH / 2) - 123)
		{
			forward[3] = false;
		}
		if (cx5 >= (WINDOW_WIDTH / 2) - 123)
		{
			forward[4] = false;
		}

		/*	while (cx1 > -((WINDOW_WIDTH / 2) - 123) && cx2 > -((WINDOW_WIDTH / 2) - 123) && cx3 > -((WINDOW_WIDTH / 2) - 123) && cx4 > -((WINDOW_WIDTH / 2) - 123) && cx5 > -((WINDOW_WIDTH / 2) - 123))
		{


		while (forward[0] == false && forward[1] == false && forward[2] == false && forward[3] == false && forward[4] == false)
		{
		timer = true;
		cx1 -= rand() % 5 + 6;
		cx2 -= rand() % 5 + 6;
		cx3 -= rand() % 5 + 6;
		cx4 -= rand() % 5 + 6;
		cx5 -= rand() % 5 + 6;
		}
		*/
		if (cx1 >= -((WINDOW_WIDTH / 2) - 125) && cx2 >= -((WINDOW_WIDTH / 2) - 125) && cx3 >= -((WINDOW_WIDTH / 2) - 125) && cx4 >= -((WINDOW_WIDTH / 2) - 125) && cx5 >= -((WINDOW_WIDTH / 2) - 125))
		{

			if (forward[0] == false) //&& cx1 > -((WINDOW_WIDTH / 2) - 123))
			{
				cx1 -= rand() % 5 + 6;
			}
			if (forward[1] == false)//&& cx2 > -((WINDOW_WIDTH / 2) - 123))
			{
				cx2 -= rand() % 5 + 6;
			}
			if (forward[2] == false)//&& cx3 > -((WINDOW_WIDTH / 2) - 123))
			{
				cx3 -= rand() % 5 + 6;
			}
			if (forward[3] == false)//&& cx4 > -((WINDOW_WIDTH / 2) - 123))
			{
				cx4 -= rand() % 5 + 6;
			}
			if (forward[4] == false)//&& cx5 > -((WINDOW_WIDTH / 2) - 123))
			{
				cx5 -= rand() % 5 + 6;
			}
		}
		if (cx1 == -400 || cx2 == -400 || cx3 == -400 || cx4 == -400 || cx5 == -400)
		{
			for (int i = 0; i < 5; i++)
				if (forward[i] == false)
					timer = !timer;
		}
		/*	if (cx1 > -((WINDOW_WIDTH / 2) - 123) && cx2 > -((WINDOW_WIDTH / 2) - 123) && cx3 > -((WINDOW_WIDTH / 2) - 123) && cx4 > -((WINDOW_WIDTH / 2) - 123) && cx5 > -((WINDOW_WIDTH / 2) - 123))
		{
		if (forward[0] == false && cx1 > -((WINDOW_WIDTH / 2) - 123))
		{
		cx1 -= rand() % 5 + 6;
		}
		if (forward[1] == false && cx2 > -((WINDOW_WIDTH / 2) - 123))
		{
		cx2 -= rand() % 5 + 6;
		}if (forward[2] == false && cx3 > -((WINDOW_WIDTH / 2) - 123))
		{
		cx3 -= rand() % 5 + 6;
		}if (forward[3] == false && cx4 > -((WINDOW_WIDTH / 2) - 123))
		{
		cx4 -= rand() % 5 + 6;
		}if (forward[4] == false && cx5 > -((WINDOW_WIDTH / 2) - 123))
		{
		cx5 -= rand() % 5 + 6;
		}

		}
		else {
		timer = !timer;
		}*/
		// to refresh the window it calls display() function
	}
	glutPostRedisplay(); // display()



}


#endif

void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Template File");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	srand(time(NULL));
	Init();

	glutMainLoop();
}