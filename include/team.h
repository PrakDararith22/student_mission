#ifndef TEAM_H
#define TEAM_H

#define NAME_LEN 40
#define LINE_LEN 160

typedef struct {
    int id;
    char name[NAME_LEN];
    int score;
    int missions;
} Team;

int findTeamIndex(const Team teams[], int size, int id);
int ensureCapacity(Team **teams, int *capacity, int required);
int addTeam(Team **teams, int *size, int *capacity, Team candidate);
int recordMission(Team teams[], int size, int id, int points);
int deleteTeam(Team teams[], int *size, int id);
void sortLeaderboard(Team teams[], int size);
void displayTeams(const Team teams[], int size);
void displayTeam(const Team *t);
int loadTeams(const char *filename, Team **teams, int *size, int *capacity);
int saveTeams(const char *filename, const Team teams[], int size);
void readText(const char *prompt, char text[], int limit);
int readInt(const char *prompt, int *value);

#endif