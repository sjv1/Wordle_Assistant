//Wordle Assistant
//Copyright (c) Simo Voutilainen 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

void populate(WordList *wl, char words[count][len+1])
{
    int i = 0;
    for (i = 0; i < count; i++)
    {
        wl_addToFront(wl, words[i]);
    }
}

void readWords(char words[count][len+1])
{
    FILE *wordfile = fopen("words.txt", "r");
    char list[100000];
    char* word;
    fgets(list, 100000, wordfile);
    fclose(wordfile);
    int i = 0;
    int j = 0;
    for(word = strtok(list, " "); word != NULL; word = strtok(NULL, " "))
    {
        for(j = 0; j < len+1; j++)
        {
            words[i][j] = word[j];
        }
        i++;
    }
    return;
}

void check(WordList *shortlist, char* colour)
{
    char input[15];
    int i;
    bool prune = true;
    printf("Give %s letters in a format where each letter is followed by its position, e.g. g1s4s5:\n", colour);
    fgets(input, 15, stdin);
    fflush(stdin);
    if(input != NULL)
    {
        for(i=0; i<strlen(input)-1; i=i+2)
        {
            if(!(isalpha(input[i]) && isdigit(input[i+1]))) //better: check that 0<input[i+1]<6
            {
                printf("Cannot parse input: %c%c. The input must consist of letter-number pairs.\n", input[i], input[i+1]);
                prune = false;
                break;
            }
        }
        if(prune)
        {
            wl_pruneList(shortlist, input, colour);
            printf("shortlist has %d items", shortlist->n);
            if(shortlist->n < 20)
            {
                printf(":\n");
                wl_print(shortlist);

            }
            printf("\n");
        }
    }
}

void checkGrey(WordList *shortlist)
{
    char input[15];
    int i;
    bool prune = true;
    printf("Give grey letters without any position, e.g. gls:\n");
    fgets(input, 15, stdin);
    fflush(stdin);
    if(input != NULL)
    {
        for(i=0; i<strlen(input)-1; i=i+1)
        {
            if(!(isalpha(input[i])))
            {
                printf("Cannot parse input: %c. The input must contain only letters.\n", input[i]);
                prune = false;
                break;
            }
        }
        if(prune)
        {
            wl_pruneList(shortlist, input, "grey");
            printf("shortlist has %d items", shortlist->n);
            if(shortlist->n < 20)
            {
                printf(":\n");
                wl_print(shortlist);

            }
            printf("\n");
        }
    }
}

void run(char words[count][len+1])
{
    char cont = 'y';
    WordList* shortlist = wl_create();
    populate(shortlist, words);
    while(cont != 'n')
    {
        check(shortlist, "green");
        check(shortlist, "yellow");
        checkGrey(shortlist);
        printf("Continue (y/n)?");
        cont = fgetc(stdin);
        fflush(stdin);
        printf("\n");
    }
    wl_delete(shortlist);
}

int main()
{
    char words[count][len+1];
    readWords(words);
    run(words);
    return 0;
}
