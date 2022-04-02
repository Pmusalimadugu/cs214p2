#pragma once
#include <stdlib.h>

/**
* @brief 
* maintains a word vector, similar to cpp std::vector
*/
typedef struct {
  char *word;
  size_t used;
  size_t size;
} Word;


/**
* @brief 
* creates the word with given initial size
* @param w
* pointer to word struct
* @param initalSize
* size of vector initally
* @return void
*/
void createWord(Word *w, size_t initialSize);
/**
* @brief 
* adds character to word vector, similar to cpp std::vector push_back()
* @param w
* pointer to word struct
* @param character
* character to push back
* @return void
*/
void push_back(Word *w, char character);
/**
* @brief 
* frees word
* @param w
* pointer to word struct
* @return void
*/
void freeWord(Word *w);