#ifndef SRC_OBJ_PARCER_H_
#define SRC_OBJ_PARCER_H_

#include <stdio.h>
#include <stdlib.h>

#define LENSTR 500

typedef struct Matrix {
	double **matrix;
	int rows;
	int cols;
} matrix_t;

typedef struct facets {
	int *vertexes;
	int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct Data {
	int count_of_vertexes;
    int count_of_facets;
    matrix_t matrix_3d;
	polygon_t *polygons;
} obj_data;

obj_data obj_parcer(char *name_obj_file);
void amount_of_vertexes_and_facets(char *name_obj_file, obj_data *data);
void memories_for_coordinates(obj_data *data);
void obj_parcing(char *name_obj_file, obj_data *data);
void matrix_of_polygons(polygon_t* polygons, obj_data *data);

// вспомогательная функция для распечатки данных obj файла
void obj_print(obj_data data);

#endif  // SRC_OBJ_PARCER_H_