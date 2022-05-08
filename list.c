
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
  printf("List:");
  for(s = wl->head; s != NULL; s = s->next)
  {
    printf(" %s", s->word);
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
      }
      else if (strcmp(colour, "grey") == 0)
      {
        //for each each letter-pos pair, go through shortlist and remove every word that contains that letter
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

/*
double dl_alkio(const DblLista *lista, size_t i)
{
    WordNode *s = lista->paa;
    int j = 0;
    while ((j < i) && (s != NULL))
    {
        s = s->seur;
        j++;
    }
    if (s == NULL)
    {
        return 0;
    }
    return s->data;
}

WordNode * dl_lisaa(DblLista *lista, size_t i, double arvo)
{
    WordNode* u = NULL;
    WordNode* s = lista->paa;
    WordNode* e = NULL;
    int j = 0;
    if ((i == 0) || (lista->n == 0))
    {
        dl_lisaaEteen(lista, arvo);
        return lista->paa;
    }
    while ((j < i) && (s != NULL))
    {
        e = s;
        s = s->seur;
        j++;
    }
    u = ds_luo(arvo, NULL);
    e->seur = u;
    u->seur = s;
    lista->n += 1;
    return u;
}

double dl_poista(DblLista *lista, size_t i)
{
    WordNode* s = lista->paa;
    WordNode* e = NULL;
    int j = 0;
    double arvo = 0;
    if (i > lista->n)
    {
        return 0;
    }
    if (i == 0)
    {
        return dl_poistaEdesta(lista);
    }
    while (j < i)
    {
        e = s;
        s = s->seur;
        j++;
    }
    arvo = s->data;
    e->seur = s->seur;
    free(s);
    lista->n -= 1;
    return arvo;
}
*/
