build:
	@echo Building...
	g++ -c main.cpp -o main.o
	g++ -c cpu\cpu.cpp -o cpu\cpu.o
	g++ -c memory\memory.cpp -o memory\memory.o
	g++ -c programmer\programmer.cpp -o programmer\programmer.o
	g++ -c debugger\debugger.cpp -o debugger\debugger.o
	@echo Linking...
	g++ main.o cpu\cpu.o memory\memory.o programmer\programmer.o debugger\debugger.o -o 8086.exe
	@echo Done