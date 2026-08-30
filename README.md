# Campus Quest: Team Challenge Leaderboard

A safe dynamic-array leaderboard in **C++ (C++17)** for the Campus Quest hackathon.
Teams register with an ID, name, score, and completed-mission count. The program
keeps every record together, grows capacity safely, searches and removes teams,
produces a ranked leaderboard, and saves/restores a `teams.txt` file. Built with a
hand-written dynamic array (no `std::vector`), per the mission brief.

## Team Members & Roles

| Member | Role | Main responsibility |
| --- | --- | --- |
| Sinsideth Sithikar | Memory Guardian | Owner pointer, size/capacity, `realloc`, cleanup |
| Limsok Kelly | Record Architect | `Team` design, validation, complete-record movement |
| Prak Dararith | Test Captain | Expected results, boundary cases, test evidence |
| Yem Kanhnalida | UX | Menu, prompts, input handling, output formatting, feedback messages |
| Eng Samrith | Integration Captain / Presenter | Menu wiring, function connections, file flow, demo |


## Data Model and File Format

```cpp
typedef struct {
    int id;
    char name[40];
    int score;
    int missions;
} Team;
```

File format: one team per line, four fields separated by `|`:

```
101|Byte Bandits|120|2
102|Pointer Pirates|90|1
```

## Validation Rules

- ID must be **positive** and **unique**.
- Name must be **non-empty** and fit the 40-character array (max 39 + `\0`).
- `score` and `missions` must be **nonnegative**.
- Mission points entered through the menu must be **1 through 100**.

Persistence: malformed, duplicate, or out-of-rule lines in `teams.txt` are **rejected**
without disturbing the already-accepted records.

## Requirements

- GCC/G++ (C++17-compatible compiler)
- CMake 3.16+

## Build & Run

```sh
make        # build (debug)
make run    # build and run
make clean  # remove build artifacts
make release  # build with -O2 optimizations
```

## Project Structure

```
student_mission/
├── CMakeLists.txt
├── Makefile
├── include/
│   └── team.h
└── src/
    ├── main.cpp
    └── team.cpp
```

## Test Gauntlet (T1–T11)

| Test | Setup/action | Expected evidence |
| --- | --- | --- |
| T1 Empty | Show leaderboard, size 0 | No read; clear "no teams" output |
| T2 First add | Add ID 101 | size 1; complete record visible |
| T3 Growth boundary | Capacity 2, add third team | Capacity grows safely; first two records preserved |
| T4 Duplicate | Add ID 101 again | Rejected; size and old record unchanged |
| T5 Invalid points | Add 0 or 101 points | Rejected; score and missions unchanged |
| T6 Search absent | Search unused ID | Not found; no mutation |
| T7 Delete boundaries | Delete first, then last | Complete records shift; size decreases; no out-of-range access |
| T8 Sort identity | Equal/different scores | Correct rank; every name stays attached to its ID and fields |
| T9 Malformed file | Bad field count | Line rejected; accepted collection unchanged |
| T10 Save/reload | Save, exit, rerun | Same accepted logical records restored |
| T11 Cleanup | Exit normally | Allocation freed once; owner no longer used |

## Submission Checklist

- Completed `.cpp` source with group member names in a comment.
- Sample `teams.txt` used for the final demonstration.
- Test evidence sheet containing at least six required tests.
- One screenshot or short note showing successful save/reload.
- Individual exit ticket: invariant, bug found, and next improvement.