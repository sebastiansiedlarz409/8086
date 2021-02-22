build:
	@echo Building...
	g++ -c main.cpp -o main.o
	g++ -c cpu\cpu.cpp -o cpu\cpu.o
	g++ -c memory\memory.cpp -o memory\memory.o
	@echo Linking...
	g++ main.o cpu\cpu.o memory\memory.o -o 8086.exe
	@echo Done