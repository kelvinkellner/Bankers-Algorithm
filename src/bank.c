#include "bank.h"

/**
 * Main program driver.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 * 
 */
int main(int argc, int *args[]) {
    if (argc < 3) {
        printf("Please include at least 2 space-delimited integer arguments.\n");
        return 1;
    }

    load_available_resources(argc, args);
    load_customer_resources();

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
    char *input = NULL;
    size_t len = 0;
    ssize_t strlen = 0;

    int running = true;

    while (running) {
        strlen = getline(&input, &len, stdin);
        if (strlen == -1)
            // exit on error
            running = false;
        else {
            printf(input);
            if (input == "RQ") {
                //TODO: Function Call
                printf("State is safe, and request is satisfied");
            } else if (input == "RL") {
                //TODO: Function Call
                printf("The resources have been released succesfully");
            } else if (input == "Status") {
            } else if (input == "Run") {
            } else if (input == "Exit") {
            } else {
                printf("Invalid Command, Please Try Again!");
            }
        }
    }

    free(input);
}

/**
 * Loads available resources from parameters.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 * 
 */
void load_available_resources(int argc, int *args[]) {
    available_resources = (int *)malloc((argc - 1) * sizeof(int));
    for (int i = 0; i < argc - 1; i++) {
        available_resources[i] = atoi(args[i + 1]);
    }
}

/**
 * Loads customer resource data from the file.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 * 
 */
void load_customer_resources() {
}