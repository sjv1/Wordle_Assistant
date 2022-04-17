#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


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

void run(char words[count][len+1])
{
    char cont = 'y';
    WordList* shortlist = wl_create();
    populate(shortlist, words);
    while(cont != 'n')
    {
        wl_print(shortlist);
        printf("\nWord count: ");
        printf("%d\n", shortlist->n);
    /*
    read green letters in format where a letter is followed by its position, e.g. g1s4s5
    for each each letter-pos pair, go through shortlist and remove every word that doesn't have that letter in that pos-1
    read yellow letters in the same format, e.g. g2g3s1s2
    for each each letter-pos pair, go through shortlist and remove every word that has that letter in that pos-1 or that does not contain that letter
    read grey letters as a list, e.g. irthdw
    for each each letter-pos pair, go through shortlist and remove every word that contains that letter
    output shortlist
    read continue
    */
        printf("Continue (y/n)?");
        cont = fgetc(stdin);
        printf("Your reply was %c\n", cont);
    }
    wl_delete(shortlist);
}

void populate(WordList *wl, char words[count][len+1])
{
    int i = 0;
    for (i = 0; i < count; i++)
    {
        wl_addToFront(wl, words[i]);
    }
}

int main()
{
    char words[count][len+1];
    readWords(words);
    run(words);
    printf("Back in main");
    return 0;
}
