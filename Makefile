#make file example

CC = gcc #compiler

readFile.o = readFile.cpp nodes.h calendar.h simulation.h
	$(CC) -c readFile.cpp

nodes.o = nodes.cpp readFile.h calendar.h simulation.h
	$(CC) -c nodes.cpp

calendar.o = calendar.cpp readFile.h calendar.h simulation.h
	$(CC) -c calendar.cpp

simulation.o = simulation.cpp readFile.h calendar.h simulation.h
	$(CC) -c simulation.cpp
	
simulation: readFile.o nodes.o calendar.o simulation.o
	$(CC) readFile.o nodes.o calendar.o simulation.o
