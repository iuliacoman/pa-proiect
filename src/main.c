#include "task1.h"
#include "task2.h"
#include <string.h>

int main(int argc, char *argv[]){
    if (argc<3) return 1;
    //rezolvareTask1(argc, argv);
    rezolvareTask2(argv[1], argv[2]);
    return 0;
}