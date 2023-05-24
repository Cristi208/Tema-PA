#include "functii.h"

Team* citeste(char* fisier,int* numTeams)
{   
     int i,j;
    FILE* file=fopen(fisier, "r");
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
         for(j=1;j<strlen(teamName);j++)
        if(teamName[strlen(teamName)-j]==' ' && teamName[strlen(teamName)-j]=='\r')  
        teamName[strlen(teamName)-j]='\0';
        else j=strlen(teamName);
        
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
void printList(Team* list,FILE* g) {
    Team* currentTeam = list;
    while (currentTeam != NULL) {
        
        fprintf(g,"%s\n", currentTeam->name);
        currentTeam = currentTeam->next;
    }
}
void verifica_numar_echipe(Team** list, int numTeams)
{
    int i=1,numNecesar;
    while(i<=numTeams)
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
        while (currentTeam != NULL) {
            if (currentTeam->points < minpoints) {
                minpoints = currentTeam->points;
                minTeam = currentTeam;
            }
            currentTeam = currentTeam->next;
        }
    elimina(&(*list),minTeam);
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
void creareMeciuri(MatchQueue* meciuri, Team** list)
{
    Team* currentTeam=*list;
    MatchQueue* currentMatch=meciuri;
    while(currentTeam!=NULL && currentTeam->next!=NULL)
    {
        currentMatch->team1=currentTeam;
        currentTeam=currentTeam->next;
        currentMatch->team2=currentTeam;
        currentTeam=currentTeam->next;
        currentMatch->next=(MatchQueue*)malloc(sizeof(MatchQueue));
        currentMatch=currentMatch->next;
        currentMatch->next=NULL;

    }
}
void jocuri(MatchQueue* meciuri, WinnerStack* castigatori, LoserStack* pierzatori)
{
    MatchQueue* currentMatch=meciuri;
    while(currentMatch->next!=NULL)
    {
        if(currentMatch->team1->points>=currentMatch->team2->points)
        {
            actualizarePuncte(currentMatch->team1);
            actualizareCastigatori(&castigatori,currentMatch->team1);
            actualizarePierzatori(&pierzatori,currentMatch->team2);
        }
        else
        {
            actualizarePuncte(currentMatch->team2);
            actualizareCastigatori(&castigatori,currentMatch->team2);
            actualizarePierzatori(&pierzatori,currentMatch->team1);
        }
        currentMatch=currentMatch->next;

    }
}
void actualizarePuncte(Team* castigator)
{
    castigator->points+=1.0;
}
void actualizareCastigatori(WinnerStack** castigatori,Team* echipa)
{
    WinnerStack* newNode = (WinnerStack*)malloc(sizeof(WinnerStack));
    newNode->team = echipa;
    newNode->next=*castigatori;
    *castigatori=newNode;
}
void actualizarePierzatori(LoserStack** pierzatori,Team* echipa)
{
    LoserStack* newNode = (LoserStack*)malloc(sizeof(LoserStack));
    newNode->team = echipa;
    newNode->next=*pierzatori;
    *pierzatori=newNode;
}
void procesareMeciuri(Team** list, int* numTeams)
{
    MatchQueue meciuri;
    WinnerStack *castigatori=(WinnerStack*)malloc(sizeof(WinnerStack));
    LoserStack *pierzatori=(LoserStack*)malloc(sizeof(LoserStack));
    creareMeciuri(&meciuri, list);
    castigatori->team=malloc(sizeof(Team));
    pierzatori->team=malloc(sizeof(Team));
    jocuri(&meciuri,&castigatori,&pierzatori);
    int i;
    for(i=0; i<(*numTeams)/2; i++)
    {
        addTeamToList(&list, castigatori->team);
        castigatori->team=castigatori->team->next;
    }
    (*numTeams)=(*numTeams)/2;

    //freeLoserStack(&pierzatori);
}
void freeLoserStack(LoserStack** pierzatori)
{
    LoserStack* current = *pierzatori;
    while (current != NULL)
    {
        LoserStack* temp = current;
        current = current->next;
        free(temp);
    }
}
