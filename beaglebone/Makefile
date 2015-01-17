
CC=clang++
CFLAGS=-Wall
LFLAGS=

OBJ=dynamixel.o main.o dylib.o dxl_hal.cpp

TARGET=dynamixel

all: $(OBJ)
	$(CC) -o $(TARGET) $(LFLAGS) $(OBJ)

%.o:
	$(CC) -c $(basename $@).cpp

clean:
	rm -rf *.o $(TARGET)
