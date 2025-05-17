#include <GL/glut.h>
#include "rendering.h"
#include "globals.h"

void plane() {
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t * 90.0;

    /// Main body
    glColor3d(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(3, 0.4, 0.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3d(0.0 / 255, 94.0 / 255, 184.0 / 255); 
    glPushMatrix();
    glTranslated(1.7, 0.1, 0);
    glScaled(1.5, 0.7, 0.8);
    glRotated(40, 0, 1, 0);
    glutSolidSphere(0.45, 30, 30);
    glPopMatrix();

    /// Right wing
    glColor3d(0.0 / 255, 94.0 / 255, 184.0 / 255); // lighter blue wing
    glPushMatrix();
    glTranslated(0, 0, 1.2);
    glRotated(-50, 0, 1, 0);
    glScaled(0.7, 0.1, 3);
    glRotated(25, 0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(1.0, 1.0, 1.0); // white accent torus
    glPushMatrix();
    glTranslated(-0.3, -0.15, 1.5);
    glRotated(90, 0, 1, 0);
    glScaled(0.1, 0.1, 0.9);
    glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    glColor3d(1.0, 1.0, 1.0); // white accent torus
    glPushMatrix();
    glTranslated(0.2, -0.15, 0.9);
    glRotated(90, 0, 1, 0);
    glScaled(0.1, 0.1, 0.9);
    glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    /// Left wing (mirror of right wing)
    glColor3d(0.0 / 255, 94.0 / 255, 184.0 / 255); // lighter blue wing
    glPushMatrix();
    glTranslated(0, 0, -1.2);
    glRotated(50, 0, 1, 0);
    glScaled(0.7, 0.1, 3);
    glRotated(-25, 0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();

    glColor3d(1.0, 1.0, 1.0); // white accent torus
    glPushMatrix();
    glTranslated(-0.3, -0.15, -1.5);
    glRotated(90, 0, 1, 0);
    glScaled(0.1, 0.1, 0.9);
    glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    glColor3d(1.0, 1.0, 1.0); // white accent torus
    glPushMatrix();
    glTranslated(0.2, -0.15, -0.9);
    glRotated(90, 0, 1, 0);
    glScaled(0.1, 0.1, 0.9);
    glutSolidTorus(0.5, 0.5, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.8, 0, 0);
    glScaled(0.8, 0.5, 0.3);

    /// Right smaller wing
    glColor3d(0.0 / 255, 94.0 / 255, 184.0 / 255); // lighter blue
    glPushMatrix();
    glTranslated(0.4, 0, 1.5);
    glRotated(-30, 0, 1, 0);
    glScaled(0.7, 0.1, 3);
    glRotated(10, 0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();

    /// Left smaller wing
    glColor3d(0.0 / 255, 94.0 / 255, 184.0 / 255); // lighter blue
    glPushMatrix();
    glTranslated(0.4, 0, -1.5);
    glRotated(30, 0, 1, 0);
    glScaled(0.7, 0.1, 3);
    glRotated(-10, 0, 1, 0);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    glColor3d(0.0 / 255, 94.0 / 255, 184.0 / 255); // lighter blue
    glPushMatrix();
    glTranslated(-2.7, 0.5, 0);
    glRotated(45, 0, 0, 1);
    glScaled(0.8, 2, 0.1);
    glRotated(-20, 0, 0, 1);
    glutSolidCube(0.5);
    glPopMatrix();

    glColor3d(1.0, 1.0, 1.0); // white accent
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

