#include "globals.h"

#define rad (3.1416/180)
#define EN_SIZE 20

int score = 0;
bool torusActive[7] = { true, true, true, true, true, true, true };

float zoom = 4;
int tola[5000][5000];

float tX = 0, tY = 0, tZ = -8, rX = 0, rY = 0, rZ = 4;
float tZ1 = -20, tZ2 = -40, tZ3 = -60, tZ4 = -80, tZ5 = -100, tZ6 = -120;

float rotX = 0, rotY = 0, rotZ = 0;
float cosX = 0, cosY = 1, cosZ = 2;
float angle = 0;

float xEye = 0.0f, yEye = 5.0f, zEye = 30.0f;
float cenX = 0, cenY = 0, cenZ = 0, roll = 0;
float radius = 0;
float theta = 0, slope = 0;

float speed = 0.3;
float angleBackFrac = 0.2;

float r[] = { 0.1, 0.4, 0.0, 0.9, 0.2, 0.5, 0.0, 0.7, 0.5, 0.0 };
float g[] = { 0.2, 0.0, 0.4, 0.5, 0.2, 0.0, 0.3, 0.9, 0.0, 0.2 };
float b[] = { 0.4, 0.5, 0.0, 0.7, 0.9, 0.0, 0.1, 0.2, 0.5, 0.0 };

int TIME = 0;
bool START = false;

float torusPosX[7] = { 1, -2, 3, -4, -2, 0, 2 };
float torusPosY[7] = { 2, 3, 10, 6, 7, 4, 1 };

bool rot = false;