#include "functii.h"

Team* read(int* numTeams)
{
     int i,j;
    FILE* file=fopen("d.in", "r");
    if (file == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        return 1;
    }
      fscanf(file,"%d",numTeams);
    Team* list = NULL;

    for (i = 0; i < (*numTeams); i++) {
        int numPlayers;
        fscanf(file, "%d", &numPlayers);
        char teamName[100];
        fgetc(file);
        fgets(teamName,100,file);
        teamName[strlen(teamName)-1]='\0';
        Team* team = createTeam(teamName,numPlayers);
        for (j = 0; j < numPlayers; j++) {
            char firstName[100];
            char secondName[100];
            int points;
            fscanf(file, "%s %s %d", firstName, secondName, &points);

            Player* player = createPlayer(firstName, secondName, points);
            addPlayerToTeam(team, player, numPlayers);
        }
        addTeamToList(&list, team);
    }
    fclose(file);
   // printList(list);
   return list;
}
Player* createPlayer(char* firstName, char* secondName, int points) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->firstName=malloc(100*sizeof(char));
    player->secondName=malloc(100*sizeof(char));
    strcpy(player->firstName,firstName);
    strcpy(player->secondName,secondName);
    player->points = points;
    player->next = NULL;
    return player;
}
Team* createTeam(char* name, int numPlayers) {
    Team* team = (Team*)malloc(sizeof(Team));
    team->name=malloc(100*sizeof(char));
    strcpy(team->name,name);
    team->numPlayers = numPlayers;
    team->players = NULL;
    team->points = 0;
    team->next = NULL;
    return team;
}
void addPlayerToTeam(Team* team, Player* player, int numPlayers) {
    player->next = team->players;
    team->players = player;
    team->points += player->points/numPlayers;
}

void addTeamToList(Team** list, Team* team) {
    team->next = *list;
    *list = team;
}
void printList(Team* list) {
    Team* currentTeam = list;
    while (currentTeam != NULL) {
        printf("Team: %s\n", currentTeam->name);
        Player* currentPlayer = currentTeam->players;
        while (currentPlayer != NULL) {
            printf("Player: %s %s\n", currentPlayer->firstName, currentPlayer->secondName);
            currentPlayer = currentPlayer->next;
        }
        printf("Total points: %.2f\n\n", currentTeam->points);
        currentTeam = currentTeam->next;
    }
}
void verifica_numar_echipe(Team** list, int numTeams)
{
    int i=1,numNecesar;
    while(i<numTeams)
    {
        numNecesar=i;
        i=i*2;
    }
    numNecesar=numTeams-numNecesar;
    for (i = 0; i < numNecesar; i++)
    {
    float minpoints=(*list)->points;
    Team* minTeam=*list;
    Team* currentTeam=(*list)->next;
       /* while(points!=NULL)
        {
            if(points->points < minpoints)
                minpoints=points->points;
            points=points->next;
        }*/
        while (currentTeam != NULL) {
            if (currentTeam->points < minpoints) {
                minpoints = currentTeam->points;
                minTeam = currentTeam;
            }
            currentTeam = currentTeam->next;
        }
    elimina(list,minTeam);
    }

}
void elimina(Team** list, Team* team) {
    if (*list == team) {
        *list = (*list)->next;
        free(team);
        return;
    }

    Team* currentTeam = *list;
    while (currentTeam != NULL && currentTeam->next != team) {
        currentTeam = currentTeam->next;
    }

    if (currentTeam != NULL) {
        currentTeam->next = team->next;
        free(team);
    }
}
/*void elimina(Team** list,float minpoints)
{       if(*list==NULL)
        return;
        Team* temp=*list;
        if(temp->points==minpoints)
        {
                *list=(*list)->next;
                free(temp);
                return;
        }
        Team* prevTeam=*list;
        while(temp!=NULL)
        {
            if((*list)->points!=minpoints)
            {
                prevTeam=temp;
                temp=temp->next;

            }
            else
            {
                prevTeam->next=temp->next;
                free(temp);
                return;
            }
        }
}
*/
