INCLUDES= -I ./include
FLAGS= -g
OBJECTS=./build/emulatormemory.o ./build/emulator.o ./build/emulatorscreen.o

all:${OBJECTS}
	gcc ${FLAGS} ${INCLUDES} ./src/main.c ${OBJECTS} -L ./lib -lmingw32 -lSDL2main -lSDL2 -o ./bin/main

./build/emulatormemory.o:src/emulatormemory.c
	gcc ${FLAGS} ${INCLUDES} ./src/emulatormemory.c -c -o ./build/emulatormemory.o

./build/emulator.o:src/emulator.c
	gcc ${FLAGS} ${INCLUDES} ./src/emulator.c -c -o ./build/emulator.o

./build/emulatorscreen.o:src/emulatorscreen.c
	gcc ${FLAGS} ${INCLUDES} ./src/emulatorscreen.c -c -o ./build/emulatorscreen.o