#ifndef SRC_OBJ_PARCER_H_
#define SRC_OBJ_PARCER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LENSTR 500

typedef struct polygons {
    int num_vertexes;
    unsigned int* polygon_i;
} polygon_t;

typedef struct data {
    unsigned int amount_of_vertexes;
    unsigned int amount_of_facets;
    unsigned int count_of_vertexes_in_facets;
    double maxwidth;
    double minwidth;
    double maxheight;
    double minheight;
    double maxdepth;
    double mindepth;
    double max;
    polygon_t* polygons;
    double *vertexes_array;
    unsigned int* indexes_array;
} obj_data;

int obj_parcer(char *name_obj_file, obj_data *data);
int amount_of_vertexes_and_facets(char *name_obj_file, obj_data *data);
void obj_parcing(char *name_obj_file, obj_data *data);
void parcig_of_coordinates(char *str, obj_data *data, int n);
void parcig_of_facets(char *str, obj_data *data, int m);
void writing_indexes_array(obj_data *data);
void correct_vertexes_array(obj_data *data);
void free_obj(obj_data *data);

#endif  // SRC_OBJ_PARCER_H_
