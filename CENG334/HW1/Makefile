CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -O2
CFLAGS = -Wall -Wextra -O2
TARGET = server

OBJS = server.o print_output.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

server.o: server.cpp print_output.h game_structs.h
	$(CXX) $(CXXFLAGS) -c server.cpp

print_output.o: print_output.c print_output.h game_structs.h
	$(CC) $(CFLAGS) -c print_output.c

clean:
	rm -f *.o $(TARGET)