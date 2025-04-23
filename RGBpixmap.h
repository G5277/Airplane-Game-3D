#ifndef RGBPIXMAP_H
#define RGBPIXMAP_H

#include <gl/glut.h>

typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned char uchar;

class mRGB {
public:
    uchar r, g, b, a;
    mRGB() { r = g = b = 0; a = 255; }
};

class RGBpixmap {
public:
    int nRows, nCols;
    mRGB* pixel;

    void readBMPFile(char* frame);
    //void makeCheckerBoard();
    void makeCheckImage();
    void setTexture(GLuint textureName);
};

// Utility functions used inside readBMPFile
ushort getShort();
ulong getLong();

#endif
