
/* Imports */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */
const char *FILE_NAME = "sample4_in.txt";

/* Variables and Structs */

typedef struct customer {
    int *maximum;
    int *allocated;
    int *need;
} Customer;

int *available_resources;
Customer *customer_resources;

/* Function Headers */
void load_available_resources(int argc, char *args[]);
int load_customer_resources(int count_resources);
void run_program();