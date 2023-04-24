#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/lab1.h>

#include <ctest.h>

CTEST(TEST_output_bugs, outputs_correct_message) {
    char message[] = "This is a test message";
    output_bugs(1, 5, message);
    ASSERT_STR("Error 1 occurred at location 5: This is a test message", message);
}

CTEST(TEST_to_lower, converts_string_to_lowercase) {
    char str[] = "Hello, World!";
    to_lower(str, 13);
    ASSERT_STR("hello, world!", str);
}

CTEST(TEST_x_data, returns_correct_x_coordinate) {
    int num;
    double result = x_data("1.23, 4.56", &num);
    ASSERT_EQUAL(2, num);
    ASSERT_DBL_NEAR_TOL(1.23, result, 1e-4);
}

CTEST(y_data, returns_correct_y_coordinate) {
    int num;
    double result = y_data("1.23, 4.56", &num);
    ASSERT_EQUAL(2, num);
    ASSERT_DBL_NEAR_TOL(4.56, result, 1e-6);
}

CTEST(radius_data, returns_correct_radius) {
    int num;
    double result = radius_data("1.23, 4.56, 7.89", &num);
    ASSERT_EQUAL(3, num);
    ASSERT_DBL_NEAR_TOL(7.89, result, 1e-6);
}

CTEST(empty, empties_string_and_resets_num) {
    char str[] = "This is a test string";
    int num = 5;
    empty(str, &num);
    ASSERT_STR("", str);
    ASSERT_EQUAL(0, num);
}

CTEST(find_center, returns_correct_center_point) {
    int num;
    struct Point result = find_center("1.23, 4.56; 7.89, 0.12; 3.45, 6.78", &num);
    ASSERT_EQUAL(6, num);
    ASSERT_DBL_NEAR_TOL(4.19, result.x, 1e-6);
    ASSERT_DBL_NEAR_TOL(3.82, result.y, 1e-6);
}

CTEST(find_out_circle, returns_correct_circle) {
    int num;
    struct Point center = {1.23, 4.56};
    struct Circle result = find_out_circle(&center, "2.34, 5.67; 3.45, 6.78; 4.56, 7.89", &num);
    ASSERT_EQUAL(6, num);
    ASSERT_DBL_NEAR_TOL(3.184474, result.radius, 1e-6);
    ASSERT_DBL_NEAR_TOL(1.971825, result.center.x, 1e-6);
    ASSERT_DBL_NEAR_TOL(5.392342, result.center.y, 1e-6);
}

CTEST(output_circle_message, outputs_correct_message) {
    struct Circle circle = {{1.23, 4.56}, 7.89};
    char message[100];
    output_circle_message(&circle);
    ASSERT_STR("Circle with center (1.23, 4.56) and radius 7.89", message);
}