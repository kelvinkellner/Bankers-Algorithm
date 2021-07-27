#include "bank.h"

#include "util.c"

/**
 * Main program driver.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 * 
 */
int main(int argc, char *args[]) {
    if (argc < 3) {
        printf("Please include at least 2 space-delimited integer arguments.\n");
        return 1;
    }

    load_available_resources(argc, args);
    load_customer_resources();

    // printf("%d %d\n", num_customers, num_resources);

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
        printf("Enter Command: ");
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
                printf("Exiting...\n");
                running = false;
            } else {
                printf("Invalid Command.\nPlease Try Again!\n");
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
void load_available_resources(int argc, char *args[]) {
    num_resources = argc - 1;
    available_resources = (int *)malloc((num_resources) * sizeof(int));  // allocate memory for arry
    for (int i = 0; i < num_resources; i++) {
        available_resources[i] = atoi(args[i + 1]);  // fill array using args
    }
}

/**
 * Loads customer resource data from the file.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 * 
 */
int load_customer_resources() {
    FILE *fp;
    char *line;
    size_t len = 0;
    ssize_t strlen;

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("File opening error.");
        return -1;
    }

    num_customers = 0;
    // count number of lines in the file
    while (fgets(line, sizeof(line), fp))
        num_customers++;
    fseek(fp, 0, SEEK_SET);  // reset fp back to start

    return 0;

    customer_resources = malloc(num_customers * sizeof(Customer));

    int i = 0;
    while ((strlen = getline(&line, &len, fp)) != -1) {
        Customer c;
        c.maximum = delimited_string_to_int_array(line, ",", num_resources);
        c.allocated = malloc(sizeof(int) * num_resources);
        c.need = malloc(sizeof(int) * num_resources);

        customer_resources[i] = c;
        i++;
    }

    free(line);
    fclose(fp);
}