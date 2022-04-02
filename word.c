#include "word.h"

void createWord(Word *w, size_t initialSize) {
  w->word = malloc(initialSize * sizeof(char));
  w->used = 0;
  w->size = initialSize;
}

void push_back(Word *w, char character) {
  if (w->used == w->size) {
    w->size *= 2;
    w->word = realloc(w->word, w->size * sizeof(char));
  }
  w->word[w->used++] = character;
}

void freeWord(Word *w) {
  free(w->word);
  w->word = NULL;
  w->used = w->size = 0;
}