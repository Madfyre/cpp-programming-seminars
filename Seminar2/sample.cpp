#include <iostream>

int* foo(int x) {
    int* p = new int(x);
    return p;
}

void bar() {
    int a[10];
    for (int i = 10; i < 20; ++i) {
        a[i - 10] = i;
    }
}

int main() {
    int* y = foo(4);
    int a = 10;
    std::cout << *y << std::endl;
    return 0;
}

