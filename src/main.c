#include "task1.h"
#include "task2.h"

int main(int argc, char *argv[]){
    if (argc<3) return 1;
    if (strstr(argv[1], "task2") != NULL || strstr(argv[1], "c2") != NULL) {
        rezolvareTask2(argv[1], argv[2]);
    } 
    else {
        rezolvareTask1(argc, argv); 
    }

    return 0;
}