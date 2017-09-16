/** Assignment 6, 600.120
    Nancy Wang
    nwang22
    nwang22@jhu.edu
    April 4, 2017
*/

#include "menuUtil.h"

void menu_prompt() {
    printf(
        "Main menu:\n"
        "r <filename> - read image from <filename> \n"
        "w <filename> - write image to <filename> \n"
        "c <x1> <y1> <x2> <y2> - crop image to the box with the given corners\n"
        "i - invert intensities\n"
        "s - swap color channels\n"
        "g - convert to grayscale\n"
        "b <amt> - change brightness (up or down) by the given amount\n"
        "q - quit\n");
}

void readInput(char c, Pixel* temp, Pixel* tempo, PPM** image) {
    char file[100];
    char ch = '\0';
    int row = 0;
    int column = 0;
    int color = 0;
    int column1 = 0;
    int column2 = 0;
    int row1 = 0;
    int row2 = 0;
    double brightness = 0;
    int intensity = 0;
    int count = 0;
    int count2 = 0;
    int discard = 0;
    int num = 0;
    switch (c) {
    case 'r':
        scanf("%s", file);
        FILE* infile = fopen(file, "r + b");
        if (!infile) {
            printf("Error: file %s not found\n", file);
            break;
        }
        if ((ch = fgetc(infile)) == 'P' && (ch = fgetc(infile)) == '6') {
            checkComment(infile);
            fscanf(infile, "%d", &column);
            checkComment(infile);
            fscanf(infile, "%d", &row);
            checkComment(infile);
            fscanf(infile, "%d", &color);
        }
        (*image) = malloc(sizeof(PPM));
        (*image)->column = column;
        (*image)->row = row;
        (*image)->color = color;
        (*image)->data = malloc(sizeof(Pixel) * ((*image)->row) * ((*image)->column));
        fread((*image)->data, sizeof(Pixel), ((*image)->row) * ((*image)->column), infile);
        printf("Reading from %s...\n", file);
        fclose(infile);
        break;
    case 'w':
        scanf("%s", file);
        FILE* outfile = fopen(file, "w");
        num = checkFile(image);
        if (num == 1) {
            printf("Error: there is no current image\n");
            break;
        }
        fileWriter(outfile, image);
        printf("Writing to %s...\n", file);
        break;
    case 'c':
        scanf("%d", &row1);
        scanf("%d", &column1);
        scanf("%d", &row2);
        scanf("%d", &column2);
        num = checkFile(image);
        if (num == 1) {
            printf("Error: there is no current image\n");
            break;
        }
        if ((column2 < column1) || (row2 < row1)) {
            printf("Error: cropping failed, image unchanged\n");
        }
        column = column2 - column1;
        row = row2 - row1;
        if ((column > ((*image)->column)) || (row > ((*image)->row))) {
            printf("Error: cropping failed, image unchanged\n");
            break;
        }
        tempo = malloc(sizeof(Pixel) * row * column);
        count2 = (((*image)->column) * row1) + column1;
        discard = ((*image)->column) - column;
        for (int i = row1; i < row2; i++) {
            for (int j = column1; j < column2; j++) {
                tempo[count] = ((*image)->data)[count2];
                count++;
                count2++;
            }
            count2 += discard;
        }
        (*image)->data = tempo;
        (*image)->row = row;
        (*image)->column = column;
        break;
    case 'i':
        num = checkFile(image);
        if (num == 1) {
            printf("Error: there is no current image\n");
            break;
        }
        invertPic(image);
        printf("Inverting intensity...\n");
        break;
    case 's':
        num = checkFile(image);
        if (num == 1) {
            printf("Error: there is no current image\n");
            break;
        }
        temp = malloc(sizeof(Pixel) * ((*image)->row) * ((*image)->column));
        swapColors(temp, image);
        printf("Swapping color channels...\n");
        free(temp);
        break;
    case 'g':
        num = checkFile(image);
        if (num == 1) {
            printf("Error: there is no current image\n");
            break;
        }
        greyScale(intensity, image);
        printf("Converting to grayscale...\n");
        break;
    case 'b':
        scanf("%lf", &brightness);
        num = checkFile(image);
        if (num == 1) {
            printf("Error: there is no current image\n");
            break;
        }
        for (int i = 0; i < ((*image)->row) * ((*image)->column); i++) {
            (*image)->data[i].red = adjustBright(brightness, (*image)->data[i].red);
            (*image)->data[i].blue = adjustBright(brightness, (*image)->data[i].blue);
            (*image)->data[i].green = adjustBright(brightness, (*image)->data[i].green);
        }
        printf("Adjusting brightness by %lf...\n", brightness);
        break;
    case 'q':
        printf("Goodbye!\n");
        num = checkFile(image);
        if (num == 1) {
            break;
        }
        free((*image)->data);
        free(*image);
        free(tempo);
        break;
    default:
        printf("Error: unknown command\n");
        break;
    }
}
