#make file example

CC = gcc #compiler
#CFLAGS = -Wall -std=c99 -O3
TARGET = graph #target file name

all:
	$(CC) -o $(TARGET) readFile.c


clean:
	rm $(TARGET)