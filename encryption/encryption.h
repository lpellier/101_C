#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

float determinant(int **matrix, int size);
float ** cofactor(int **matrix, int size);
float ** transpose(int **num, float **fac, int size);