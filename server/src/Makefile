CC = g++
OPTIONS = -std=c++11 -lpthread -g
OBJ = entry.o

server : $(OBJ)
	$(CC) $(OPTIONS) -o server $(OBJ)

clean :
	- rm -f $(OBJ)
kill :
	- rm -f $(OBJ) server

entry.o: entry.cpp
	$(CC) $(OPTIONS) -c entry.cpp

.c.o:
	$(CC) $(OPTIONS) -c $<
