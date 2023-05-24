#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char* firstName;
    char* secondName;
    float points;
    struct Player *next;
} Player;

typedef struct {
    char* name;
    int numPlayers;
    Player* players;
    float points;
    struct Team *next;
} Team;

typedef struct {
    Team* team1;
    Team* team2;
    struct MatchQueue *next;
} MatchQueue;

typedef struct {
    Team* team;
    struct WinnerStack *next;
} WinnerStack;

typedef struct {
    Team* team;
    struct LoserStack *next;
} LoserStack;

Team* citeste(char* fisier, int* numTeams);
Player* createPlayer(char* firstName, char* secondName, int points);
Team* createTeam(char* name, int numPlayers);
void addPlayerToTeam(Team* team, Player* player, int numPlayers);
void addTeamToList(Team** list, Team* team);
void printList(Team* list,FILE* g);
void verifica_numar_echipe(Team** list, int numTeams);
void elimina(Team** list, Team* team);
void creareMeciuri(MatchQueue* meciuri, Team** list);
void jocuri(MatchQueue* meciuri, WinnerStack* castigatori, LoserStack* pierzatori);
void actualizarePuncte(Team* castigator);
void actualizareCastigatori(WinnerStack** castigatori,Team* echipa);
void actualizarePierzatori(LoserStack** pierzatori,Team* echipa);
void procesareMeciuri(Team** list, int* numTeams);
void freeLoserStack(LoserStack** pierzatori);



