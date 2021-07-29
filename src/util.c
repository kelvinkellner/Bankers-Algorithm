#include <string.h>

/**
 * Takes a string, delimeter, and length of array and creates and
 * fills an array with integer conversions of the contents of the
 * string split by the delimeter.
 *
 * @author Kelvin Kellner
 */
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

/**
 * Prints an integer array with good spacing.
 * Pass the array and the length of the array.
 * 
 * @author Kelvin Kellner
 */
void print_array(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i == len - 1)
            printf("\n");
        else
            printf(" ");
    }
}