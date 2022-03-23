#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    count = 2315,
    len = 5
};

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

int main()
{
    char words[count][len+1];
    readWords(words);
    int i = 0;
    for(i = 0; i < count; i++)
    {
        printf("%s ", words[i]);
    }
    return 0;
}
