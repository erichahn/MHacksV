
CC=clang++
CFLAGS=-Wall
LFLAGS=

OBJ=main.o

TARGET=leapMotion

all: $(OBJ)
	$(CC) -o $(TARGET) $(LFLAGS) $(OBJ)

%.o:
	$(CC) -c $(basename $@).cpp

clean:
	rm -rf *.o $(TARGET)
