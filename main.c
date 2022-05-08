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

void greenCheck(WordList *shortlist)
{
    char greens[15];
    int i;
    bool prune = true;
    printf("Give green letters in a format where each letter is followed by its position, e.g. g1s4s5:\n");
    fgets(greens, 15, stdin);
    fflush(stdin);
    if(greens != NULL)
    {
        for(i=0; i<strlen(greens)-1; i=i+2)
        {
            if(!(isalpha(greens[i]) || isdigit(greens[i+1]))) //better: check that 0<greens[i+1]<6
            {
                printf("Cannot parse input: %c%c. The input must consist of letter-number pairs.\n", greens[i], greens[i+1]);
                prune = false;
                break;
            }
        }
        if(prune)
        {
            wl_pruneGreen(shortlist, greens);
            printf("shortlist has %d items\n", shortlist->n);
            if(shortlist->n < 20)
            {
                wl_print(shortlist);
                printf("\n");
            }
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
        greenCheck(shortlist);
    /*
    read yellow letters in the same format, e.g. g2g3s1s2
    for each each letter-pos pair, go through shortlist and remove every word that has that letter in that pos-1 or that does not contain that letter
    read grey letters as a list, e.g. irthdw
    for each each letter-pos pair, go through shortlist and remove every word that contains that letter
    output shortlist
    read continue
    */
        printf("Continue (y/n)?");
        cont = fgetc(stdin);
        fflush(stdin);
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
