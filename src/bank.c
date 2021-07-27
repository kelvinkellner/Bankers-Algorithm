#include "bank.h"

#include <stdio.h>

/**
 * Main program driver.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 * 
 */
int main(int argc, int *args[]) {
    if (argc <= 2) {
        printf("Please include at least 2 space-delimited integer arguments.\n");
        return 1;
    }

    load_available_resources(argc, args);
    load_customer_resources(FILE_NAME);

    run_program();

    return 0;
}

/**
 * Program event loop.
 * Loops until the user types 'exit'
 * Allows user to interact with the program.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 * 
 */
void run_program() {
}

/**
 * Loads available resources from parameters.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 * 
 */
void load_available_resources(int n, int *args[]) {
}

/**
 * Loads customer resource data from the file.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 * 
 */
void load_customer_resources(char *file_name) {
}