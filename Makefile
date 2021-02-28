build32:
	@echo Building...
	g++32 -c -Wall -std=c++17 main.cpp -o main.o
	g++32 -c -Wall -std=c++17  cpu\cpu.cpp -o cpu\cpu.o
	g++32 -c -Wall -std=c++17  memory\memory.cpp -o memory\memory.o
	g++32 -c -Wall -std=c++17  programmer\programmer.cpp -o programmer\programmer.o
	g++32 -c -Wall -std=c++17  debugger\debugger.cpp -o debugger\debugger.o
	@echo Linking...
	g++32 -std=c++17  main.o cpu\cpu.o memory\memory.o programmer\programmer.o debugger\debugger.o -o 8086.exe
	@echo Done

build64:
	@echo Building...
	g++ -c -Wall -std=c++17  main.cpp -o main.o
	g++ -c -Wall -std=c++17  cpu\cpu.cpp -o cpu\cpu.o
	g++ -c -Wall -std=c++17  memory\memory.cpp -o memory\memory.o
	g++ -c -Wall -std=c++17  programmer\programmer.cpp -o programmer\programmer.o
	g++ -c -Wall -std=c++17  debugger\debugger.cpp -o debugger\debugger.o
	@echo Linking...
	g++ -std=c++17  main.o cpu\cpu.o memory\memory.o programmer\programmer.o debugger\debugger.o -o 8086.exe
	@echo Done