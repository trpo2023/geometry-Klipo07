#include </home/demo/geometry-Klipo07/src/libgeometry/lab1.h>

int main()
{
    char enter[MAX], shape[MAX];
    int num = 0;

    printf("Enter the name and coordinates of the shape (or press Enter for "
           "exit):\n");
    fgets(enter, MAX, stdin);

    for (size_t i = 0; i < strlen(enter); i++) {
        if (enter[i] == '(' || enter[i] == ' ') {
            to_lower(shape, num);
            if (strcmp(shape, "circle") == 0) {
                struct Point center = find_center(enter, &num);
                struct Circle circle = find_out_circle(&center, enter, &num);
                empty(enter, &num);
                output_circle_message(&circle);
                break;
            } else {
                output_bugs(BUG_NAME, 0, NULL);
                exit(1);
            }
        } else if (enter[i] == ')') {
            output_bugs(BUG_STAPLES, num, &enter[i]);
            exit(1);
        }

        shape[num] = enter[i];
        num++;
    }

    return 0;
}