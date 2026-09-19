#ifndef NICANDRA_TEST_LIB_H
#define NICANDRA_TEST_LIB_H

// void nc_test_start();
// void nc_test_suite_set(const char * suite_name);
void nc_test_assert_eq_str(const char * test_name, const char * a, const char * b);
void nc_test_assert_eq_int(const char * test_name, int a, int b);
int nc_test_stop();

#endif