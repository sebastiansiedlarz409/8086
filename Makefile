build:
	g++ -c main.cpp
	g++ -c cpu\cpu.cpp
	g++ main.o cpu.o -o 8086.exe