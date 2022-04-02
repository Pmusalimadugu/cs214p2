#pragma once
#include <stdlib.h>

typedef struct {
  char *word;
  size_t used;
  size_t size;
} Word;

void createWord(Word *w, size_t initialSize);
void push_back(Word *w, char element);
void freeWord(Word *w);