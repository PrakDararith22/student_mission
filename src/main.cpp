// Campus Quest - Team 5
// Sinsideth Sithikar (Memory Guardian)
// Limsok Kelly (Record Architect)
// Yem Kanhnalida (Test Captain)
// Eng Samrith (UX)
// Prak Dararith (Integration Captain / Presenter)

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "team.h"

void displayTeams(const Team teams[], int size)
{
    if (size == 0) {
        std::cout << "No teams registered yet.\n";
        return;
    }
    std::cout << "ID\tNAME\t\t\t\t\tSCORE\tMISSIONS\n";
    std::cout << "------------------------------------------------------------\n";
    for (int i = 0; i < size; i++)
        std::cout << teams[i].id << "\t" << teams[i].name << "\t\t\t\t\t"
                  << teams[i].score << "\t" << teams[i].missions << "\n";
}

void displayTeam(const Team *t)
{
    if (t == nullptr) {
        std::cout << "ID not found.\n";
        return;
    }
    std::cout << "ID " << t->id << ": " << t->name
              << " | score " << t->score
              << " | missions " << t->missions << "\n";
}

void readText(const char *prompt, char text[], int limit)
{
    std::cout << prompt;
    if (std::fgets(text, limit, stdin) != nullptr)
        text[std::strcspn(text, "\n")] = '\0';
}

int readInt(const char *prompt, int *value)
{
    char line[LINE_LEN], extra;
    std::cout << prompt;
    if (std::fgets(line, sizeof line, stdin) == nullptr) return 0;
    return std::sscanf(line, "%d %c", value, &extra) == 1;
}

int main(void)
{
    Team *teams = nullptr;
    int size = 0;
    int capacity = 0;
    int choice;

    loadTeams("teams.txt", &teams, &size, &capacity);

    do {
        std::cout << "\n=== CAMPUS QUEST LEADERBOARD ===\n"
                  << "1. Register a team\n2. Record mission points\n3. Find a team\n"
                  << "4. Remove a team\n5. Show leaderboard\n6. Save and exit\n";

        if (!readInt("Choose: ", &choice)) {
            std::cout << "Invalid menu input.\n";
            continue;
        }

        if (choice == 1) {
            Team candidate = {0, "", 0, 0};
            readInt("Team ID: ", &candidate.id);
            readText("Team name: ", candidate.name, NAME_LEN);
            if (addTeam(&teams, &size, &capacity, candidate))
                std::cout << "Team " << candidate.id << " registered.\n";
            else
                std::cout << "Registration failed: invalid or duplicate ID.\n";
        } else if (choice == 2) {
            int id, points;
            readInt("Team ID: ", &id);
            readInt("Mission points (1-100): ", &points);
            if (recordMission(teams, size, id, points))
                std::cout << "Points recorded.\n";
            else
                std::cout << "Failed: points must be 1-100 and ID must exist.\n";
        } else if (choice == 3) {
            int id;
            readInt("Team ID: ", &id);
            int idx = findTeamIndex(teams, size, id);
            displayTeam(idx == -1 ? nullptr : &teams[idx]);
        } else if (choice == 4) {
            int id;
            readInt("Team ID: ", &id);
            if (deleteTeam(teams, &size, id))
                std::cout << "Team " << id << " removed.\n";
            else
                std::cout << "ID not found.\n";
        } else if (choice == 5) {
            sortLeaderboard(teams, size);
            displayTeams(teams, size);
        } else if (choice == 6) {
            if (!saveTeams("teams.txt", teams, size))
                std::cout << "Warning: data could not be saved.\n";
        } else {
            std::cout << "Choose a number from 1 to 6.\n";
        }
    } while (choice != 6);

    std::free(teams);
    teams = nullptr;
    return 0;
}