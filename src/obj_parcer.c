#include "obj_parcer.h"

// int main() {
//     obj_data data = obj_parcer("obj_files/cube.obj");
//     obj_print(data);
// }

/* главный парсер, который записывает данные из obj файла и записывает 
их в переменную типа obj_data, которую и возвращает сама функция*/
obj_data obj_parcer(char *name_obj_file) {
    obj_data data;

    amount_of_vertexes_and_facets(name_obj_file, &data);
    obj_parcing(name_obj_file, &data);
    return data;
}

// подсчет количества врешин и полигонов и запись этих данных в структуру типа obj_data
void amount_of_vertexes_and_facets(char *name_obj_file, obj_data *data) {
    FILE *obj_file;
    char str[LENSTR];

    data->count_of_vertexes = 0;
    data->count_of_facets = 0;
    if ((obj_file = fopen(name_obj_file, "r")) == NULL) {
       printf("file is not found\n");
    } else {
        while (!feof(obj_file)) {
            fgets(str, LENSTR, obj_file);
            if (str[0] == 'v' && str[1] == ' ') {
                data->count_of_vertexes++;
            } else if (str[0] == 'f' && str[1] == ' ') {
                data->count_of_facets++;
            }
        }
    }
    fclose(obj_file);
}

void obj_parcing(char *name_obj_file, obj_data *data) {
    FILE *obj_file;
    char str[LENSTR];

    if ((obj_file = fopen(name_obj_file, "r")) == NULL) {
       printf("file is not found\n");
    } else {
        int num_of_row_coordinates = 0;
        // int num_of_row_polygons = 0;
        memories_for_coordinates(data);
        while (!feof(obj_file)) {
            char number[20];
            int check = 0;

            fgets(str, LENSTR, obj_file);
            if (str[0] == 'v' && str[1] == ' ') {
                int num_of_column = 0;
                num_of_row_coordinates++;
                for (int i = 2, j = 0; str[i] != '\n'; i++) {

                    if (((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-') && check == 0) {
                        number[j] = str[i];
                        j++;
                    } else {
                        number[j] = '\0';
                        data->matrix_3d.matrix[num_of_row_coordinates][num_of_column] = atof(number);
                        j = 0;
                        num_of_column++;
                    }
                }
            } /*else if (str[0] == 'f' && str[1] == ' ') {
                
            }*/
        }
    }
    fclose(obj_file);
}

// выделяем память под матрицу координат
void memories_for_coordinates(obj_data *data) {
    data->matrix_3d.rows = data->count_of_vertexes;
    data->matrix_3d.cols = 3;
    data->matrix_3d.matrix = (double**)calloc(data->matrix_3d.rows + 1, sizeof(double*));
    for (int i = 1; i < data->matrix_3d.rows + 1; i++) {
        data->matrix_3d.matrix[i] = (double*)calloc(3, sizeof(double));
    }
}

// выделяем память и заполняем структуру с информацией о полигонах
// void matrix_of_polygons(polygon_t* polygons, obj_data *data) {

// }

// вспомогательная функция для распечатки данных obj файла
void obj_print(obj_data data) {
    printf ("count of vertexes = %d\n", data.count_of_vertexes);
    printf ("count of facets = %d\n", data.count_of_facets);
    printf ("matrix of coordinates vertexes\n");
    for (int i = 1; i < data.count_of_vertexes + 1; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f   ", data.matrix_3d.matrix[i][j]);
        }
        printf("\n");
    }
}