# Campus Quest — Exit Tickets
Individual exit ticket: one invariant, one bug found, one next improvement.

## Sinsideth Sithikar (Memory Guardian)
- **Invariant:** `0 <= size <= capacity`; the owner pointer is `NULL` or the live allocation.
- **Bug found:** growth used `*teams = realloc(...)` directly — a failure would have leaked the old block (fixed with the temporary-pointer pattern).
- **Next:** double-check with valgrind on rename to confirm exactly one free.

## Limsok Kelly (Record Architect)
- **Invariant:** every `Team`'s ID, name, score, and missions move together as one object.
- **Bug found:** a duplicate-ID add left the record half-committed (fixed by validating *before* the copy + commit).
- **Next:** add an edit-team feature so records can be updated in place.

## Yem Kanhnalida (Test Captain)
- **Invariant:** indexes `0..size-1` are the only meaningful records; tests never read unused capacity.
- **Bug found:** invalid mission points (0 and 101) were applied before the range check (fixed by validating points first).
- **Next:** automate the evidence sheet so pass/fail is filled by the script, not by hand.

## Eng Samrith (UX)
- **Invariant:** only the logical records are displayed, so the empty list shows "No teams registered yet." instead of garbage rows.
- **Bug found:** long team names misaligned the leaderboard columns (fixed with fixed-width `setw`).
- **Next:** add a delete-confirmation prompt.

## Prak Dararith (Integration Captain / Presenter)
- **Invariant:** menu choices 1-5 each wire to exactly one mutating function and the array is freed exactly once on exit; there is no path that reads or writes a record outside `0..size-1`.
- **Bug found:** a save-and-exit could drop recent edits if `teams.txt` could not be reopened — the failure was only reported as a warning (fixed by loading the saved file flow path so reload/re-demo always sees the same logical records).
- **Next:** add an automated end-to-end demo script that drives the menu and verifies save/reload in a single run.