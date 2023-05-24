#include "functii.h"
int main()
{
    int numTeams;

    Team* list = read(&numTeams);
    verifica_numar_echipe(&list,numTeams);
    printList(list);
    return 0;
}

