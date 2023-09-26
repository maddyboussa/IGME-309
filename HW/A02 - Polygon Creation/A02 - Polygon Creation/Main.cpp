// Course:			IGME 309
// Student Name:	Madeline Boussa
// Assignment Number: 02

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include "PolyObject.h"

using namespace std;

float canvasSize[] = { 10.0f, 10.0f };
int rasterSize[] = { 800, 600 };

// commenting out interactive triangle implementation
// structure for storing 3 2D vertices of a triangle
//int numOfVertices = 0;
//float v[2 * 3];
//float color[3];

float mousePos[2];

void init(void)
{
    // initialize vertex values as 0
    /*for (int i = 0; i < 6; i++)
        v[i] = 0.0f;*/

    mousePos[0] = mousePos[1] = 0.0f;

    // initialize color as red
    /*color[0] = 1.0f;
    color[1] = color[2] = 0.0f;*/
}

// draws cursor (point) at mouse position
void drawCursor()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex2fv(mousePos);
    glEnd();
    glPointSize(1.0f);
}

void display(void)
{
    // clear canvas
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // set drawing color to whatever current color is selected
    //glColor3fv(color);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // draw triangle based on mouse clicks
    /*if (numOfVertices > 0 && numOfVertices < 3) {

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < numOfVertices; i++)
            glVertex2fv(v + i * 2);
        glVertex2fv(mousePos);
        glEnd();
    }
    else if (numOfVertices == 3) {
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < numOfVertices; i++)
            glVertex2fv(v + i * 2);
        glEnd();
    }*/

    // draw mouse cursor
    drawCursor();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    rasterSize[0] = w;
    rasterSize[1] = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, canvasSize[0], 0.0, canvasSize[1]);
    glViewport(0, 0, rasterSize[0], rasterSize[1]);

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    // alter number of vertices depending on mouse clicks
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // reset number of vertices if it is at triangle max
        /*if (numOfVertices >= 3)
            numOfVertices = 0;*/

        // get canvas mouse position based on os position
        mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
        mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

        // set new vertex positions to mouse position
        /*v[numOfVertices * 2 + 0] = mousePos[0];
        v[numOfVertices * 2 + 1] = mousePos[1];*/

        //numOfVertices++;
        glutPostRedisplay();
    }
}

void motion(int x, int y)
{
    // mouse events are handled by OS, eventually. When using mouse in the raster window, it assumes top-left is the origin.
    // Note: the raster window created by GLUT assumes bottom-left is the origin.
    mousePos[0] = (float)x / rasterSize[0] * canvasSize[0];
    mousePos[1] = (float)(rasterSize[1] - y) / rasterSize[1] * canvasSize[1];

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}

void menu(int value)
{
    // menu states
    //switch (value) {
    //case 0: // clear
    //    numOfVertices = 0;
    //    glutPostRedisplay();
    //    break;
    //case 1: //exit
    //    exit(0);
    //case 2: // red
    //    color[0] = 1.0f;
    //    color[1] = 0.0f;
    //    color[2] = 0.0f;
    //    glutPostRedisplay();
    //    break;
    //case 3: // green
    //    color[0] = 0.0f;
    //    color[1] = 1.0f;
    //    color[2] = 0.0f;
    //    glutPostRedisplay();
    //    break;
    //case 4: // blue
    //    color[0] = 0.0f;
    //    color[1] = 0.0f;
    //    color[2] = 1.0f;
    //    glutPostRedisplay();
    //    break;
    //default:
    //    break;
    //}
}

// creates interactable menu on right click
void createMenu()
{
    int colorMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Blue", 4);

    glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 0);
    glutAddSubMenu("Colors", colorMenu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(rasterSize[0], rasterSize[1]);
    glutCreateWindow("Mouse Event - draw a triangle");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motion);
    createMenu();
    glutMainLoop();
    return 0;


}