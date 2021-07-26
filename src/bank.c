#include "bank.h"

#include <stdio.h>

int main(int argc, int *args[]) {
    if (argc == 1) {
        printf("Please include arguments to use the bank.\nUse the 'help' argument if you are stuck.\n");
        return 1;
    }

    return 0;
}