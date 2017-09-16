/** Assignment 6, 600.120
    Nancy Wang
    nwang22
    nwang22@jhu.edu
    April 4, 2017
*/

#include <stdio.h>
#include "menuUtil.h"
#include "ppMIO.h"
int main() {
    char c = '\0';
    PPM* image = NULL;
    Pixel* temp = NULL;
    Pixel* tempo = NULL;
    do {
        menu_prompt();
        c = getchar();
        readInput(c, temp, tempo, &image);
        if (c == 'q') {
            exit(0);
        }
    } while (scanf("%c", &c));
    return 0;
}
