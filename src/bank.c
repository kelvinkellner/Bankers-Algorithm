/**
 * Banker's Algoritm
 * CP 386 --> Assignment 4
 * 
 * @author Kelvin Kellner (190668940) - https://github.com/kelvinkellner
 * @author Nishant Tewari (190684430) - https://github.com/XSilviaX
 * 
 * @see https://github.com/kelvinkellner/Bankers-Algorithm
 */

#include "bank.h"

#include "util.c"

/**
 * Main program driver.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
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
            // convert input to lowercase
            char *cptr = input;
            for (; *cptr; ++cptr) {
                // remove line breaks
                if (*cptr == '\n')
                    *cptr = '\0';
                else
                    // call tolower on each character
                    *cptr = tolower(*cptr);
            }

            // call appropriate function per command
            if (input == "RQ") {
                //TODO: Function Call
                printf("State is safe, and request is satisfied");
            } else if (input == "RL") {
                //TODO: Function Call
                printf("The resources have been released succesfully");
            } else if (strcmp(input, "status") == 0) {
                display_status();
            } else if (strcmp(input, "run") == 0) {
                // TODO: not correct function call for run
                printf("%s", is_safe() ? "Safe: YES\n" : "Safe: NO\n");
            } else if (strcmp(input, "exit") == 0) {
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
 */
int load_customer_resources() {
    FILE *fp;
    char *line;
    size_t len = 0;
    ssize_t strlen;

    if ((fp = fopen(FILE_NAME, "r")) == NULL) {
        printf("File opening error.");
        return -1;
    }

    num_customers = 1;  // start at one since last line does not have line break
    char ch;
    // count number of lines in the file
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            num_customers++;
    }
    fseek(fp, 0, SEEK_SET);  // reset fp back to start

    customer_resources = malloc(num_customers * sizeof(Customer));

    int r, c = 0;
    while ((strlen = getline(&line, &len, fp)) != -1) {
        Customer customer;
        customer.maximum_resources = delimited_string_to_int_array(line, ",", num_resources);
        customer.allocation_resources = malloc(sizeof(int) * num_resources);
        customer.need_resources = malloc(sizeof(int) * num_resources);
        // ensure no memory-related value issues occur
        for (r = 0; r < num_resources; r++)
            customer.allocation_resources[r] = 0;
        for (r = 0; r < num_resources; r++)
            customer.need_resources[r] = 0;
        customer_resources[c] = customer;
        c++;
    }

    free(line);
    fclose(fp);
}

/**
 * Prints arrays of all available and customer resources
 *  
 * @author Kelvin Kellner 
 * @author Nish Tewari
 */
void display_status() {
    int c;
    printf("Available Resources:\n");
    print_array(available_resources, num_resources);

    printf("Maximum Resources:\n");
    for (c = 0; c < num_customers; c++)
        print_array(customer_resources[c].maximum_resources, num_resources);

    printf("Allocated Resources:\n");
    for (c = 0; c < num_customers; c++)
        print_array(customer_resources[c].allocation_resources, num_resources);

    printf("Need Resources:\n");
    for (c = 0; c < num_customers; c++)
        print_array(customer_resources[c].need_resources, num_resources);
}

/**
 * def'n 
 *  
 * @author Kelvin Kellner 
 * @author Nish Tewari
 */
void request_resource(int *request) {
}

/**
 * def'n 
 *  
 * @author Kelvin Kellner 
 * @author Nish Tewari
 */
void release_resource() {
}

/**
 * def'n 
 *  
 * @author Kelvin Kellner 
 * @author Nish Tewari
 */
void run_resource() {
}

/**
 * Uses Saftey Algorithm to determine whether or not
 * system is in a safe state.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 */
bool is_safe() {
    // use safety algorithm from lecture
    int *work = (int *)malloc(num_resources * sizeof(int));
    bool *finish = (bool *)malloc(num_customers * sizeof(bool));
    int r, c;
    // fill with default values
    for (r = 0; r < num_resources; r++)
        work[r] = available_resources[r];
    for (c = 0; c < num_customers; c++)
        finish[c] = false;
    // default values for looping
    bool safe, found_customer;
    do {
        safe = true;
        found_customer = false;
        // attempt to find a customer to finish
        for (c = 0; c < num_customers && !found_customer; c++) {
            if (finish[c] == false) {  // condition 1:  customer is not finished
                found_customer = true;
                // condition 2: customer need vector < work vector
                for (r = 0; r < num_resources && found_customer; r++)
                    found_customer = customer_resources[c].need_resources[r] <= work[r];
                // if both conditions are met...
                if (found_customer) {
                    // update work and finish vectors to reflect changes
                    for (int j = 0; j < num_resources; j++)
                        work[r] += customer_resources[c].allocation_resources[r];
                    finish[c] = true;
                }
            }
            safe = safe && finish[c];  // system is safe if all customers have finished
        }
    } while (found_customer && !safe);  // loop until (state is safe) or (state is unsafe and no changes are made to system)
    // no memory leaks please :)
    free(work);
    free(finish);
    return safe;
}