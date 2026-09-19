#include <nicandra.h>
#include <nicandra_test.h>

int main() {
    nc_test_assert_eq_int("Passing Test", 1, 1);
    nc_test_assert_eq_int("Failing Test", 1, 1);
    return nc_test_stop();
}