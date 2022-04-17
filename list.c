#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  printf("\nDone.\n");
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
