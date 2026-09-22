#!/usr/bin/env bash
# Walk demo.cpp through every build stage. Artifacts land in out/.
# Usage: ./stages.sh [--pause]
set -uo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"

CXX=${CXX:-clang++}
STD=-std=c++23
OUT=out
mkdir -p "$OUT"
[ "${1:-}" = "--pause" ] && PAUSE=1 || PAUSE=0

step() { echo; echo "=============================================="; echo "  $*"; echo "=============================================="; }
run() { echo "\$ $*"; "$@"; }
wait_key() { [ "$PAUSE" = 1 ] && { echo; read -r -p "-- Enter --" _; }; return 0; }

step "1/4 COMPILATION: demo.cpp -> demo.ii"
run $CXX $STD -E demo.cpp -o "$OUT/demo.ii"
echo "  rows: $(wc -l < demo.cpp) -> $(wc -l < "$OUT/demo.ii")"
grep -n 'Seminar 1' "$OUT/demo.ii" | tail -1
grep -n 'int sum_to' "$OUT/demo.ii"
printf '#include <iostream>\nint main() {}\n' > "$OUT/tiny.cpp"
$CXX $STD -E "$OUT/tiny.cpp" -o "$OUT/tiny.ii"
echo "  empty main c <iostream>: 2 -> $(wc -l < "$OUT/tiny.ii") rows"
wait_key

step "2/4 COMPILATION: demo.ii -> demo.s"
run $CXX $STD -fsyntax-only -Xclang -ast-dump demo.cpp > "$OUT/demo.ast.txt" 2>&1
echo "  AST, $(wc -l < "$OUT/demo.ast.txt") rows:"
grep -n 'seminar\|Counter\|twice' "$OUT/demo.ast.txt" | grep -v Implicit | head -3
run $CXX $STD -O0 -S -emit-llvm demo.cpp -o "$OUT/demo.ll"
grep -n 'define .*@main' "$OUT/demo.ll"
run $CXX $STD -O0 -S demo.cpp -o "$OUT/demo.O0.s"
run $CXX $STD -O2 -S demo.cpp -o "$OUT/demo.O2.s"
echo "  -O0: $(wc -l < "$OUT/demo.O0.s") rows, -O2: $(wc -l < "$OUT/demo.O2.s") rows"
echo "  -O2 counted twice(21):"; grep -n '#42' "$OUT/demo.O2.s" | head -1
echo "  -O0 calls:";      grep -n 'bl.*twiceIiE' "$OUT/demo.O0.s" | head -1
wait_key

step "3/4 ASSEMBLY: demo.s -> demo.o"
run $CXX $STD -c demo.cpp -o "$OUT/demo.o"
run $CXX $STD -c mathutils.cpp -o "$OUT/mathutils.o"
echo "  after c++filt (U = undefined, T = defined here):"
nm "$OUT/demo.o" | c++filt
wait_key

step "4/4 LINKAGE: demo.o + mathutils.o -> demo_pipeline"
echo "  without mathutils.o:"
$CXX "$OUT/demo.o" -o "$OUT/broken" 2>&1 | sed 's/^/    /'
run $CXX "$OUT/demo.o" "$OUT/mathutils.o" -o "$OUT/demo_pipeline"
otool -L "$OUT/demo_pipeline" | sed 's/^/    /'
wait_key

step "RUN"
run "./$OUT/demo_pipeline"
echo; echo "Artefacts: $(pwd)/$OUT"
