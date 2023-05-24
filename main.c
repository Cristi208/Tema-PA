#include "functii.h"
int main()
{
    int numTeams;
    FILE* g=fopen("r.out","w");
    Team* list = read(&numTeams);
    verifica_numar_echipe(&list,numTeams);
    printList(list,g);
    return 0;
}

