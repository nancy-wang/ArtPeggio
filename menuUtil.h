/** Assignment 6, 600.120
    Nancy Wang
    nwang22@jhu.edu
    nwang22
    April 4, 2017
*/
#ifndef MENUUTIL_H
#define MENUUTIL_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ppMIO.h"

void menu_prompt();
void readInput(char c, Pixel* temp, Pixel* tempo, PPM** image);

#endif
