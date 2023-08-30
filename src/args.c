#include <stdio.h>
#include <stdlib.h>
#define EXPECTED_ARGC 1


size_t parse_args(int _argc, char** _argv) {
    // Check argument limits (executable path + percentage)
    _argc--;
    if (_argc > EXPECTED_ARGC) {
        fprintf(stderr, "Passed too many arguments, expected %d received %d.\n", EXPECTED_ARGC, _argc);
        exit(1);
    } else if (_argc < EXPECTED_ARGC) {
        fprintf(stderr, "Not enough arguments, expected %d and received %d.\n", EXPECTED_ARGC, _argc);
        exit(1);
    }

    // get percentage
    size_t percentage = 0; 
    sscanf(_argv[1], "%lu%%", &percentage);

    // validate percentage
    if (percentage > 100) {
        fprintf(stderr, "Went over maximum amount of memory to allocate (%lu%% over 100%% limit).\n", percentage - 100);
        exit(1);
    }

    // return validated percentage
    return percentage;
}

