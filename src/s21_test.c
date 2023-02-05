#include "obj_parcer.h"
#include <check.h>

START_TEST(test_parser_with_file) {
  char filename[100] = "obj_files/cube.obj";
  obj_data objdata;
  int error = obj_parcer(filename, &objdata);
  free_obj(&objdata);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_parser_without_file) {
  char filename[100] = "obj_files/no_file.obj";
  obj_data objdata;
  int error = obj_parcer(filename, &objdata);
  if (error == 0) {
    free_obj(&objdata);
  }
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_amount_of_vertexes_and_facets) {
  char filename[100] = "obj_files/guitar.obj";
  obj_data objdata;
  int error = obj_parcer(filename, &objdata);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq((int)objdata.amount_of_vertexes, 37662);
  ck_assert_int_eq((int)objdata.amount_of_facets, 37441);
  free_obj(&objdata);
}
END_TEST

int main() {
  Suite *suite = suite_create("S21_TESTS");
  SRunner *srunner = srunner_create(suite);

  TCase *s21_3dviewer_1_case = tcase_create("3dviewer_1");
  suite_add_tcase(suite, s21_3dviewer_1_case);
  tcase_add_test(s21_3dviewer_1_case, test_parser_with_file);

  TCase *s21_3dviewer_2_case = tcase_create("3dviewer_2");
  suite_add_tcase(suite, s21_3dviewer_2_case);
  tcase_add_test(s21_3dviewer_2_case, test_parser_without_file);

  TCase *amount_case = tcase_create("amount_test");
  suite_add_tcase(suite, amount_case);
  tcase_add_test(amount_case, test_amount_of_vertexes_and_facets);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return (number_failed == 0) ? 0 : 1;
}