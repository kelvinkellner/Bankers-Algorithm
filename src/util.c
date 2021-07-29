#include <string.h>

int* delimited_string_to_int_array(char* msg, char* delimeter, int len) {
    int* arr = (int*)malloc(len * sizeof(int));

    int count = 0;
    char* token;
    while ((token = strsep(&msg, delimeter)) != NULL) {
        if (token != "") {
            arr[count] = atoi(token);
            count++;
        }
    }
    return arr;
}

void print_array(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i == len - 1)
            printf("\n");
        else
            printf(" ");
    }
}