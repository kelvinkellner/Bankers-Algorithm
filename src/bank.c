/**
 * 
 * Banker's Algoritm
 * CP 386 --> Assignment 4
 * 
 * @author Kelvin Kellner (190668940) - https://github.com/kelvinkellner
 * @author Nishant Tewari (190684430) - https://github.com/XSilviaX
 * 
 * @see https://github.com/kelvinkellner/Bankers-Algorithm
 * 
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
    // confirm arguments are valid
    if (argc < 3) {
        printf("Please include at least 2 space-delimited integer arguments.\n");
        return 1;
    }

    // load data from arguments and file
    load_available_resources(argc, args);
    load_customer_resources();

    // start event loop
    run_program();

    // exuent
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
    // for reading from console
    char *input = NULL;
    size_t len = 0;
    ssize_t read = 0;

    // loop until told to stop (from "exit" command)
    int running = true;
    while (running) {
        printf("Enter Command: ");
        read = getline(&input, &len, stdin);  // read line from console
        if (read == -1)
            // exit on error
            running = false;
        else {
            // convert input to lowercase
            char *ch_ptr = input;
            for (; *ch_ptr; ++ch_ptr) {
                // remove line breaks
                if (*ch_ptr == '\n')
                    *ch_ptr = '\0';
                else
                    // call tolower on each character
                    *ch_ptr = tolower(*ch_ptr);
            }

            // call appropriate function per command and print messages as needed
            // "RQ ..."
            if (strlen(input) >= 2 && input[0] == 'r' && input[1] == 'q')
                printf("%s", handle_request(input, len, request_resources));
            // "RL ..."
            else if (strlen(input) >= 2 && input[0] == 'r' && input[1] == 'l')
                printf("%s", handle_request(input, len, release_resources));
            // "Status"
            else if (strcmp(input, "status") == 0)
                display_status();
            // "Run"
            else if (strcmp(input, "run") == 0)
                run_resources();
            // "Exit"
            else if (strcmp(input, "exit") == 0) {
                printf("Exiting...\n");
                running = false;
            }
            // otherwise...
            else
                printf("Invalid Command\n");
        }
    }
    free(input);  // no memory leaks :)
}

/**
 * Loads available resources from program arguments.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 */
void load_available_resources(int argc, char *args[]) {
    num_resources = argc - 1;                                            // first arg is always program call
    available_resources = (int *)malloc((num_resources) * sizeof(int));  // allocate memory for array
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
    // for reading from file
    FILE *fp;
    char *line;
    size_t len = 0;
    ssize_t read;

    // attempt to open from file
    if ((fp = fopen(FILE_NAME, "r")) == NULL) {
        // quit if there is an error
        printf("File opening error.");
        return -1;
    }

    num_customers = 1;  // start at one since last line does not have line break
    // count number of lines in the file
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            num_customers++;
            // if line was actually empty then don't count it
            if ((ch = fgetc(fp)) == EOF)
                num_customers--;
        }
    }
    fseek(fp, 0, SEEK_SET);  // reset fp back to start after counting

    // allocate memory for customer_resources data structure
    customer_resources = malloc(num_customers * sizeof(Customer));

    // read customer data from file
    int r, c = 0;
    while ((read = getline(&line, &len, fp)) != -1) {  // for each line in file
        // ignore blank lines
        if (strlen(line) > 1) {
            // create customer data structure and fill with data
            Customer customer;
            customer.max_resources = delimited_string_to_int_array(line, ",", num_resources);
            customer.allocation_resources = malloc(sizeof(int) * num_resources);
            customer.need_resources = malloc(sizeof(int) * num_resources);
            // ensure no memory-related value issues occur by setting values to 0 (frick C)
            for (r = 0; r < num_resources; r++)
                customer.allocation_resources[r] = 0;
            // need = max - allocation, allocation is all 0s now, so set to need = max to start
            for (r = 0; r < num_resources; r++)
                customer.need_resources[r] = customer.max_resources[r];
            customer_resources[c] = customer;
            c++;
        }
    }
    // no memory leaks please :)
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
    // print status for all data structures
    int c;
    printf("Available Resources:\n");
    print_array(available_resources, num_resources);

    printf("Maximum Resources:\n");
    for (c = 0; c < num_customers; c++)
        print_array(customer_resources[c].max_resources, num_resources);

    printf("Allocated Resources:\n");
    for (c = 0; c < num_customers; c++)
        print_array(customer_resources[c].allocation_resources, num_resources);

    printf("Need Resources:\n");
    for (c = 0; c < num_customers; c++)
        print_array(customer_resources[c].need_resources, num_resources);
}

/**
 * Processes a request for resources from the bank.
 * Determines whether request is possible and safe, fulfilling the request-
 * or notifies the customer to either wait or make a different request.
 *  
 * @author Kelvin Kellner 
 * @author Nish Tewari
 */
char *request_resources(int customer_number, int *request) {
    // uses resource-request algorithm from lecture notes
    int r, c = customer_number;
    bool valid = true, safe;

    // check if request is all 0s
    valid = false;
    for (r = 0; r < num_resources; r++) {
        if (request[r] != 0)
            valid = true;
    }

    if (valid) {
        // condition 1: request vector <= customer's need vector, request has exceeding it's maximum claim
        for (r = 0; r < num_resources && valid; r++)
            valid = request[r] <= customer_resources[c].need_resources[r];

        if (valid) {
            // condition 2: request vector <= available vector, customer must wait til resources are available
            for (r = 0; r < num_resources && valid; r++)
                valid = request[r] <= available_resources[r];
            if (valid) {
                // temporarily modify values to determine if safe
                for (r = 0; r < num_resources; r++) {
                    available_resources[r] -= request[r];
                    customer_resources[c].allocation_resources[r] += request[r];
                    customer_resources[c].need_resources[r] -= request[r];
                }
                if (is_safe(NULL)) {
                    // if system is safe after fulfilling the resource request, print success message
                    return "State is safe, and request is satisfied\n";
                } else {
                    // if system becomes unsafe, undo temporary changes to value and print failure message
                    for (r = 0; r < num_resources; r++) {
                        available_resources[r] += request[r];
                        customer_resources[c].allocation_resources[r] -= request[r];
                        customer_resources[c].need_resources[r] += request[r];
                    }
                    return "State is unsafe, not enough resources available for that request\n";
                }
            } else {
                return "Not enough resources available, please wait\n";
            }
        } else {
            return "Request exceeds maximum resource claim, cannot be satisfied\n";
        }
    } else {
        return "Requesting zero resources is illogical\n";
    }
}

/**
 * Releases resources from a customer and makes them available again.
 *  
 * @author Kelvin Kellner 
 * @author Nish Tewari
 */
char *release_resources(int customer_number, int *request) {
    int r, c = customer_number;
    // optional extra validation in case someone really tries to breaky-breaky :eyes:
    bool valid = true;
    // check if release vector > allocation vector, otherwise a release request might "create new resources"
    for (r = 0; r < num_resources; r++) {
        // not exhaustive, we do not check if this customer is the one holding the resources, not important
        if (request[r] > customer_resources[c].allocation_resources[r])
            valid = false;
    }
    if (valid) {
        valid = false;
        // check if request is all 0s
        for (r = 0; r < num_resources; r++) {
            if (request[r] != 0)
                valid = true;
        }
        if (valid) {
            // release those resources!
            for (r = 0; r < num_resources; r++) {
                // simply make the resources available again
                available_resources[r] += request[r];
            }
            return "Resources have been released\n";
        } else {
            return "Releasing zero resources is illogical\n";
        }
    } else {
        return "Cannot release resources that are not in use\n";
    }
}

/**
 * Executes customers as threads in a safe sequence.
 *  
 * @author Kelvin Kellner 
 * @author Nish Tewari
 */
void run_resources() {
    // check if a safe sequence exists and store the sequence in sequence
    int c, position;
    int *sequence = (int *)malloc(num_customers * sizeof(int));
    bool safe_sequence_exists = is_safe(&sequence);
    // once we have a safe sequence, we can run it
    if (safe_sequence_exists) {
        printf("Safe sequence is: ");
        print_array(sequence, num_customers);
        for (position = 0; position < num_customers; position++) {
            // display status before running thread
            c = sequence[position];  // current customer
            printf("--> Customer/Thread %d\n", c);
            printf("    Allocated resources: ");
            print_array(customer_resources[c].allocation_resources, num_resources);
            printf("    Needed: ");
            print_array(customer_resources[c].need_resources, num_resources);
            printf("    Available: ");
            print_array(available_resources, num_resources);
            // run thread by requesting all needed resources
            printf("    Thread has started\n");
            request_resources(c, customer_resources[c].need_resources);
            printf("    Thread has finished\n");
            // release resources
            printf("    Thread is releasing resources\n");
            release_resources(c, customer_resources[c].allocation_resources);
            // display new status
            printf("    New available: ");
            print_array(available_resources, num_resources);
        }
    } else
        printf("Safe sequence is: There is no safe sequence\n");
}

/**
 * Uses Saftey Algorithm to determine whether or not system is in a safe state.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 */
bool is_safe(int *sequence[]) {
    // use safety algorithm from lecture
    int *work = (int *)malloc(num_resources * sizeof(int));
    bool *finish = (bool *)malloc(num_customers * sizeof(bool));
    int r, c, i, count = 0;
    // fill vectors with starting values
    for (r = 0; r < num_resources; r++)
        work[r] = available_resources[r];
    for (c = 0; c < num_customers; c++)
        finish[c] = false;

    // loop until either (state is safe) or (state is unsafe and no changes are made to system)
    bool safe, customer_must_wait;
    for (i = 0; i < num_customers; i++) {
        safe = true;
        // attempt to find a customer to finish
        for (c = 0; c < num_customers; c++) {
            if (finish[c] == false) {  // condition 1:  customer is not finished
                customer_must_wait = false;
                // condition 2: customer need vector must be <= work vector
                for (r = 0; r < num_resources && !customer_must_wait; r++) {
                    if (customer_resources[c].need_resources[r] > work[r])
                        customer_must_wait = true;
                }
                // if both conditions are met...
                if (!customer_must_wait) {
                    // put the customer number in sequence and move to next number
                    if (sequence)
                        (*sequence)[count++] = c;
                    // update work and finish vectors to reflect changes
                    for (int r = 0; r < num_resources; r++)
                        work[r] += customer_resources[c].allocation_resources[r];
                    finish[c] = true;
                }
            }
        }
        // check if all customers are finished
        for (c = 0; c < num_customers; c++)
            safe = safe && finish[c];  // system is safe if all customers have finished
    }
    // free from memory and make null if there is no safe sequence
    if (!safe) {
        if (sequence) {
            free(*sequence);
            *sequence = NULL;
        }
    }
    // no memory leaks please :)
    free(work);
    free(finish);
    return safe;
}

/**
 * Help function for RQ and RL commands to process and validate command calls.
 * 
 * @author Kelvin Kellner
 * @author Nish Tewari
 */
char *handle_request(char *input, int len, char *(*func)(int, int *)) {
    int customer_number = -1;
    int *request = (int *)malloc(len * sizeof(int));
    int i, n, count = 0;
    // valid is not needed anymore, since changing from a void* to char* function, still leaving it because it does no harm :)
    bool is_number = true, valid = true;

    // begin processing given command in string input, token stores next value of input split by space as a delimeter
    char *token = strsep(&input, " ");  // skip "RQ" or "RL"
    while ((token = strsep(&input, " ")) != NULL && valid) {
        // check if token is numeric first, only valid entries please!
        n = strlen(token);
        for (i = 0; i < n && is_number; i++)  // if all characters in token are numeric
            is_number = token[i] >= '0' && token[i] <= '9';
        if (is_number) {
            // use the number as customer_number if it is the first number we find
            if (customer_number == -1) {
                if (atoi(token) >= 0)
                    if (atoi(token) < num_customers)
                        // use as customer_number
                        customer_number = atoi(token);
                    else {
                        valid = false;
                        free(request);  // no memory leaks :)
                        return "Bad command, customer number too big\n";
                    }
                else {
                    valid = false;
                    free(request);  // no memory leaks :)
                    return "Bad command, negative values are not acceptable\n";
                }

            } else {
                // all following numbers are used as resource amounts
                if (count < num_resources) {
                    if (atoi(token) >= 0) {  // if positive
                        // store number in the request array
                        request[count] = atoi(token);
                        count++;  // increment count
                    } else {
                        valid = false;
                        free(request);  // no memory leaks :)
                        return "Bad command, negative values are not acceptable\n";
                    }
                } else {
                    valid = false;
                    free(request);  // no memory leaks :)
                    return "Bad command, more arguments given than needed\n";
                }
            }
        } else {
            valid = false;
            free(request);  // no memory leaks :)
            return "Bad command, non-numeric argument given\n";
        }
    }
    if (valid) {
        // if all numbers are processed and the amount of numbers given = num_resources
        if (count == num_resources) {
            // the request is valid!!! go ahead and call the appropriate function and return its return value :)
            char *msg = func(customer_number, request);
            free(request);  // no memory leaks :)
            return msg;
        } else {
            valid = false;
            free(request);  // no memory leaks :)
            return "Bad command, not enough arguments given\n";
        }
    }
}