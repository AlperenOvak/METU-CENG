CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++17
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

TARGET = server

CXX_SRCS = server.cpp
C_SRCS = print_output.c
OBJS = $(CXX_SRCS:.cpp=.o) $(C_SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
