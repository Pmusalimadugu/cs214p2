#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// buffer size for the char array
#define BUFFER_SIZE 1
// initial size for the word vector
#define INIT_WORD_SIZE 20

/**
* @brief 
* word wraps to the given width
* @param read_fd
* the file descriptor of the location to read from
* @param write_fd
* the file descriptor of the location to write to
* @return void
*/
void wrap(int read_fd, int write_fd, int width);