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
        return 0;   // old block + owner + capacity stay unchanged

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
        return 0;                       // duplicate ID rejected

    if (!ensureCapacity(teams, capacity, *size + 1))
        return 0;

    (*teams)[*size] = candidate;        // whole struct, single copy
    (*size)++;
    return 1;
}

int recordMission(Team teams[], int size, int id, int points)
{
    if (points < 1 || points > 100)
        return 0;                       // validate points FIRST

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
        return 0;                       // missing ID: state unchanged

    for (int j = i; j < *size - 1; j++)
        teams[j] = teams[j + 1];        // shift COMPLETE records left
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
                Team tmp = teams[j];    // swap whole objects
                teams[j] = teams[j + 1];
                teams[j + 1] = tmp;
            }
        }
    }
}