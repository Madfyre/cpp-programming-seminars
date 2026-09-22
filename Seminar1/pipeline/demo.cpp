#include <cstdio>
#include <vector>
#include <iostream>

#include "mathutils.hpp"
int sum_to(int n);

#define GREETING "Seminar 1"
#define SQUARE(x) ((x) * (x))

namespace seminar {

struct Counter {
    int value = 0;
    int value1 = 0;

    int bump(int by) {
        value += by;
        return value;
    }
};

// bump in .text



// virt addr space:

// 0xffffffff
//
// stack 1 MB ()
// |
// V

// ^
// |
// heap
// 
// .data 
// .bss
// .text
// 
// 
// 0x00000

} // namespace seminar

int main() {
    seminar::Counter counter;
    counter.bump(SQUARE(3));

    std::printf("%s: counter=%d twice=%d\n",
                GREETING,
                counter.value,
                sum_to(10));
}
