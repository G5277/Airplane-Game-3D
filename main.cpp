#include <windows.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <cmath>
#include <algorithm>

#include "rendering.h"
#include "environment.h"
#include "globals.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

static void key(unsigned char key, int x, int y)
{
    float frac = 0.3;
    float rotFrac = 1;
    switch (key)
    {
    case 27:
    case 'g':
        START = true;
        break;
    case 'm':
        START = false;
        break;
    default:
        START = false;
    }

    glutPostRedisplay();
}

void read_file()
{
    std::cout << "enter";
    if (START == false)
    {
        glutKeyboardFunc(key);
    }

    std::ifstream file("D:/key_events.txt");
    if (!file) {
        std::cerr << "Failed to open the file.\n";
        return;
    }
    char ch;
    file.get(ch); // Read a single character

    if (file) {
        std::cout << "Character read: " << ch << "\n";
    }
    else {
        ch = 'c';
    }

    file.close();

    float frac = 0.3;
    float rotFrac = 1;
    switch (ch)
    {
    case 27:
    case 'q':
        exit(0);
        break;
    case 'w':
        tY -= frac;
        rotZ += rotFrac;
        break;
    case 's':
        tY += frac;
        rotZ -= rotFrac;
        break;
    case 'a':
        tX += frac;
        rotX -= rotFrac * 3;
        rotY += rotFrac / 2;
        break;
    case 'd':
        tX -= frac;
        rotX += rotFrac * 3;
        rotY -= rotFrac / 2;
        break;
    case 'g':
        START = true;
        break;
    case 'm':
        START = false;
        break;
    }
    glutPostRedisplay();
}

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool checkThroughRing(float planeX, float planeY, float torusX, float torusY, float tZ_val) {

    float horizontalDist = sqrt(pow(planeX - torusX, 2) + pow(planeY - torusY, 2));
    float ringInnerRadius = 0.9;
    float zThreshold = 0.5;
    bool withinInnerOpening = horizontalDist < ringInnerRadius;
    bool passingThroughZ = fabs(tZ_val) < zThreshold;
    bool movingTowardScreen = tZ_val > -0.2 && tZ_val < 0.2;
    return withinInnerOpening && passingThroughZ && movingTowardScreen;
}

void handleEnvironment(int index, float zTranslation, float& zValue) {
    float planeX = 0;
    float planeY = 1;

    if (torusActive[index] && checkThroughRing(planeX - tX, planeY - tY, torusPosX[index], torusPosY[index], zTranslation)) {
        score += 10;
        torusActive[index] = false;
    }

    glPushMatrix();
    glTranslated(tX, tY, zTranslation);
    environment(index);
    glPopMatrix();

    zValue += speed;
    if (zValue >= 20) {
        zValue = -110;
        torusActive[index] = true;
    }
}

void draw() {
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    TIME = t;

    rotX = (rotX < -11.0f) ? -11.0f : (rotX > 11.0f) ? 11.0f : rotX;
    rotZ = (rotZ < -15.0f) ? -15.0f : (rotZ > 10.0f) ? 10.0f : rotZ;

    // Draw the plane
    glPushMatrix();
    glTranslated(0, 1, 0);
    glRotated(90, 0, 1, 0);
    glRotated(5, 0, 0, 1);
    glRotated(rotX, 1, 0, 0);
    glRotated(rotY, 0, 1, 0);
    glRotated(rotZ, 0, 0, 1);
    glScaled(0.4, 0.4, 0.4);
    plane();
    glPopMatrix();

    if (tX >= 4.1)tX = 4.1;
    if (tX <= -4.1)tX = -4.1;
    if (tY > 0.1)tY = 0.1;
    if (tY < -15)tY = -15;

    // Handle each environment with corresponding torus
    handleEnvironment(2, tZ, tZ);
    handleEnvironment(3, tZ2, tZ2);
    handleEnvironment(1, tZ3, tZ3);
    handleEnvironment(5, tZ4, tZ4);
    handleEnvironment(4, tZ5, tZ5);
    handleEnvironment(2, tZ6, tZ6);
}

void drawBitmapText(char* str, float x, float y, float z)
{
    char* c;
    glRasterPos3f(x, y + 8, z);

    for (c = str; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
    }
}

void drawStrokeText(const char* str, int x, int y, int z)
{
    const char* c;
    glPushMatrix();
    glTranslatef(x, y + 8, z);
    glScalef(0.002f, 0.002f, z);

    glColor3f(0.0f, 0.0f, 0.0f); // Set text color to black

    for (c = str; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawStrokeText2(const char* str, int x, int y, int z)
{

    const char* c;
    glPushMatrix();
    glTranslatef(x, y + 8, z);
    glScalef(0.005f, 0.005f, z);
    glColor3f(0.0f, 0.0f, 0.0f);

    for (c = str; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawStrokeChar(char c, float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y + 8, z);
    glScalef(0.002f, 0.002f, z);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    glPopMatrix();
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t * 90.0;
    double aa = a;
    if (!isrotate) {
        a = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 4.5, 10.0,
        0, 4, 0,
        0, 1.0f, 0.0f);

    if (START) {
        glPushMatrix();
        glTranslated(0, 0, 0);
        glScaled(zoom, zoom, zoom);
        glRotated(a, 0, 1, 0);
        draw();
        glPopMatrix();

        // Controls at the top
        drawStrokeText("MAIN MENU: M", -8, 0, 0);

        // Score on the left bottom
        drawStrokeText("SCORE: ", -8, -1, 0);
        int tempScore = score;
        float digitPos = -6.5;

        // Handle the case when score is 0
        if (tempScore == 0) {
            drawStrokeChar('0', digitPos, -1, 0);
        }
        else {
            int digits[10]; // Store individual digits
            int digitCount = 0;

            // Extract digits from score (in reverse order)
            while (tempScore > 0) {
                digits[digitCount++] = tempScore % 10;
                tempScore /= 10;
            }

            // Display digits in correct order
            for (int i = digitCount - 1; i >= 0; i--) {
                drawStrokeChar(digits[i] + '0', digitPos, -1, 0);
                digitPos += 0.2;
            }
        }

        // Time on the right bottom
        drawStrokeText("TIME: ", 3, -1, 0);
        int mod, number = 0;
        int tmpTime = TIME;

        // Handle the case when time is 0
        if (tmpTime == 0) {
            drawStrokeChar('0', 4.5, -1, 0);
        }
        else {
            while (tmpTime) {
                mod = tmpTime % 10;
                number = number * 10 + mod;
                tmpTime /= 10;
            }

            float tmp = 0;
            while (number) {
                mod = number % 10;
                drawStrokeChar(mod + 48, 4.5 + tmp, -1, 0);
                number /= 10;
                tmp += 0.2;
            }
        }
    }
    else {
        score = 0;

        for (int i = 0; i < 7; i++) {
            torusActive[i] = true;
        }

        glPushMatrix();
        glTranslated(0, 3, 0);
        glRotated(aa, 0, 1, 0);
        glScaled(1.5, 1.5, 1.5);
        plane();
        glPopMatrix();

        drawStrokeText2("Plane Game", -2, 0, 0);
        drawStrokeText("Press G to Start", -1, -1, 0);
    }
    read_file();
    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
//
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1366, 720);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    read_file();
    //glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}