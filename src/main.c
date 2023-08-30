#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "args.h"
#include "memory.h"
#define MSECS 1000000


void sighandler(int signo) {
    switch (signo) {
        case SIGINT:
        case SIGSTOP:
            // stop and re-enable cursor
            printf("\r\033[KStopping...\033[?25h\n"); 
            exit(EXIT_SUCCESS);
    }
}


int main(int argc, char** argv) {
    // set signal handler
    if (signal(SIGINT, sighandler) == SIG_ERR) {
        printf("Failed to catch SIGINT!\n");
    }

    // parse arguments
    size_t sz = parse_args(argc, argv);

    // get available memory
    size_t available = get_available_memory();
    if (available == 0) {
        fprintf(stderr, "Failed to get memory info!\n");
    }
    size_t raw_perc = (sz * available) / 100;

    /* get the amount of memory that will be fillable, that amount will be 
     * rounded down from the available memory and divided by the size of the
     * struct. */
    size_t fillable = get_fillable(raw_perc);

    // Print information
    printf("\033[33mInformation:\033[00m\n");
    printf("  Available memory:\t%16lu bytes\n", available);
    printf("  Raw %lu%% of available:\t%16lu bytes\n", sz, raw_perc);
    printf("  Fillable memory:\t%16lu bytes\n", fillable);

    // fill memory and then free it.
    fill_memory(fillable);

    // exit
    return EXIT_SUCCESS;
}
