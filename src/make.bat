g++ -std=c++17 -o day01.o -c day01.cpp -pedantic -Wall -Wextra
g++ -std=c++17 -o main.o -c main.cpp -pedantic -Wall -Wextra
g++ -std=c++17 -o main.exe day01.o main.o
