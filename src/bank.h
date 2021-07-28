/* Imports */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */
const char *FILE_NAME = "sample4_in.txt";

/* Variables and Structs */

int num_resources;
int num_customers;

typedef struct customer {
    int *maximum_resources;
    int *allocation_resources;
    int *need_resources;
} Customer;

int *available_resources;
Customer *customer_resources;

typedef struct request {
    int customer_number;
    int *allocation;
} Request;

/* Function Headers */
void load_available_resources(int argc, char *args[]);
int load_customer_resources();
void run_program();

void display_status();
void request_resource();
void release_resource();
void run_resource();