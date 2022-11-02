//Copyright (c) Simo Voutilainen 2022

#include "list.h"

WordNode * wd_create(char* word, WordNode *next)
{
  WordNode *wn = malloc(sizeof(WordNode));
  strcpy(wn->word, word);
  wn->next = next;
  return wn;
}

WordList * wl_create(void)
{
  WordList *wl = malloc(sizeof(WordList));
  wl->n = 0;
  wl->head = NULL;
  return wl;
}

void wl_addToFront(WordList *wl, char* word)
{
  wl->head = wd_create(word, wl->head);
  wl->n += 1;
}

void wl_deleteFromFront(WordList *wl)
{
  if(wl->n > 0)
  {
    WordNode *oldHead = wl->head;
    wl->head = wl->head->next;
    free(oldHead);
    wl->n -= 1;
  }
}

void wl_empty(WordList *wl)
{
  while(wl->n > 0)
  {
    wl_deleteFromFront(wl);
  }
}

void wl_delete(WordList *wl)
{
  wl_empty(wl);
  free(wl);
}

void wl_print(const WordList *wl)
{
  WordNode *s;
  for(s = wl->head; s != NULL; s = s->next)
  {
    printf("%s ", s->word);
  }
}

void wl_pruneList(WordList *wl, char* letters, char* colour)
{
  WordNode *s;
  WordNode *previousWord = wl->head;
  bool removeThis;
  for(s = wl->head; s != NULL; s = s->next)
  {
      removeThis = false;
      if(strcmp(colour, "green") == 0)
      {
          removeThis = wl_pruneGreen(s->word, letters);
      }
      else if(strcmp(colour, "yellow") == 0)
      {
        //for each each letter-pos pair, go through shortlist and remove every word that has that letter in that pos or that does not contain that letter
        removeThis = wl_pruneYellow(s->word, letters);
      }
      else if (strcmp(colour, "grey") == 0)
      {
        //for each each letter-pos pair, go through shortlist and remove every word that contains that letter
        removeThis = wl_pruneGrey(s->word, letters);
      }
      if(removeThis == true)
      {
          //if this is the first word in the list,
          if(previousWord == s)
          {
              //update list head:
              wl->head = s->next;
              //move both previousWord and s to point to the next word:
              previousWord = s->next;
          }
          else
          {
              previousWord->next = s->next;
          }
          free(s);
          wl->n -= 1;
      }
      else
      {
          previousWord = s;
      }
  }
}

bool wl_pruneGreen(char* word, char* greens)
{
    int i;
    for(i=0; i<strlen(greens)-1; i=i+2)
    {
        char letter = greens[i];
        int pos = (int)(greens[i+1])-49;
        if(word[pos] != letter)
        {
            return true;
        }
    }
    return false;
}

bool wl_pruneYellow(char* word, char* yellows)
{
    int i;
    int j;
    bool pruneThis;
    for(i=0; i<strlen(yellows)-1; i=i+2)
    {
        pruneThis = true;
        char letter = yellows[i];
        int pos = (int)(yellows[i+1])-49;
        //if a yellow letter occurs in the given pos, drop this word:
        if(word[pos] == letter)
        {
            return true;
        }
        //check the whole word for matches:
        for(j=0; j<5; j++)
        {
            //if any match is found, keep the word (the given pos was already
            //ruled out in the previous if()
            if(word[j] == letter)
            {
                pruneThis = false;
            }
        }
        //After each letter, check pruneThis. If it is still true,
        //the word does not contain this letter, and there's no
        //need to check the rest:
        if(pruneThis)
        {
            return true;
        }
    }
    return false;
}

bool wl_pruneGrey(char* word, char* greys)
{
    int i;
    int j;
    for(i=0; i<strlen(greys)-1; i=i+1)
    {
        char letter = greys[i];
        //check the whole word for matches:
        for(j=0; j<5; j++)
        {
            //if any match is found, drop the word:
            if(word[j] == letter)
            {
                return true;
            }
        }
    }
    //if processing gets this far, the word contains none
    //of the grey letters and can be kept:
    return false;
}
