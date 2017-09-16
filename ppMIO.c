/** Assignment 6, 600.120
    Nancy Wang
    nwang22
    nwang22@jhu.edu
    April 4, 2017
*/
#include "ppMIO.h"


void checkComment(FILE* infile) {
    char c;
    while (isspace(c = fgetc(infile))) {
        while ((c = fgetc(infile))  == '#') {
            while ((c = fgetc(infile)) != '\n') {
            }
        }
        ungetc(c, infile);
    }
    ungetc(c, infile);
}

int checkFile(PPM** image) {
    if ((*image) == NULL) {
        return 1;
    }
    return 0;
}
int fileWriter(FILE* outfile, PPM** image) {
    int number = 0;
    fprintf(outfile, "P6");
    fprintf(outfile, "\n%d %d\n", (*image)->column, (*image)->row);
    fprintf(outfile, "%d\n\n\n", (*image)->color);
    number = fwrite((*image)->data, sizeof(Pixel), ((*image)->row) * ((*image)->column), outfile);
    fclose(outfile);
    return number;
}

void invertPic(PPM** image) {
    for (int i = 0; i < ((*image)->row) * ((*image)->column); i++) {
        (*image)->data[i].red  = 255 - (*image)->data[i].red;
        (*image)->data[i].green = 255 - (*image)->data[i].green;
        (*image)->data[i].blue = 255 - (*image)->data[i].blue;
    }
}
void greyScale(int intensity, PPM** image) {
    for (int i = 0; i < ((*image)->row) * ((*image)->column); i++) {
        intensity = 0.3 * ((*image)->data[i].red) + 0.59 * ((*image)->data[
                        i].red) + (0.11) * ((*image)->data[i].blue);
        (*image)->data[i].red = intensity;
        (*image)->data[i].blue = intensity;
        (*image)->data[i].green  = intensity;
    }
}
void swapColors(Pixel* temp, PPM** image) {
    for (int i = 0; i < ((*image)->row) * ((*image)->column); i++) {
        temp[i].red = (*image)->data[i].red;
        (*image)->data[i].red = (*image)->data[i].green;
        (*image)->data[i].green = (*image)->data[i].blue;
        (*image)->data[i].blue = temp[i].red;
    }
}
unsigned char adjustBright(double delta, double data) {
    double result = 0;
    result = data * delta;
    if (result > 255) {
        result = 255;
    } else if (result < 0) {
        result = 0;
    } else {
        result = (unsigned char) result;
    }
    return result;
}
