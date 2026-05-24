#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include<stdio.h>
#include <string.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    if (argc<3) return 1;
    int nr = 0;
    for (int i = 0; argv[1][i] != '\0'; i++) {
        if (argv[1][i] >= '0' && argv[1][i] <= '9') {
            nr = atoi(&argv[1][i]);
            break;
        }
    }
    if(nr >= 1 && nr <= 5)
        rezolvareTask1(argv[1], argv[2]);
    else if(nr >= 6 && nr <= 10)
        rezolvareTask2(argv[1], argv[2]);
    else if(nr >= 11 && nr <= 15)
        rezolvareTask3(argv[1], argv[2]);
    else if(nr >=16 && nr <= 20)
        rezolvareTask4(argv[1], argv[2]);
    return 0;
}