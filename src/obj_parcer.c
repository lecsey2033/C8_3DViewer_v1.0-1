#include "obj_parcer.h"

// проверка работы парсера
/*int main() {
    obj_data data = obj_parcer("obj_files/cube.obj");
    obj_print(data);
    free_obj_data(&data);
}*/

/*функция, которая считает количество вершин и полигонов
и вызывает главный парсер результат работы которого возвращает в типе данных obj_data*/
obj_data obj_parcer(char *name_obj_file) {
    obj_data data;

    amount_of_vertexes_and_facets(name_obj_file, &data);
    obj_parcing(name_obj_file, &data);
    return data;
}

// Зачистка выделенной памяти (ОБЯЗАТЕЛЬНО!!! после вывода всей необходимой информации)
void free_obj_data(obj_data *data) {
    /*отчистка матрицы*/
    for (int i = 0; i < data->count_of_vertexes + 1; i++) {
        free(data->matrix_3d.matrix[i]);
    }
    free(data->matrix_3d.matrix);
    /*отчистка полигонов*/
    for (int i = 0; i < data->count_of_facets + 1; i++) {
        free(data->polygons[i].vertexes);
    }
    free(data->polygons);
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

/*главный парсер, который записывает данные из obj файла и записывает 
их в переменную типа obj_data*/
void obj_parcing(char *name_obj_file, obj_data *data) {
    FILE *obj_file;

    if ((obj_file = fopen(name_obj_file, "r")) == NULL) {
       printf("file is not found\n");
    } else {
        char str[LENSTR];
        int num_of_row_coordinates = 0;
        int num_of_row_polygons = 0;
        memories_for_coordinates_and_polygons(data);
        while (!feof(obj_file)) {
            fgets(str, LENSTR, obj_file);
            if (str[0] == 'v' && str[1] == ' ') {
                parcig_of_coordinates(&num_of_row_coordinates, str, data);
            } else if (str[0] == 'f' && str[1] == ' ') {
                parcig_of_polygons(&num_of_row_polygons, str, data);
            }
        }
    }
    fclose(obj_file);
}

// выделяем память под матрицу координат и присваивает значения переменным rows и cols
// выделяем память под массив структур содержащих информацию о полигонах
void memories_for_coordinates_and_polygons(obj_data *data) {
    data->matrix_3d.rows = data->count_of_vertexes;
    data->matrix_3d.cols = 3;
    data->matrix_3d.matrix = (double**)calloc(data->matrix_3d.rows + 1, sizeof(double*));
    for (int i = 1; i < data->count_of_vertexes + 1; i++) {
        data->matrix_3d.matrix[i] = (double*)calloc(3, sizeof(double));
    }
    data->polygons = (polygon_t*)calloc(data->count_of_facets + 1, sizeof(polygon_t));
}

// парсинг координат вершин и запись их в структуру obj_data
void parcig_of_coordinates(int *num_of_row_coordinates, char *str, obj_data *data) {
    char number[20];
    int num_of_column = 0;
    int check = 0;

    (*num_of_row_coordinates)++; 
    for (int i = 2, j = 0; check == 0; i++) {
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-') {
            number[j] = str[i];
            j++;
        } else {
            if (str[i] == '\0') {check = 1;}
            number[j] = '\0';
            data->matrix_3d.matrix[*num_of_row_coordinates][num_of_column] = atof(number);
            j = 0;
            num_of_column++;
        }
    }
}

// парсинг полигонов и запись их в структуру obj_data
void parcig_of_polygons(int *num_of_row_polygons, char *str, obj_data *data) {
    char number[20];
    int num_of_column = 0;
    int check = 0;

    (*num_of_row_polygons)++;
    data->polygons[*num_of_row_polygons].numbers_of_vertexes_in_facets = 0;

    for (int i = 1; str[i]; i++) {
        if (str[i] == ' ' && ((str[i+1] >= '0' && str[i+1] <= '9') || str[i+1] == '-')) {
            data->polygons[*num_of_row_polygons].numbers_of_vertexes_in_facets++;
        }
    }
    data->polygons[*num_of_row_polygons].vertexes = (int*)calloc(data->polygons[*num_of_row_polygons].numbers_of_vertexes_in_facets, sizeof(int));
    for (int i = 2, j = 0; check == 0; i++) {
        if (str[i] == '-') {
            i++;
        }
        if (str[i] >= '0' && str[i] <= '9') {
            number[j] = str[i];
            j++;
        } else if (str[i] == '/') {
            while (str[i+1] != ' ' && str[i+2] != '\n') {
                i++;
            }
        } else {
            if (str[i] == '\0') {check = 1;}
            number[j] = '\0';
            data->polygons[*num_of_row_polygons].vertexes[num_of_column] = atoi(number);
            j = 0;
            num_of_column++;
        }
        
    } 
}            

// вспомогательная функция для распечатки данных obj файла
void obj_print(obj_data data) {
    printf ("count of vertexes = %d\n", data.count_of_vertexes);
    printf ("count of facets = %d\n", data.count_of_facets);
    printf ("matrix of coordinates vertexes\n");
    for (int i = 1; i < data.count_of_vertexes + 1; i++) {
        printf("%d.  ", i);
        for (int j = 0; j < 3; j++) {
            printf("%10f   ", data.matrix_3d.matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf ("matrix of facets\n");
    for (int i = 1; i < data.count_of_facets + 1; i++) {
        printf("%d.  ", i);
        for (int j = 0; j < data.polygons[i].numbers_of_vertexes_in_facets; j++) {
            printf("%6d   ", data.polygons[i].vertexes[j]);
        }
        printf("\n");
    }
}