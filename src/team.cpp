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
