// Campus Quest - Team 5
// Sinsideth Sithikar (Memory Guardian)
// Limsok Kelly (Record Architect)
// Yem Kanhnalida (Test Captain)
// Eng Samrith (UX)
// Prak Dararith (Integration Captain / Presenter)

#include "team.h"

#include <cstdio>
#include <cstdlib>

int findTeamIndex(const Team teams[], int size, int id)
{
    for (int i = 0; i < size; i++)
        if (teams[i].id == id)
            return i;
    return -1;
}

int ensureCapacity(Team **teams, int *capacity, int required)
{
    if (*capacity >= required)
        return 1;

    int newCapacity = (*capacity == 0) ? 2 : *capacity;
    while (newCapacity < required)
        newCapacity *= 2;

    Team *tmp = static_cast<Team *>(std::realloc(*teams, newCapacity * sizeof(Team)));
    if (tmp == nullptr)
        return 0;

    *teams = tmp;
    *capacity = newCapacity;
    return 1;
}

int addTeam(Team **teams, int *size, int *capacity, Team candidate)
{
    if (candidate.id <= 0 || candidate.name[0] == '\0' ||
        candidate.score < 0 || candidate.missions < 0)
        return 0;
    if (findTeamIndex(*teams, *size, candidate.id) != -1)
        return 0;

    if (!ensureCapacity(teams, capacity, *size + 1))
        return 0;

    (*teams)[*size] = candidate;
    (*size)++;
    return 1;
}

int recordMission(Team teams[], int size, int id, int points)
{
    if (points < 1 || points > 100)
        return 0;

    int i = findTeamIndex(teams, size, id);
    if (i == -1)
        return 0;

    teams[i].score += points;
    teams[i].missions++;
    return 1;
}

int deleteTeam(Team teams[], int *size, int id)
{
    int i = findTeamIndex(teams, *size, id);
    if (i == -1)
        return 0;

    for (int j = i; j < *size - 1; j++)
        teams[j] = teams[j + 1];
    (*size)--;
    return 1;
}

void sortLeaderboard(Team teams[], int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (teams[j].score < teams[j + 1].score ||
                (teams[j].score == teams[j + 1].score &&
                 teams[j].missions < teams[j + 1].missions)) {
                Team tmp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = tmp;
            }
        }
    }
}

int loadTeams(const char *filename, Team **teams, int *size, int *capacity)
{
    FILE *fp = std::fopen(filename, "r");
    if (fp == nullptr)
        return 0;

    char line[LINE_LEN];
    while (std::fgets(line, sizeof line, fp) != nullptr) {
        Team t = {0, "", 0, 0};
        char extra;
        int n = std::sscanf(line, "%d|%39[^|\n]|%d|%d %c",
                            &t.id, t.name, &t.score, &t.missions, &extra);
        if (n != 4)
            continue;
        if (t.id <= 0 || t.name[0] == '\0' || t.score < 0 || t.missions < 0)
            continue;
        if (findTeamIndex(*teams, *size, t.id) != -1)
            continue;
        if (!ensureCapacity(teams, capacity, *size + 1))
            break;
        (*teams)[(*size)++] = t;
    }
    std::fclose(fp);
    return 1;
}

int saveTeams(const char *filename, const Team teams[], int size)
{
    FILE *fp = std::fopen(filename, "w");
    if (fp == nullptr)
        return 0;

    for (int i = 0; i < size; i++)
        std::fprintf(fp, "%d|%s|%d|%d\n",
                     teams[i].id, teams[i].name, teams[i].score, teams[i].missions);

    int ok = !std::ferror(fp);
    if (std::fclose(fp) != 0)
        ok = 0;
    return ok;
}