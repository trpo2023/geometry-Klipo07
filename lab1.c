#include <ctype.h>
#include <stdio.h>
#include <string.h>
int Figur(char* str)
{
    int flag = 1;
    char data[40];
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '(') {
            data[i] = tolower(str[i]);
            str[i] = tolower(str[i]);
        } else
            break;
    }
    char figure[] = "circle";
    if (strcmp(data, figure) == 0) {
        flag = 0;
    }
    return flag;
}

int first(char* str)
{
    int flag = 1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '(')
            continue;
        else {
            flag = 0;
            break;
        }
    }
    return flag;
}

int Arg(char* str)
{
    int flag = 1;
    int data;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            data = i;
            break;
        }
    }
    for (int i = data + 1; i < strlen(str) - 2; i++) {
        if ((str[i] >= 48 && str[i] <= 57) || str[i] == '.' || str[i] == ','
            || str[i] == ' ')
            flag = 0;
        else {
            flag = 1;
            break;
        }
    }
    for (int i = data + 1; i < strlen(str) - 1; i++) {
        if (str[i] == '.' && ((str[i + 1] < 48 || str[i + 1] > 57)
            || (str[i - 1] < 48 || str[i - 1] > 57)))
            flag = 1;
        else if (
                str[i] == ',' && (str[i + 1] != ' ')
                && (str[i - 1] < 48 && str[i - 1] > 57))
            flag = 1;
    }
    return flag;
}

int num(char* str){
    int flag=1;
    int data;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            data = i;
            break;
        }
    }
    int cnt=0;
    for (int i = data + 1; i < strlen(str) - 2; i++) {
	if(str[i] >= 48 && str[i] <= 57)
	    cnt++;
	else if(str[i]=='.')
	    cnt--;
	if(cnt>3)
	    flag=1;
	else
	    flag=0;
    }
    return flag;
}

int Simval(char* str)
{
    int flag = 1;
    int data;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '(') {
            data = i;
            break;
        }
    }
    for (int i = data + 1; i < strlen(str) - 2; i++) {
        if (str[i] == ',') {
            flag = 0;
        } else {
            continue;
        }
    }
    return flag;
}

int End(char* str)
{
    int flag = 1;
    int bracket = 0;
    long int ending = strlen(str) - 2;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ')') {
            bracket = i;
            break;
        }
    }
    if (bracket == ending || bracket == ending + 1)
        flag = 0;
    return flag;
}

int main()
{
    FILE* file;
    file = fopen("lab1.txt", "r");
    char str[40];
    int cnt = 1;
    fgets(str, 40, file);
    if (Figur(str)) {
        printf("Неправильное название фигуры в %d строке\n", cnt);
        if (first(str))
            printf("Конкретная ошибка:Ошибка открывающей скобки\n");
    } else if (Arg(str))
        printf("Неправильно введены координаты в %d строке\n", cnt);
    else if(num(str))
	printf("Слишком много переданных аргументов в %d строке \n",cnt);
    else if (Simval(str))
        printf("Неправильная постановка запятой в %d строке\n", cnt);
    else if (End(str))
        printf("Ошибка завершающей скобки в %d строке\n", cnt);
    else
        printf("%s\n", str);
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\n' && fgets(str, 40, file) != NULL) {
            cnt++;
            if (Figur(str)) {
                printf("Неправильное название фигуры во %d строке\n", cnt);
                if (first(str))
                    printf("Конкретная ошибка:Ошибка открывающей скобки\n");
            } else if (Arg(str))
                printf("Неправильно введены координаты во %d строке\n", cnt);
            else if(num(str))
	        printf("Слишком много переданных аргументов во %d строке \n",cnt);
	    else if (Simval(str))
                printf("Неправильная постановка запятой во %d строке\n", cnt);
            else if (End(str))
                printf("Ошибка завершающей скобки во %d строке\n", cnt);
            else
                printf("%s\n", str);
            i = 0;
        }
    }
    fclose(file);
    return 0;
}