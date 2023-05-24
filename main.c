#include "functii.h"
int main(int argc, char *argv[])
{   int v[5],numTeams;
    FILE *f = fopen(argv[1], "rt");
    FILE *g = fopen(argv[3], "wt");
    int i;
    for (i = 0; i < 5; i++) {
        fscanf(f, "%d", &v[i]);
    }
    fclose(f);
    Team* list = citeste(argv[2],&numTeams);
    if(v[0]==1 && v[1]==0)
    printList(list,g);
    if(v[1]==1 && v[2]==0)
    {verifica_numar_echipe(&list,numTeams);
    printList(list,g);
    }
    if(v[2]==1 && v[3]==0)
    {
         procesareMeciuri(&list,&numTeams);
    }
    return 0;
}
/// argv[1] = c.in; argv[2] = d.in; argv[3] = r.out
