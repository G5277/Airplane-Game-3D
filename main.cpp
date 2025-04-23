#include<windows.h>
#include <GL/glut.h>
//#include<bits/stdc++.h>
#include <stdlib.h>
#include<cmath>
#define rad (3.1416/180)
#define EN_SIZE 20

#include "RGBpixmap.h"

using namespace std;

RGBpixmap pix[6];

int score = 0;
bool torusActive[7] = { true, true, true, true, true, true, true }; // Track which circles are active


float zoom = 4;
int tola[5000][5000];
float tX = 0, tY = 0, tZ = -8, rX = 0, rY = 0, rZ = 4;
float tZ1 = -20, tZ2 = -40, tZ3 = -60, tZ4 = -80, tZ5 = -100, tZ6 = -120;
float rotX = 0, rotY = 0, rotZ = 0;
float cosX = 0, cosY = 1, cosZ = 0;
float angle = 0;
float xEye = 0.0f, yEye = 5.0f, zEye = 30.0f;
float cenX = 0, cenY = 0, cenZ = 0, roll = 0;
float radius = 0;
float theta = 0, slope = 0;
float speed = 0.3;
float angleBackFrac = 0.2;
float r[] = { 0.1,0.4,0.0,0.9,0.2,0.5,0.0,0.7,0.5,0.0 };
float g[] = { 0.2,0.0,0.4,0.5,0.2,0.0,0.3,0.9,0.0,0.2 };
float b[] = { 0.4,0.5,0.0,0.7,0.9,0.0,0.1,0.2,0.5,0.0 };
int TIME = 0;
bool START = false;
float torusPosX[7] = { 1,-2,3,-4,-2,0,2 };
float torusPosY[7] = { 2,3,10,6,7,4,1 };

bool rot = false;

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

void plane() {
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t * 90.0;

    /// Main body
    glColor3d(0.5, 0, 1); // Purple color
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(3, 0.4, 0.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3d(0.2, 0, 0.5); // Darker purple
    glPushMatrix();
    glTranslated(1.7, 0.1, 0);
    glScaled(1.5, 0.7, 0.8);
    glRotated(40, 0, 1, 0);
    glutSolidSphere(0.45, 30, 30);
    glPopMatrix();

    ///Right
    glColor3d(0.6, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(0, 0, 1.2);
    glRotated(-50, 0, 1, 0);
    glScaled(0.7, 0.1, 3);
    glRotated(25, 0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(0.7, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(-0.3, -0.15, 1.5);
    glRotated(90, 0, 1, 0);
    glScaled(0.1, 0.1, 0.9);
    glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    glColor3d(0.7, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(0.2, -0.15, 0.9);
    glRotated(90, 0, 1, 0);
    glScaled(0.1, 0.1, 0.9);
    glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    ///Left
    glColor3d(0.6, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(0, 0, -1.2);
    glRotated(50, 0, 1, 0);
    glScaled(0.7, 0.1, 3);
    glRotated(-25, 0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(0.7, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(-0.3, -0.15, -1.5);
    glRotated(90, 0, 1, 0);
    glScaled(0.1, 0.1, 0.9);
    glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    glColor3d(0.7, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(0.2, -0.15, -0.9);
    glRotated(90, 0, 1, 0);
    glScaled(0.1, 0.1, 0.9);
    glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.8, 0, 0);
    glScaled(0.8, 0.5, 0.3);

    ///Right
    glColor3d(0.6, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(0.4, 0, 1.5);
    glRotated(-30, 0, 1, 0);
    glScaled(0.7, 0.1, 3);
    glRotated(10, 0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();

    ///left
    glColor3d(0.6, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(0.4, 0, -1.5);
    glRotated(30, 0, 1, 0);
    glScaled(0.7, 0.1, 3);
    glRotated(-10, 0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    glColor3d(0.6, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(-2.7, 0.5, 0);
    glRotated(45, 0, 0, 1);
    glScaled(0.8, 2, 0.1);
    glRotated(-20, 0, 0, 1);
    glutSolidCube(0.5);
    glPopMatrix();

    glColor3d(0.7, 0, 1); // Lighter purple
    glPushMatrix();
    glTranslated(-2.95, 0.85, 0);
    glRotated(90, 0, 1, 0);
    glScaled(0.05, 0.05, 0.6);
    glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();
}

void singleHouse(int R, int G, int B) {
    glColor3d(r[R % 11], g[G % 11], b[B % 11]);
    glPushMatrix();
    glTranslated(0, 0, 0);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(0, 0, 0);
    glPushMatrix();
    glTranslated(0.2, 0, 0);
    glScaled(0.3, 0.3, 1.001);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(0, 0, 0);
    glPushMatrix();
    glTranslated(-0.2, 0, 0);
    glScaled(0.3, 0.3, 1.001);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(0, 0, 0);
    glPushMatrix();
    glTranslated(0, 0, 0.2);
    glScaled(1.001, 0.3, 0.3);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(0, 0, 0);
    glPushMatrix();
    glTranslated(0, 0, -0.2);
    glScaled(1.001, 0.3, 0.3);
    glutSolidCube(1);
    glPopMatrix();

}

void house(int n, int R, int G) {
    for (int i = 0;i < n;i++) {
        glPushMatrix();
        glTranslated(0, 0.8 + i, 0);
        singleHouse(G, R, i);
        glPopMatrix();
    }
}

static void environment(int n) {

    /// Ground (Road)
    glColor3d(0.2, 0.2, 0.2); // Dark gray color for the road
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(EN_SIZE * 2, 0.3, EN_SIZE * 2);
    glutSolidCube(1); // Creating the base of the road
    glPopMatrix();

    // Lane markings (yellow stripes)
    glColor3d(1, 1, 0); // Yellow color for lane markings
    glPushMatrix();

    // Create lane markings
    for (float i = -EN_SIZE * 2 / 2; i < EN_SIZE * 2 / 2; i += 4.0f) {
        glPushMatrix();
        glTranslated(i, 0.3, 0); // Position lane markings along the road
        glScaled(0.2, 0.05, 0.5); // Thin, long, and stretched lane markings
        glutSolidCube(1); // Draw each lane marking
        glPopMatrix();
    }

    glPopMatrix();

    // Example for objects on the ground
    glColor3d(1,0,0);
    glPushMatrix();
    glTranslated(torusPosX[n], torusPosY[n], 0);
    glScaled(0.3, 0.3, 0.3);
    glutSolidTorus(1, 3, 30, 30);
    glPopMatrix();

    for (int i = -(EN_SIZE / 2) + 1; i < (EN_SIZE / 2); i += 2) {
        for (int j = -(EN_SIZE / 2) + 1; j < (EN_SIZE / 2); j += 2) {
            if (tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1] != 0) {
                glPushMatrix();
                glTranslated(i, 0, j);
                house(tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1], i, j);
                glPopMatrix();
            }
            else if (i >= -5 && i <= 5) {
                // Optional: Skip certain area for some visual effect
            }
            else {
                tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1] = (rand() % 5) + 1;
                glPushMatrix();
                glTranslated(i, 0, j);
                house(tola[i + (EN_SIZE / 2) + 1][j + (EN_SIZE / 2) + 1], i, j);
                glPopMatrix();
            }
        }
    }
}

// Improved collision detection function that checks if plane passes through the middle of the torus
bool checkThroughRing(float planeX, float planeY, float torusX, float torusY, float tZ_val) {
    // Calculate horizontal and vertical distance to the ring center 
    float horizontalDist = sqrt(pow(planeX - torusX, 2) + pow(planeY - torusY, 2));

    // For a ring pass-through:
    // 1. We should be close to the ring horizontally (within the ring's inner opening)
    // 2. We should be very close to the ring's z-position (passing through it)

    // Ring inner radius (adjust based on your torus dimensions)
    float ringInnerRadius = 0.9;  // Reduced from torus inner radius for more precise detection

    // Z-axis pass-through threshold - how close the plane needs to be on Z-axis
    float zThreshold = 0.5;

    // Check if we're within the inner circle and close enough on Z axis
    bool withinInnerOpening = horizontalDist < ringInnerRadius;
    bool passingThroughZ = fabs(tZ_val) < zThreshold;

    // We also want this to trigger only once when passing through,
    // so we check if the Z value is moving in the positive direction
    // (i.e., plane is moving toward the screen)
    bool movingTowardScreen = tZ_val > -0.2 && tZ_val < 0.2;

    return withinInnerOpening && passingThroughZ && movingTowardScreen;
}

void draw() {
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t * 90.0;

    TIME = t;

    // Current plane position
    float planeX = 0; // Plane is at origin X
    float planeY = 1; // Plane is at Y=1

    ///Plane
    if (rotX > 11)rotX = 11;
    if (rotX < -11)rotX = -11;
    if (rotZ > 10)rotZ = 10;
    if (rotZ < -15)rotZ = -15;

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

    ///Environment
    if (tX >= 4.1)tX = 4.1;
    if (tX <= -4.1)tX = -4.1;
    if (tY > 0.1)tY = 0.1;
    if (tY < -15)tY = -15;

    // Check for collisions and draw environments with their respective toruses

    // First environment
    if (torusActive[2] && checkThroughRing(planeX - tX, planeY - tY, torusPosX[2], torusPosY[2], tZ)) {
        score += 10;
        torusActive[2] = false;
    }

    glPushMatrix();
    glTranslated(tX, tY, tZ);
    if (!torusActive[2]) {
        // Draw environment without torus if collected
        int originalTorusIndex = 2;
        int tempIndex = originalTorusIndex;
        torusActive[originalTorusIndex] = false;
        environment(tempIndex);
        torusActive[originalTorusIndex] = false;
    }
    else {
        environment(2);
    }
    glPopMatrix();

    // Second environment
    if (torusActive[3] && checkThroughRing(planeX - tX, planeY - tY, torusPosX[3], torusPosY[3], tZ2)) {
        score += 10;
        torusActive[3] = false;
    }

    glPushMatrix();
    glTranslated(tX, tY, tZ2);
    if (!torusActive[3]) {
        // Draw environment without torus if collected
        int originalTorusIndex = 3;
        int tempIndex = originalTorusIndex;
        torusActive[originalTorusIndex] = false;
        environment(tempIndex);
        torusActive[originalTorusIndex] = false;
    }
    else {
        environment(3);
    }
    glPopMatrix();

    // Third environment
    if (torusActive[1] && checkThroughRing(planeX - tX, planeY - tY, torusPosX[1], torusPosY[1], tZ3)) {
        score += 10;
        torusActive[1] = false;
    }

    glPushMatrix();
    glTranslated(tX, tY, tZ3);
    if (!torusActive[1]) {
        // Draw environment without torus if collected
        int originalTorusIndex = 1;
        int tempIndex = originalTorusIndex;
        torusActive[originalTorusIndex] = false;
        environment(tempIndex);
        torusActive[originalTorusIndex] = false;
    }
    else {
        environment(1);
    }
    glPopMatrix();

    // Fourth environment
    if (torusActive[5] && checkThroughRing(planeX - tX, planeY - tY, torusPosX[5], torusPosY[5], tZ4)) {
        score += 10;
        torusActive[5] = false;
    }

    glPushMatrix();
    glTranslated(tX, tY, tZ4);
    if (!torusActive[5]) {
        // Draw environment without torus if collected
        int originalTorusIndex = 5;
        int tempIndex = originalTorusIndex;
        torusActive[originalTorusIndex] = false;
        environment(tempIndex);
        torusActive[originalTorusIndex] = false;
    }
    else {
        environment(5);
    }
    glPopMatrix();

    // Fifth environment
    if (torusActive[4] && checkThroughRing(planeX - tX, planeY - tY, torusPosX[4], torusPosY[4], tZ5)) {
        score += 10;
        torusActive[4] = false;
    }

    glPushMatrix();
    glTranslated(tX, tY, tZ5);
    if (!torusActive[4]) {
        // Draw environment without torus if collected
        int originalTorusIndex = 4;
        int tempIndex = originalTorusIndex;
        torusActive[originalTorusIndex] = false;
        environment(tempIndex);
        torusActive[originalTorusIndex] = false;
    }
    else {
        environment(4);
    }
    glPopMatrix();

    // Sixth environment
    if (torusActive[2] && checkThroughRing(planeX - tX, planeY - tY, torusPosX[2], torusPosY[2], tZ6)) {
        score += 10;
        torusActive[2] = false;
    }

    glPushMatrix();
    glTranslated(tX, tY, tZ6);
    if (!torusActive[2]) {
        // Draw environment without torus if collected
        int originalTorusIndex = 2;
        int tempIndex = originalTorusIndex;
        torusActive[originalTorusIndex] = false;
        environment(tempIndex);
        torusActive[originalTorusIndex] = false;
    }
    else {
        environment(2);
    }
    glPopMatrix();

    // Move environments and reset when they go offscreen
    tZ += speed;
    tZ1 += speed;
    tZ2 += speed;
    tZ3 += speed;
    tZ4 += speed;
    tZ5 += speed;
    tZ6 += speed;

    if (tZ >= 20) {
        tZ = -110;
        torusActive[2] = true; // Reset torus when environment recycles
    }
    if (tZ1 >= 20) {
        tZ1 = -110;
        // No torus in environment 1 based on original code
    }
    if (tZ2 >= 20) {
        tZ2 = -110;
        torusActive[3] = true;
    }
    if (tZ3 >= 20) {
        tZ3 = -110;
        torusActive[1] = true;
    }
    if (tZ4 >= 20) {
        tZ4 = -110;
        torusActive[5] = true;
    }
    if (tZ5 >= 20) {
        tZ5 = -110;
        torusActive[4] = true;
    }
    if (tZ6 >= 20) {
        tZ6 = -110;
        torusActive[2] = true; // Same as first environment
    }

    if (rotX > 0)rotX -= angleBackFrac;
    if (rotX < 0)rotX += angleBackFrac;
    if (rotY > 0)rotY -= angleBackFrac;
    if (rotY < 0)rotY += angleBackFrac;
    if (rotZ > 0)rotZ -= angleBackFrac;
    if (rotZ < 0)rotZ += angleBackFrac;

    speed += 0.0002;
    if (speed >= 0.7)speed = 0.7;
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
    if (!rot) {
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
        drawStrokeText("UP: W, DOWN: S, LEFT: A, RIGHT: D, MAIN MENU: M", -8, 0, 0);

        // Score on the left bottom
        drawStrokeText("SCORE: ", -8, -1, 0);
        int tempScore = score;
        float digitPos = -6.5;

        // Handle the case when score is 0
        if (tempScore == 0) {
            drawStrokeChar('0', digitPos, -1, 0);
        }
        else {
            // Convert score to digits and display them
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
        // Reset score when returning to menu
        score = 0;

        // Reset all toruses to active
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

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    float frac = 0.3;
    float rotFrac = 1;
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;
    case 'r':
        rot = true;
        break;
    case 't':
        rot = false;
        break;
    case 'z':
        zoom += 0.05;
        break;
    case 'Z':
        zoom -= 0.05;
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

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

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
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    // Set background color to light blue (RGB: 0.5, 0.7, 1.0)
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);  // Light blue color

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
