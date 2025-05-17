#include <GL/glut.h>
#include "environment.h"
#include "globals.h"
#include "utils.h"
#include "rendering.h"
#include <cmath>

void environment(int n) {

    /// Ground (Road)
    glColor3d(0.2, 0.2, 0.2);
    glPushMatrix();
    glTranslated(0, 0, 0);
    glScaled(EN_SIZE * 2, 0.3, EN_SIZE * 2);
    glutSolidCube(1);
    glPopMatrix();

    // (yellow stripes)
    glColor3d(1, 1, 0);
    glPushMatrix();

    // Create lane markings
    for (float i = -EN_SIZE * 2 / 2; i < EN_SIZE * 2 / 2; i += 4.0f) {
        glPushMatrix();
        glTranslated(i, 0.3, 0);
        glScaled(0.2, 0.05, 0.5);
        glutSolidCube(1);
        glPopMatrix();
    }

    glPopMatrix();

    // obj on the ground
    glColor3d(1, 0, 0);
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

