#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * lueKunnes(FILE *virta, char erotin, size_t *pituus)
{
    size_t kap = 1;
    char* puskuri = malloc(kap);
    size_t pit = 0;
    int c = 0;
    c = fgetc(virta);
    while ((c != erotin) && (c != EOF))
    {
        if (pit == kap)
        {
            kap *= 2;
            puskuri = realloc(puskuri, kap);
        }
        puskuri[pit] = c;
        pit++;
        c = fgetc(virta);
    }
    if (pit > 0 || c == erotin)
    {
        puskuri = realloc(puskuri, pit+1);
        puskuri[pit] = '\0';  /*puskurin viimeinen varattu muistipaikka*/
    }
    else
    {
        puskuri = realloc(puskuri, 0);
    }
    *pituus = pit;
    return puskuri;
}



void readWords(char words[2315][6])
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
        for(j = 0; j < 6; j++)
        {
            words[i][j] = word[j];
        }
        i++;
    }
    return;
}

int main()
{
    char words[2315][6];
    readWords(words);
    int i = 0;
    for(i = 0; i < 2315; i++)
    {
        printf("%s\n", words[i]);
    }
    return 0;
}
