/*********
CTIS164 - Template Source Program
----------
STUDENT :
SECTION :
HOMEWORK:
----------
PROBLEMS: If your program does not function correctly,
explain here which parts are not running.
*********/

#include <glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD   9 // Period for the timer.
#define TIMER_ON       1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height


typedef struct {
	int Cx;
	int Cy;
}x;

x ufo[5];

int r[5];

typedef struct {
	bool fr;
}frwrd;

frwrd ahead[5] = { 1,1,1,1,1 };

bool ctimer = 0;
int val = 0;
int counter = 0, minutes = 0;
bool start = 0;
int clr;
//
// to draw circle, center at (x,y)
// radius r
//
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
	for (i = 0; i < len; i++)
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
	for (i = 0; i < len; i++)
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
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}


int max()
{

	for (int z = 1; z < 5; z++)
	{
		if (ufo[z].Cx + 80 > ufo[val].Cx + 80)
			val = z;
	}
	return(val + 1);
}

int min()
{

	for (int z = 0; z < 5; z++)
	{
		if (ahead[z].fr == 0)
			if (ufo[z].Cx < ufo[val].Cx)
				val = z;
	}
	return(val + 1);
}
void displayufo(int cx, int cy, int r)
{
	glColor3ub(244, clr, 66);
	glBegin(GL_TRIANGLES);
	glVertex2f(cx + 40, cy + 10);
	glVertex2f(cx + 20, cy - 25);
	glVertex2f(cx + 60, cy - 25);
	glEnd();

	glColor3ub(29, r, 89);
	glBegin(GL_QUADS);
	glVertex2f(cx, cy);
	glVertex2f(cx + 20, cy + 30);
	glVertex2f(cx + 60, cy + 30);
	glVertex2f(cx + 80, cy);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2f(cx + 25, cy + 50);
	glVertex2f(cx + 40, cy + 30);
	glVertex2f(cx + 55, cy + 50);
	glEnd();


	glColor3ub(96, 95, 93);
	glRectf(cx + 20, cy + 30, cx + 60, cy + 40);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(cx + 20, cy + 30);
	glVertex2f(cx + 60, cy + 30);
	glEnd();

	glColor3f(1, 1, 1);
	circle(cx + 20, cy + 15, 5);
	circle(cx + 60, cy + 15, 5);
	circle(cx + 40, cy + 15, 5);
	glColor3f(0, 0, 0);
	circle(cx + 20, cy + 15, 3);
	circle(cx + 60, cy + 15, 3);
	circle(cx + 40, cy + 15, 3);

}
void displaybackground()
{
	glColor3f(0.2, 0.2, 0.2);
	glRectf(-400, 200, 400, 300);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	for (int i = 100; i >= -200; i = i - 100)
	{
		glVertex2f(-400, i);
		glVertex2f(400, i);
	}

	glColor3f(1, 1, 1);
	glEnd();
	glColor3ub(252, 90, 144);
	glRectf(-200, 220, 200, 280);
	glColor3ub(252, 238, 89);
	vprint(-160, 245, GLUT_BITMAP_HELVETICA_18, "UFO ANIMATION BY FAHAD AHMAD");
}
//
// To display onto window using OpenGL commands
//
void display() {

	//
	// clear window to black
	//
	int m;
	glClearColor(0, 0.1, 0.2, 0.5);
	glColor3f(8, 41, 94);
	glClear(GL_COLOR_BUFFER_BIT);
	displaybackground();
	for (int m = 0; m < 5; m++)
	{
		displayufo(ufo[m].Cx, ufo[m].Cy, r[m]);
	}
	if (ahead[0].fr == 1 && ahead[1].fr == 1 && ahead[2].fr == 1 && ahead[3].fr == 1 && ahead[4].fr == 1)
		m = max();
	else
		m = min();


	glColor3ub(252, 238, 89);
	vprint(300, 270, GLUT_BITMAP_9_BY_15, "WINNER");
	vprint(-338, 270, GLUT_BITMAP_9_BY_15, "TIME");

	glColor3f(1, 1, 1);

	if (start == 1)
		vprint(320, 240, GLUT_BITMAP_9_BY_15, "0%d", m);
	vprint(-350, 240, GLUT_BITMAP_8_BY_13, "00.%02d.%02d", minutes, counter);


	glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	if (key == 32)
		ctimer = !(ctimer);

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
		for (int s = 0; s < 5; s++)
		{
			ufo[s].Cx = -400;
			ahead[s].fr = 1;
		}
		ctimer = 0;
		counter = 0;
		minutes = 0;
	}

	// to refresh the window it calls display() function
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
void onTimer(int v)
{

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.
	if (ctimer)
	{
		counter++;
		if (counter % 100 == 0)
		{
			minutes++;
			counter = 0;
			clr = rand() % 255 + 1;
		}
		for (int d = 0; d < 5; d++)
			if (ufo[d].Cx + 80 < WINDOW_WIDTH / 2 && ahead[d].fr == 1)
			{
				start = 1;
				ufo[d].Cx += rand() % 3 + 1;
			}
			else
				ahead[d].fr = 0;


		if (ufo[0].Cx > -WINDOW_WIDTH / 2 && ufo[1].Cx > -WINDOW_WIDTH / 2 && ufo[2].Cx > -WINDOW_WIDTH / 2 && ufo[3].Cx > -WINDOW_WIDTH / 2 && ufo[4].Cx > -WINDOW_WIDTH / 2)
		{

			for (int a = 0; a < 5; a++)
				if (ufo[a].Cx > -(WINDOW_WIDTH / 2) && ahead[a].fr == 0)
				{
					start = 1;
					ufo[a].Cx -= rand() % 3 + 1;
				}
		}
		else ctimer = 0;
	}

	// to refresh the window it calls display() function
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

	for (int j = 0; j < 5; j++)
	{
		ufo[j].Cx = -400;
		ufo[j].Cy = 140 - (100 * j);
		r[j] = 5 + (j * 50);
	}

	srand(time(NULL));

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

	Init();

	glutMainLoop();
}