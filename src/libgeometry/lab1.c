#include <libgeometry/lab1.h>

void output_bugs(int errors, int num, char* ch)
{
    for (int i = 0; i < num; i++) {
        putchar(' ');
    }
    printf("^\n");

    switch (errors) {
    case BUG_NAME:
        printf("An error %d was found in the input line %s'Circle'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_STAPLES:
        if (*ch == ')') {
            printf("An error %d was found in the input line %s')'%s\n",
                   num,
                   RED_FLASH,
                   END);
            break;
        } else {
            printf("An error %d was found in the input line %s'('%s\n",
                   num,
                   RED_FLASH,
                   END);
            break;
        }
    case BUG_STAPLES_2:
        printf("An error %d was found in the input line %s')'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_NUMBER:
        printf("An error %d was found in the input line %s'double'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_UNIDENTIFIED_VARIABLES:
        printf("An error %d was found in the input line %s'variable'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_EXPECT_COMMA:
        printf("An error %d was found in the input line %s','%s\n",
               num,
               RED_FLASH,
               END);
        break;
    case BUG_EXTRA_POINT:
        printf("An error %d was found in the input line %s'.'%s\n",
               num,
               RED_FLASH,
               END);
        break;
    }
}

void to_lower(char* str, int ch)
{
    for (int i = 0; i < ch; i++) {
        str[i] = tolower(str[i]);
    }
}

double x_data(char* arr, int* num)
{
    char free_space[20];
    int i = 0;

    while (!isdigit(arr[*num]) && arr[*num] != '-') {
        if (arr[*num] == '(') {
            *num += 1;
        } else {
            if (arr[*num] == ')') {
                output_bugs(BUG_STAPLES, *num, &arr[*num]);
                exit(1);
            }
            if (arr[*num] == ' ') {
                output_bugs(BUG_STAPLES, *num, &arr[*num]);
                exit(1);
            } else {
                output_bugs(BUG_NUMBER, *num, NULL);
                exit(1);
            }
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '-' || arr[*num] == '.') {
        free_space[i] = arr[*num];
        i++;
        *num += 1;
    }

    if (arr[*num] != ' ') {
        output_bugs(BUG_UNIDENTIFIED_VARIABLES, *num, NULL);
        exit(1);
    }
    char* dumpster;
    return strtod(free_space, &dumpster);
}

double y_data(char* arr, int* num)
{
    char free_space[20];
    int i = 0;

    while (!isdigit(arr[*num]) && arr[*num] != '-') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            output_bugs(BUG_NUMBER, *num, NULL);
            exit(1);
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '-' || arr[*num] == '.') {
        free_space[i] = arr[*num];
        i++;
        *num += 1;
    }

    while (arr[*num] != ',') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            output_bugs(BUG_EXPECT_COMMA, *num, NULL);
            exit(1);
        }
    }
    char* dumpster;
    return strtod(free_space, &dumpster);
}

double radius_data(char* arr, int* num)
{
    char free_space[20];
    int i = 0;
    int extra_point_count = 0;

    while (!isdigit(arr[*num])) {
        if (arr[*num] == ' ' || arr[*num] == ',') {
            *num += 1;
        } else {
            output_bugs(BUG_NUMBER, *num, NULL);
            exit(1);
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '.') {
        free_space[i] = arr[*num];
        i++;
        *num += 1;
        if (arr[*num] == '.') {
            extra_point_count += 1;
        }
        if (extra_point_count >= 2) {
            output_bugs(BUG_EXTRA_POINT, *num, &arr[*num]);
            exit(1);
        }
    }

    while (arr[*num] != ')') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            if (arr[*num] == '(') {
                output_bugs(BUG_STAPLES, *num, &arr[*num]);
                exit(1);
            } else {
                output_bugs(BUG_STAPLES_2, *num, &arr[*num]);
                exit(1);
            }
        }
    }
    char* dumpster;
    return strtod(free_space, &dumpster);
}

void empty(char* arr, int* num)
{
    *num += 1;
    while (arr[*num] != '\n' && arr[*num] != EOF) {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            output_bugs(BUG_UNIDENTIFIED_VARIABLES, *num, NULL);
            exit(1);
        }
    }
}

struct Point find_center(char* arr, int* num)
{
    struct Point Center;

    Center.x = x_data(arr, num);
    Center.y = y_data(arr, num);

    return Center;
}

struct Circle find_out_circle(struct Point* Center, char* arr, int* num)
{
    struct Circle circle;

    circle.center.x = Center->x;
    circle.center.y = Center->y;
    circle.radius = radius_data(arr, num);

    return circle;
}

void output_circle_message(struct Circle* circle)
{
    printf("\ncircle(%.2f %.2f, %.2f)\n",
           circle->center.x,
           circle->center.y,
           circle->radius);
    printf("perimeter: %.4f\n", (2 * M_PI * circle->radius));
    printf("area: %.4f\n", ((circle->radius * circle->radius) * M_PI));
}
