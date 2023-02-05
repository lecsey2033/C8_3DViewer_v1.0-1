#include "obj_parcer.h"

// Функция, которая вызывает ключевые функции записывающие структуру obj_data
int obj_parcer(char *name_obj_file, obj_data *data) {
  int error = 0;
  error = amount_of_vertexes_and_facets(name_obj_file, data);
  if (error == 0) {
    data->vertexes_array =
        (double *)calloc(3 * data->amount_of_vertexes, sizeof(double));
    data->polygons =
        (polygon_t *)calloc(data->amount_of_facets, sizeof(polygon_t));
    obj_parcing(name_obj_file, data);
    correct_vertexes_array(data);
  }
  return error;
}

// инициализацие некоторых переменных и подсчет количества врешин и полигонов, и
// запись этих данных в структуру obj_data
int amount_of_vertexes_and_facets(char *name_obj_file, obj_data *data) {
  int error = 0;
  FILE *obj_file;
  char str[LENSTR];

  data->amount_of_vertexes = 0;
  data->maxwidth = 0;
  data->maxheight = 0;
  data->maxdepth = 0;
  data->minwidth = 0;
  data->minheight = 0;
  data->mindepth = 0;
  data->amount_of_facets = 0;
  data->count_of_vertexes_in_facets = 0;

  if ((obj_file = fopen(name_obj_file, "r")) == NULL) {
    error = 1;
  } else {
    while (!feof(obj_file)) {
      fgets(str, LENSTR, obj_file);
      if (str[0] == 'v' && str[1] == ' ') {
        data->amount_of_vertexes++;
      } else if (str[0] == 'f' && str[1] == ' ') {
        data->amount_of_facets++;
      }
    }
  }
  fclose(obj_file);
  return error;
}

/*главный парсер, который анализирует данные из obj файла и записывает
их в переменную типа obj_data*/
void obj_parcing(char *name_obj_file, obj_data *data) {
  FILE *obj_file;

  obj_file = fopen(name_obj_file, "r");
  char str[LENSTR];
  int n = 0;
  int m = 0;

  while (!feof(obj_file)) {
    fgets(str, LENSTR, obj_file);
    if (str[0] == 'v' && str[1] == ' ') {
      parcig_of_coordinates(str, data, n);
      n += 3;
    }
    if (str[0] == 'f' && str[1] == ' ') {
      parcig_of_facets(str, data, m);
      m++;
    }
  }
  writing_indexes_array(data);
  fclose(obj_file);
}

// парсинг координат вершин в один массив, который будет вызываться в OpenGL
// нахождение max и min по всем трём координатам
void parcig_of_coordinates(char *str, obj_data *data, int n) {
  char number[20];
  int check = 0;
  int xyz = 1;

  for (int i = 2, j = 0; check == 0; i++) {
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-') {
      number[j] = str[i];
      j++;
    } else {
      if (str[i] == '\0' || str[i] == '\n') {
        check = 1;
      }
      number[j] = '\0';
      data->vertexes_array[n] = atof(number);
      if (xyz == 1) {
        if (data->vertexes_array[n] > data->maxwidth) {
          data->maxwidth = data->vertexes_array[n];
        } else if (data->vertexes_array[n] < data->minwidth) {
          data->minwidth = data->vertexes_array[n];
        }
      } else if (xyz == 2) {
        if (data->vertexes_array[n] > data->maxheight) {
          data->maxheight = data->vertexes_array[n];
        } else if (data->vertexes_array[n] < data->minheight) {
          data->minheight = data->vertexes_array[n];
        }
      } else {
        if (data->vertexes_array[n] > data->maxdepth) {
          data->maxdepth = data->vertexes_array[n];
        } else if (data->vertexes_array[n] < data->mindepth) {
          data->mindepth = data->vertexes_array[n];
        }
      }
      xyz++;
      n++;
      j = 0;
    }
  }
}

// парсинг полигонов
void parcig_of_facets(char *str, obj_data *data, int m) {
  char number[20];
  int check = 0;
  data->polygons[m].num_vertexes = 0;

  for (int i = 1; str[i]; i++) {
    if (str[i] == ' ' && str[i + 1] != '\n' && str[i + 1] != '\0') {
      data->polygons[m].num_vertexes++;
    }
  }
  data->count_of_vertexes_in_facets += 2 * data->polygons[m].num_vertexes;
  data->polygons[m].polygon_i = (unsigned int *)calloc(
      data->polygons[m].num_vertexes, sizeof(unsigned int));

  int num_of_column = 0;

  for (int i = 2, j = 0; check == 0; i++) {
    if (str[i] == '-') {
      i++;
    }
    if (str[i] >= '0' && str[i] <= '9') {
      number[j] = str[i];
      j++;
    } else if (str[i] == '/') {
      while (str[i + 1] != ' ' && str[i + 1] != '\n' && str[i + 1] != '\0') {
        i++;
      }
    } else {
      number[j] = '\0';
      data->polygons[m].polygon_i[num_of_column] = atoi(number) - 1;
      j = 0;
      num_of_column++;
      if (str[i] == '\n' || str[i] == '\0') {
        check = 1;
      }
      if (str[i] == ' ' && (str[i + 1] == '\n' || str[i + 1] == '\0')) {
        check = 1;
      }
    }
  }
}

// запись массива индексов для функций из OpenGL
void writing_indexes_array(obj_data *data) {
  int n = 0;
  data->indexes_array = (unsigned int *)calloc(
      data->count_of_vertexes_in_facets, sizeof(unsigned int));
  for (unsigned int i = 0; i < data->amount_of_facets; i++) {
    for (int j = 0; j < data->polygons[i].num_vertexes - 1; j++) {
      data->indexes_array[n] = data->polygons[i].polygon_i[j];
      n++;
      data->indexes_array[n] = data->polygons[i].polygon_i[j + 1];
      n++;
    }
    data->indexes_array[n] =
        data->polygons[i].polygon_i[data->polygons[i].num_vertexes - 1];
    n++;
    data->indexes_array[n] = data->polygons[i].polygon_i[0];
    n++;
  }
}

// сдвиг массива вершин в положение, когда объект будет находится по центру
// системы координат в OpenGL нахождение модуля максимального значения среди min
// и max всех трёх осей
void correct_vertexes_array(obj_data *data) {
  double x = (-1) * (data->maxwidth + data->minwidth) / 2;
  double y = (-1) * (data->maxheight + data->minheight) / 2;
  double z = (-1) * (data->maxdepth + data->mindepth) / 2;
  data->max = fabs(x + data->maxwidth);
  double maxy = fabs(y + data->maxheight);
  double maxz = fabs(z + data->maxdepth);
  if (maxy > data->max) {
    data->max = maxy;
  }
  if (maxz > data->max) {
    data->max = maxz;
  }
  int count = 1;
  for (unsigned int i = 0; i < 3 * data->amount_of_vertexes; i++) {
    if (count == 1) {
      data->vertexes_array[i] += x;
      count++;
    } else if (count == 2) {
      data->vertexes_array[i] += y;
      count++;
    } else {
      data->vertexes_array[i] += z;
      count = 1;
    }
  }
}

// отчистка структуры obj_data
void free_obj(obj_data *data) {
  free(data->vertexes_array);
  for (unsigned int i = 0; i < data->amount_of_facets; i++) {
    free(data->polygons[i].polygon_i);
  }
  free(data->polygons);
  free(data->indexes_array);
}
