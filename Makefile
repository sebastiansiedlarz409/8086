CC = g++
CFLAGS = -c -Wall -std=c++17
LFLAGS = -std=c++17
TARGET = 8086.exe
SRC_DIR = src
OBJ_DIR = obj

build:
	@echo Building...
	${CC} ${CFLAGS}  main.cpp -o ${OBJ_DIR}\main.o
	${CC} ${CFLAGS}  ${SRC_DIR}\cpu\cpu.cpp -o ${OBJ_DIR}\cpu.o
	${CC} ${CFLAGS}  ${SRC_DIR}\memory\memory.cpp -o ${OBJ_DIR}\memory.o
	${CC} ${CFLAGS}  ${SRC_DIR}\cpu\instructions.cpp -o ${OBJ_DIR}\instructions.o
	${CC} ${CFLAGS}  ${SRC_DIR}\programmer\programmer.cpp -o ${OBJ_DIR}\programmer.o
	${CC} ${CFLAGS}  ${SRC_DIR}\debugger\debugger.cpp -o ${OBJ_DIR}\debugger.o
	@echo Linking...
	${CC} ${LFLAGS} ${OBJ_DIR}\main.o ${OBJ_DIR}\cpu.o ${OBJ_DIR}\memory.o ${OBJ_DIR}\programmer.o ${OBJ_DIR}\debugger.o ${OBJ_DIR}\instructions.o -o ${TARGET}
	@echo Done