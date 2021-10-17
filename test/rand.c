
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    time_t t;
    srand((unsigned) time(&t));
    printf("\n%d\n", 1 + rand()%3);

}