# CPP Programming — семинары

Код с семинаров курса.

```bash
git clone https://github.com/Madfyre/cpp-programming-seminars.git
```

Курс собирается на Clang, все примеры проверены с ним.

## Семинар 1 — как из исходников получается программа

`Seminar1/pipeline/` — небольшая программа из двух файлов (`demo.cpp` и
`mathutils.cpp`) и скрипт, который проводит её по всем этапам сборки:
препроцессор, компиляция в LLVM IR и ассемблер, объектные файлы, линковка.

```bash
./Seminar1/pipeline/stages.sh --pause
```

Все промежуточные файлы (`.ii`, `.ll`, `.s`, `.o`) скрипт складывает в
`Seminar1/pipeline/out/` — их интересно открыть и посмотреть глазами.

Собрать программу обычным способом:

```bash
cmake -S Seminar1 -B build/seminar1
cmake --build build/seminar1
./build/seminar1/demo_pipeline
```

Скрипт писался под macOS: для просмотра зависимостей бинарника он
вызывает `otool -L`, на Linux вместо него работает `ldd`. Поиск инструкции
`bl` в ассемблере рассчитан на ARM (Apple Silicon); на x86 вызов функции
выглядит как `call`.

## Семинар 2 — работа с памятью

`Seminar2/sample.cpp` — пример для разбора ошибок работы с памятью.

```bash
clang++ -std=c++23 -g -fsanitize=address Seminar2/sample.cpp -o sample
./sample
```

Я так и не разобрался почему с санитайзером она ушла в бесконечный луп((

## Семинар 3 — свой класс Matrix

`Seminar3/matrix.cpp` — матрица с ручным управлением памятью: перегрузка
арифметических операторов, поэлементное умножение через `&`, вывод в поток
и многомерный `operator[](row, col)` — only C++23, в более ранних
стандартах так не получится!

```bash
clang++ -std=c++23 -Wall -Wextra Seminar3/matrix.cpp -o matrix
./matrix
```
