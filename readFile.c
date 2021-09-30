#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;
    char tail[5], head[5], type;

    fp = fopen("grafo1",r);

    if(fp==NULL){
        perror("Error opening the text file");
        return(-1);
    }

    while( fscanf(fp, "%s %s %c\n", tail, head, &type) != NULL ){
        printf("%s %s %c", tail, head, type);
    }

    fclose(fp);
    return 0;
}