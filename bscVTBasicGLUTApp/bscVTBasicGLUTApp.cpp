// bscVTBasicGLUTApp.cpp : Defines the entry point for the console application.
//

// linker instructions to add libraries
// see project -> properties -> Linker -> Input -> additional dependencies
// you will also need to copy glut32.dll to your source dirtectory

// compiler instructions to include instruction sets
#include "stdafx.h" // standard instructions, must come first in list
#include <windows.h> // needed by gl
#include <gl/gl.h> // instruction to compiler to include the opengl instructions
#include <gl/glu.h> // instruction to compiler to include the glu instructions
#include <gl/glut.h> // instruction to compiler to include the glut instructions
#include <iostream> // instruction to include console printing functions

#define RED 0;
#define GREEN 1;
#define BLUE 2;
// global data declarations
int g_iMainMenu=0; // index of the main menu
int g_iDisplayMenu=0; // index of the display sub menu

// camera transformations
float g_fZoom=-10.0f; // set the camera zoom position
float g_fXRot=0.0f; // set the camera x rotation
float g_fYRot=0.0f; // set the camera y rotation

// material values for teapot
float g_afMatTeapotAmbient[]={0.01f, 0.01f, 0.01f, 1.0f}; // ambient component
float g_afMatTeapotDiffuse[]={0.6f, 0.6f, 0.6f, 1.0f}; // diffuse component
float g_afMatTeapotSpecular[]={0.0f, 1.0f, 1.0f, 1.0f}; // specular component

// material values for tiangle
float g_afMatTriAmbient[]={0.01f, 0.01f, 0.01f, 1.0f}; // ambient component
float g_afMatTriDiffuse[]={0.6f, 0.2f, 0.2f, 1.0f}; // diffuse component
float g_afMatTriSpecular[]={1.0f, 1.0f, 1.0f, 1.0f}; // specular component

//mouse motion controls
bool g_bZoom=false; // flag to run zoom actions
bool g_bRot=false; // flag to run rot actions
int g_aiLastMousePos[2]; // record of mouse position at last frame

// render properties controls
int g_iRenderMode=GL_FILL;

// lit triangle orientation
float m_fTriOri=0.0f;


// triangle colours
float g_fTriBottomLeftRed = 1.0f;
float g_fTriBottomLeftGreen = 0.0f;
float g_fTriBottomRightBlue = 0.0f;
int g_iTriBottomLeftRGB = RED;

float g_fTriBottomLeftRed = 0.0f;
float g_fTriBottomLeftGreen = 1.0f;
float g_fTriBottomRightBlue = 0.0f;
int g_iTriBottomLeftRGB = GREEN;

float g_fTriTopRed = 0.0f;
float g_fTriTopGreen = 0.0f;
float g_fTriTopBlue = 1.0f;
int g_iTriBottomLeftRGB = BLUE;

void alterColour(float &fRed, float &fGreen, float &fBlue, int &iRGB) {
	switch (iRGB) {
	case RED:
		fRed -= 0.1f;
	}
}

// function definitions
// function to draw a lit teapot
void drawLitTeapot()
{
	glPushMatrix(); // isolate the object transformation
	glPushAttrib(GL_ALL_ATTRIB_BITS); // isolate the object properties
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, g_afMatTeapotAmbient); // set front and back faces ambient component to the material value
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, g_afMatTeapotDiffuse); // set front and back faces diffuse component to the material value
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, g_afMatTeapotSpecular); // set front and back faces specular component to the material value
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f); // set the front and back material shininess value

	glTranslatef(0.0f, 0.0f, 0.0f);  // position the space

	// use glut function to draw teapot
	glutSolidTeapot(0.5f); // draw a teapot

	glPopAttrib(); // end isolation of the object properties
	glPopMatrix(); // end the isolation of the object transformation
}

// function to draw a lit triangle
void drawLitTriangle()
{
	// draw the triangle
	glPushMatrix(); // isolate the object transformation
	glTranslatef(1.0f, 1.0f, 0.0f); // position the space
	glRotatef(m_fTriOri, 0.0f, 1.0f, 0.0f); // orentate the space

	glPushAttrib(GL_ALL_ATTRIB_BITS); // isolate the object properties

	// set material values
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, g_afMatTriAmbient); // set front and back faces ambient component to the material value
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, g_afMatTriDiffuse); // set front and back faces diffuse component to the material value
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, g_afMatTriSpecular); // set front and back faces specular component to the material value
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f); // set the front and back material shininess value

	// draw a triangle
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 1.0f, 0.0f);
	glEnd();

	glPopAttrib(); // end isolation of the object properties
	glPopMatrix(); // end the isolation of the object transformation
}

// function to draw a unlit triangle
void drawTriangle()
{
	// draw the triangle
	glPushMatrix(); // isolate the object transformation
	glTranslatef(-1.0f, 1.0f, 0.0f); // position the space
	glRotatef(-30.0f, 0.0f, 1.0f, 0.0f); // orentate the space

	glPushAttrib(GL_ALL_ATTRIB_BITS); // isolate the object properties

	// disable lighting
	glDisable(GL_LIGHTING);

	// draw a triangle
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 1.0f, 0.0f);
	glEnd();

	glPopAttrib(); // end isolation of the object properties
	glPopMatrix(); // end the isolation of the object transformation
}


// The actual drawing function -> gets called by glut whenever a window redraw is required
void display()
{
	// clear the OGL drawing buffers, both the color buffer and the depth buffer 
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	// transform the scene to the right position to be viewed by the camera
	glLoadIdentity(); // clear matrix
	glTranslatef(0.0f, 0.0f, g_fZoom); // apply the zoom translation
	glRotatef(g_fYRot, 0.0f, 1.0f, 0.0f);	

	// apply reder mode
	glPolygonMode(GL_FRONT_AND_BACK, g_iRenderMode);
	
	glRotatef(m_fTriOri, 1.0f, 1.0f, -0.5f); // orentate the space
	// draw the teapot
	drawLitTeapot();

	// draw the lit triangle
	drawLitTriangle();

	// draw the unlit triangle
	drawTriangle();

	// flush the gl drawing commands
	glFlush(); 

	// swap the buffers to display the drawn image -> note this is not a gl function
	glutSwapBuffers();
}

// simulation loop function -> gets continually called when nothing else is running
void idle()
{
	// rotate the lit triangle
	m_fTriOri+=2.0f;

	// redraw scene
	glutPostRedisplay();
}

// window reshape function -> gets called by glut when the window is resized.
// Use this to redefine the viewing transformation
void reshape(int iWidth, int iHeight)
{
	glViewport(0, 0, iWidth, iHeight); // resize the viewing window

	// redefine the viewing transformation
	glMatrixMode(GL_PROJECTION); // switch to projection matrix
	glLoadIdentity(); // clear matrix
	gluPerspective(30.0f, ((float)iWidth)/((float)iHeight), 0.1f, 100.0f); // set the display parameters -> view angle, aspect ratio, near clip, far clip
	glMatrixMode(GL_MODELVIEW); // switch back to drawing matrix
	glutPostRedisplay(); // ask glut to redraw scene
}

// basic keys function -> called by glut whenever a standard key is pressed
void keyboard(unsigned char c, int iXPos, int iYPos)
{
	switch(c) // process key presses
	{
		case 'z': // zoom in
			g_fZoom+=0.1f; // change zoom dist

			if(g_fZoom > -0.4f) g_fZoom=-0.4f; // check have not zoomed too far

			glutPostRedisplay(); // redraw scene
			break;
		case 'Z': // zoom out

			g_fZoom-=0.1f; // change zoom dist

			if(g_fZoom <-70.0f) g_fZoom=-70.0f; // check have not zoomed too far

			glutPostRedisplay(); // redraw scene

			break;
		case 'a': // rotate left
		case 'A':
			g_fYRot-=1.0f;
			glutPostRedisplay(); // redraw scene
			break;
		case 'd': // rotate right
		case 'D':
			g_fYRot+=1.0f;
			glutPostRedisplay(); // redraw scene
			break;
	}
}

// basic keys function -> called by glut whenever a non-standard key is pressed
void sKeyboard(int iC, int iXPos, int iYPos)
{
	switch(iC) // process key presses
	{
	case GLUT_KEY_UP: // zoom in
		g_fZoom+=0.1f; // change zoom dist

		if(g_fZoom > -0.4f) g_fZoom=-0.4f; // check have not zoomed too far

		glutPostRedisplay(); // redraw scene
		break;
	case GLUT_KEY_DOWN: // zoom out

		g_fZoom-=0.1f; // change zoom dist

		if(g_fZoom <-70.0f) g_fZoom=-70.0f; // check have not zoomed too far

		glutPostRedisplay(); // redraw scene

		break;
	case GLUT_KEY_LEFT: // rotate left
		g_fYRot-=1.0f;
		glutPostRedisplay(); // redraw scene
		break;
	case GLUT_KEY_RIGHT: // rotate right
		g_fYRot+=1.0f;
		glutPostRedisplay(); // redraw scene
		break;
	}
}

// mouse event function -> called by glut whenever a mouse key is pressed
void mouse(int iKey, int iEvent, int iXPos, int iYPos)
{
	if(iKey==GLUT_LEFT && iEvent==GLUT_DOWN) // if a left key event and this is a key press
	{
		if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) // test to see if shift key is active (note this is a bitwise operation (&))
		{
			if(iEvent==GLUT_DOWN) g_bRot=true; // start mouse rotation
		}
		else
		{
			g_bZoom=true; // start mouse zoom;
		}
	
		// record mouse position
		g_aiLastMousePos[0]=iXPos; 
		g_aiLastMousePos[1]=iYPos; 
	}
	else if(iKey==GLUT_LEFT && iEvent==GLUT_UP) // if a left key event and this is a key release
	{
		g_bRot=false; // end rot
		g_bZoom=false; // end zoom
	}
}

// mouse event function -> called by glut whenever the mouse is moved
void motion(int iXPos, int iYPos)
{
	if(g_bZoom) // if mouse is controlling zoom 
	{
		// base zoom on changes in the y position of the mouse		

		g_fZoom+=(((float)iYPos)-((float)g_aiLastMousePos[1])); // modify zoom

		glutPostRedisplay(); // redraw scene
	}

	if(g_bRot) // if mouse is controlling rot 
	{
		// base rot on changes in the x position of the mouse		

		g_fYRot-=(((float)iXPos)-((float)g_aiLastMousePos[0])); // modify zoom

		glutPostRedisplay(); // redraw scene
	}

	// update last mouse position
	g_aiLastMousePos[0]=iXPos; 
	g_aiLastMousePos[1]=iYPos; 
}

// main menu function -> called by glut whenever the main menu is used
void menuMain(int i)
{
	if(i==1) exit(0);
}

// display menu function -> called by glut whenever the display menu is used
void menuDisplay(int i)
{
	g_iRenderMode = i;

	glutPostRedisplay();
}

void myInit()
{
	// set the clear color
	glClearColor(0.7f, 0.7f, 0.8f, 1.0f);

	// setup lighting
	glEnable(GL_DEPTH_TEST); // enable depth test -> needed for lighting
	glEnable(GL_LIGHT0); // enable a light: light0 has a set of default values
	glEnable(GL_LIGHTING); // enable lighting
}

// this is the main function -> where processing starts
int _tmain(int argc, _TCHAR* argv[])
{
	// initialize glut
	glutInit(&argc, (char**)argv); 

	// create a glut window
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(512,512);
	glutCreateWindow("bscVTBasicGlut");

	// register callback functions -> these are examples of pointers to functions
	glutDisplayFunc(display); // display function
	glutIdleFunc(idle); // simulation loop
	glutReshapeFunc(reshape); // reshape function 
	glutKeyboardFunc(keyboard); // basic keyboard entry
	glutSpecialFunc(sKeyboard); // extended keyboard function
	glutMouseFunc(mouse); // mouse events
	glutMotionFunc(motion); // mouse motion

	// create a glut sub main menu
	g_iDisplayMenu= glutCreateMenu(menuDisplay); // create a menu and associate a handler function

	// add items to the menu -> <<name>>, value
	glutAddMenuEntry("Show fill", GL_FILL);
	glutAddMenuEntry("Show lines", GL_LINE);
	glutAddMenuEntry("Show points", GL_POINT);

	// create main menu
	g_iMainMenu= glutCreateMenu(menuMain); // create a menu and associate a handler function

	// add sub menu to main menu 
	glutAddSubMenu("Display", g_iDisplayMenu);

	// add quit action to main window
	glutAddMenuEntry("Quit",1);

	// attach menus to a mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// perform initialisation of opengl rendering
	myInit(); // function I have defined

	// hand control over to glut
	glutMainLoop();

	return 0;
}
