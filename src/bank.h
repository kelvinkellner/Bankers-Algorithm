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
void request_resource(int customer_number, int *request);
void release_resource();
void run_resource();

bool is_safe();

void handle_request(char *input, int len, void (*func)(int, int *));