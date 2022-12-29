#include "obj_parcer.h"

int main() {
    obj_data data;
    amount_of_vertexes_and_facets("obj_files/cube.obj", data);
}

// подсчет количества врешин и полигонов и запись этих данных в структуру типа obj_data
void amount_of_vertexes_and_facets(char *name_obj_file, obj_data data) {
    FILE *obj_file;
    char str[LENSTR];

    data.count_of_vertexes = 0;
    data.count_of_facets = 0;
    if ((obj_file = fopen(name_obj_file, "r")) == NULL) {
       printf("file is not found\n");
    } else {
        while (!feof(obj_file)) {
            fgets(str, LENSTR, obj_file);
            if (str[0] == 'v' && str[1] == ' ') {
                data.count_of_vertexes++;
            } else if (str[0] == 'f' && str[1] == ' ') {
                data.count_of_facets++;
            }
        }
        // printf("%d %d\n", data.count_of_vertexes, data.count_of_facets);
    }
    fclose(obj_file);
}