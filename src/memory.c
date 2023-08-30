#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define MEMPATH "/proc/meminfo"


unsigned long get_available_memory(void) {
    // open /proc/meminfo
    FILE* fp = fopen(MEMPATH, "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open memory information.\n");
    }

    // get available memory
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    size_t available_mem = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("%s", line);
        // check if memory is available and return the amount in b (kb * 1024)
        if (strstr(line, "MemAvailable:") != NULL) {
            sscanf(line, "MemAvailable: %lu\n", &available_mem);
            return (available_mem * 1024);
        }

    }
    return 0;
}


size_t get_fillable(size_t available) {
    return (available - (available % sizeof(int64_t)));
}


void fill_memory(size_t fillable) {
    // allocate it
    int64_t* memvec = (int64_t*) malloc(fillable);
    size_t length = fillable / sizeof(int64_t);
    int digits = floor(log10(fillable)) + 1;
    int percentage = 0;

    // fill it
    printf("\033[?25l");  /* disable cursor */
    for (size_t i=0; i<length; i++) {
        memvec[i] = ((i + 1) * 2) / 3;  /* Random math operation */
        // print percentage
        if (i % (length / 100) == 0) {
            if (percentage == 100) {
                printf("\033[32m");
            }
            printf("\r\033[KPercentage: %3d/100%%", percentage);
            fflush(stdout);
            percentage++;
        }
        fflush(stdout);
    }

    // free
    free(memvec);
    printf("\033[?25h\n"); /* reenable cursor */
}
