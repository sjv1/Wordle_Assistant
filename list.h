#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum {
    count = 2315,
    len = 5
};

struct WordNode
{
  char word[len+1];
  struct WordNode *next;
};

typedef struct WordNode WordNode;

WordNode * wd_create(char * word, WordNode *next);

struct WordList
{
  size_t n;
  WordNode *head;
};

typedef struct WordList WordList;

WordList * wl_create(void);

void wl_addToFront(WordList *wl, char* word);

void wl_deleteFromFrontwl_deleteFromFront(WordList *wl);

void wl_empty(WordList *wl);

void wl_delete(WordList *wl);

void wl_print(const WordList *wl);

void wl_pruneList(WordList *wl, char* greens, char*);

bool wl_pruneGreen(char*, char*);

bool wl_pruneYellow(char*, char*);

bool wl_pruneGrey(char* word, char* greys);
