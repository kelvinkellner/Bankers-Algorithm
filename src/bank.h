/* Imports */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants */
const char *FILE_NAME = "sample4_in.txt";

/* Variables and Structs */

int num_resources;
int num_customers;

typedef struct customer {
    int *max_resources;
    int *allocation_resources;
    int *need_resources;
} Customer;

int *available_resources;
Customer *customer_resources;

/* Function Headers */

void load_available_resources(int argc, char *args[]);
int load_customer_resources();
void run_program();

void display_status();
char *request_resources(int customer_number, int *request);
char *release_resources(int customer_number, int *request);
void run_resources();

bool is_safe();

char *handle_request(char *input, int len, char *(*func)(int, int *));