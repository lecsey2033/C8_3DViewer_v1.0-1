#ifndef SRC_OBJ_PARCER_H_
#define SRC_OBJ_PARCER_H_

#include <stdio.h>
#include <stdlib.h>

#define LENSTR 500

typedef struct Data {
	int count_of_vertexes;
    int count_of_facets;
    matrix_t matrix_3d;
} obj_data;

typedef struct Matrix {
	double **matrix;
	int rows;
	int cols;
} matrix_t;

void amount_of_vertexes_and_facets(char *name_obj_file, obj_data data);

#endif  // SRC_OBJ_PARCER_H_