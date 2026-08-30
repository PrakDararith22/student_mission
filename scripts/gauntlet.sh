#!/bin/bash
# scripts/gauntlet.sh
# Campus Quest test gauntlet - Yem Kanhnalida, Test Captain
# Runs the built binary through T1-T11 and captures everything to transcript.txt

set -e

BINARY="./build/mission.exe"
DATAFILE="teams.txt"
OUTFILE="transcript.txt"

> "$OUTFILE"

log() { echo -e "\n########## $1 ##########" | tee -a "$OUTFILE"; }

log "STAGE A: fresh run - T1,T2,T3,T4,T5,T6,T7,T8"
rm -f "$DATAFILE"

"$BINARY" <<'EOF' >> "$OUTFILE" 2>&1
5
1
101
Byte Bandits
1
102
Pointer Pirates
1
103
Null Pointers
5
1
101
Duplicate Attempt
2
101
0
2
101
101
2
101
50
2
102
50
3
999
4
101
4
103
1
201
Team A
1
202
Team B
2
201
40
2
202
40
5
6
EOF

log "STAGE B: second launch - T10 (save/reload persistence)"

"$BINARY" <<'EOF' >> "$OUTFILE" 2>&1
5
6
EOF

log "STAGE C: malformed teams.txt - T9"
cat > "$DATAFILE" <<'DATA'
301|Good Team|50|1
badline|no|pipes
302|Missing Score||
301|Duplicate ID|10|0
303|Negative Score|-5|0
304|Fine Team|20|2
DATA

"$BINARY" <<'EOF' >> "$OUTFILE" 2>&1
5
6
EOF

log "GAUNTLET COMPLETE"
echo "Transcript written to $OUTFILE"