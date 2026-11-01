#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <type_traits>
#include <iostream>
#include <vector>
#include <string>

// семь тюремных загадок (опять)
// раскомментируй ОДИН блок (помечено номерами) и смотри!
// в каждом блоке свой main → активным держи ровно один:
// на нём #if 1, на остальных #if 0.

#if 1
////////////////////////
//   1. Строки по значению
////////////////////////
template <typename T>
T Max(T a, T b) { return a > b ? a : b; }

int main() {
    std::printf("%s\n", Max("apple", "banana"));
    // GCC печатает apple, Clang — banana: сравниваются адреса литералов,
    // результат unspecified. Для строк нужна std::string или своя перегрузка.
}
#endif

#if 0
////////////////////////
//   2. Те же строки по ссылке
////////////////////////
template <typename T>
const T& Max(const T& a, const T& b) { return a > b ? a : b; }

int main() {
    // A: не компилируется — T выводится как char[6] и char[7], конфликт
    // Max("apple", "banana");

    // B: компилируется — оба литерала char[6], T = char[6], сравниваются адреса
    Max("apple", "grape");
}
#endif

#if 0
////////////////////////
//   3. Всегда ли побеждает обычная функция
////////////////////////
template <typename T>
void Print(T&) { std::puts("шаблон"); }

void Print(const std::string&) { std::puts("обычная"); }

int main() {
    std::string s = "hi";
    const std::string cs = "hi";
    Print(s);   // шаблон: T = std::string, точное совпадение без добавления const
    Print(cs);  // обычная: равное совпадение, при равенстве обычная важнее
}
#endif

#if 0
////////////////////////
//   4. Тип результата у auto
////////////////////////
template <typename A, typename B>
auto Max(A a, B b) { return a > b ? a : b; }

int main() {
    std::cout << Max(2, 1.5) << ' ' << Max(-1, 1u) << '\n';
    // 2 4294967295: тип ?: один на обе ветки (usual arithmetic conversions);
    // -1 превращается в unsigned и становится наибольшим числом.
}
#endif

#if 0
////////////////////////
//   5. Что проверяется до инстанцирования
////////////////////////
template <typename T>
struct Box {
    void A() { T::Foo(); }  // зависимое имя — проверится при вызове b.A()
    void B() { Foo(); }     // независимое — ошибка сразу при разборе шаблона
};

int main() {
    Box<int> b;
    (void)b;
}
// не компилируется: 'Foo' was not declared (two-phase lookup ловит B)
#endif

#if 0
////////////////////////
//   6. Аргументы-значения
////////////////////////
template <typename T, std::size_t N> class Array { T data_[N]{}; };

static_assert(std::is_same_v<Array<int, 4>, Array<int, 2 + 2>>);  // A: ok
// Array<int, -1> bad;   // B: раскомментируй — ошибка (narrowing в size_t)

int main() {}
#endif

#if 0
////////////////////////
//  13. Рекурсивный Sum с лекции
////////////////////////
template <typename T> T Sum(T v) { return v; }
template <typename T, typename... Rest>
T Sum(T first, Rest... rest) { return first + Sum(rest...); }

int main() {
    std::cout << Sum(1, 2.5, 3.7) << '\n';   // 7   (1 + 6.2 → int)
    std::cout << Sum(2.5, 1, 3.7) << '\n';   // 6.5 (Sum(1,3.7) = 4 int)
}
#endif

#if 0
////////////////////////
//  14. Направление свёртки (чек ассемблер, чек функции и какие сгенерировались!)
////////////////////////
template <typename... Args> auto R(Args... args)   { return (args - ...); }
template <typename... Args> auto L(Args... args)   { return (... - args); }
template <typename... Args> auto Cat(Args... args) { return (args + ...); }

int main() {
    std::cout << R(1, 2, 3) << ' ' << L(1, 2, 3) << '\n';  // 2 -4
    std::cout << Cat(std::string("a"), std::string("b"), std::string("c")) << '\n';
}
#endif



