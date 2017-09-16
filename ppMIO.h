/** Assignment 6, 600.120
    Nancy Wang
    nwang22
    nwang22@jhu.edu
    April 4, 2017
*/
#ifndef PPMIO_H
#define PPMIO_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct _Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

typedef struct _PPMInfo {
    int column;
    int row;
    int color;
    Pixel* data;
} PPM;

void checkComment(FILE* infile);
int checkFile(PPM** image);
int fileWriter(FILE* outfile, PPM** image);
void invertPic(PPM** image);
void greyScale(int intensity, PPM** image);
void swapColors(Pixel* temp, PPM** image);
unsigned char adjustBright(double delta, double data);
#endif
