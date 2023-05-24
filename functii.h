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
    Team* teams;
    int numMatches;
} MatchQueue;

typedef struct {
    Team* teams;
    int numWinners;
} WinnerStack;

Team* read(int* numTeams);
Player* createPlayer(char* firstName, char* secondName, int points);
Team* createTeam(char* name, int numPlayers);
void addPlayerToTeam(Team* team, Player* player, int numPlayers);
void addTeamToList(Team** list, Team* team);
void printList(Team* list,FILE* g);
void verifica_numar_echipe(Team** list, int numTeams);
void elimina(Team** list, Team* team);



