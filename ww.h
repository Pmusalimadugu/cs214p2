#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUFFER_SIZE 1
#define INIT_WORD_SIZE 20


void wrap(int read_fd, int write_fd, int width);