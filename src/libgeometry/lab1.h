#pragma once
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED_FLASH "\e[5;31m"
#define END "\e[0m"
#define MAX 100

struct Point {
    double x;
    double y;
};

struct Circle {
    struct Point center;
    double radius;
};

enum Bugs {
    BUG_NAME,
    BUG_STAPLES,
    BUG_NUMBER,
    BUG_UNIDENTIFIED_VARIABLES,
    BUG_EXPECT_COMMA,
    BUG_STAPLES_2,
    BUG_EXTRA_POINT,
};

void output_bugs(int errors, int num, char* ch);
void to_lower(char* str, int ch);
double x_data(char* arr, int* num);
double y_data(char* arr, int* num);
double radius_data(char* arr, int* num);
void empty(char* arr, int* num);
struct Point find_center(char* arr, int* num);
struct Circle find_out_circle(struct Point* Center, char* arr, int* num);
void output_circle_message(struct Circle* circle);
