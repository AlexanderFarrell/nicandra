#include "nicandra_test.h"
#include <stddef.h>
#include "printf.h"
#include <string.h>

#define C_TEST_RESET     "\x1B[0m"
#define C_TEST_BLACK     "\x1B[30m"
#define C_TEST_RED       "\x1B[31m"
#define C_TEST_GREEN     "\x1B[32m"
#define C_TEST_YELLOW    "\x1B[33m"
#define C_TEST_BLUE      "\x1B[34m"
#define C_TEST_MAGENTA   "\x1B[35m"
#define C_TEST_CYAN      "\x1B[36m"
#define C_TEST_WHITE     "\x1B[37m"

static int tests_passed = 0;
static int tests_run = 0;
// static const char* current_suite = "Default Suite";
// static int suite_tests_passed = 0;
// static int suite_tests_run = 0;

// void nc_test_start() {

// }

// void nc_test_suite_set(const char * suite_name) {
//     // current_suite = suite_name
// }

void nc_test_assert_eq_str(const char * test_name, const char * a, const char * b) {
    tests_run++;
    if (strcmp(a, b) == 0) {
        tests_passed++;
        printf("%s[PASS]%s - %s\n", C_TEST_GREEN, C_TEST_RESET, test_name);
    } else {
        printf("%s[FAIL]%s - %s \t\nLeft: \"%s\" \t\nRight: \"%s\"\n", C_TEST_RED, C_TEST_RESET, test_name, a, b);
    }
}

void nc_test_assert_eq_int(const char * test_name, int a, int b) {
    tests_run++;
    if (a == b) {
        tests_passed++;
        printf("%s[PASS]%s - %s\n", C_TEST_GREEN, C_TEST_RESET, test_name);
    } else {
        printf("%s[FAIL]%s - %s \t\nLeft: \"%d\" \t\nRight: \"%d\"\n", C_TEST_RED, C_TEST_RESET, test_name, a, b);
    }
}

int nc_test_stop() {
    if (tests_passed == tests_run) {
        printf("%s[PASS]%s -%s %d %s", C_TEST_GREEN, C_TEST_RESET, C_TEST_GREEN, tests_passed, C_TEST_RESET);
    } else {
        printf("%s[FAIL]%s -%s %d %s", C_TEST_RED, C_TEST_RESET, C_TEST_RED, tests_passed, C_TEST_RESET);
    }

    printf("/ %d Tests Passed of Tests Run\n\n", tests_run);

    if (tests_passed == tests_run) {
        return 0;
    } else {
        return 1;
    }
}