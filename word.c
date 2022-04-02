#include "word.h"

void createWord(Word *w, size_t initialSize) {
  //allocate memory
  w->word = malloc(initialSize * sizeof(char));
  //used init 0
  w->used = 0;
  //init size
  w->size = initialSize;
}

void push_back(Word *w, char character) {
  //if more size is needed
  if (w->used == w->size) {
    //double size
    w->size *= 2;
    //reallocate array
    w->word = realloc(w->word, w->size * sizeof(char));
  }
  //assign value
  w->word[w->used++] = character;
}

void freeWord(Word *w) {
  //free array
  free(w->word);
  //remove array ptr
  w->word = NULL;
  //set size and used to 0
  w->used = w->size = 0;
}