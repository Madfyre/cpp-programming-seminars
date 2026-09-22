#include "mathutils.hpp"

int sum_to(int n) {
    int acc = 0;
    for (int i = 1; i <= n; ++i) {
        acc += i;
    }
    return acc;
}
