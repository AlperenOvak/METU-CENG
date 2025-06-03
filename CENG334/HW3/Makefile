# Makefile for histext2fs (Phase 1 + ext2fs_print integration)
#
# Usage:
#   make            # builds the executable histext2fs
#   make clean      # removes object files and the executable

# Compiler settings
CXX      := g++
CC       := gcc
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra
CFLAGS   := -O2 -Wall -Wextra

# Target executable
TARGET := histext2fs

# Source files
SRCS_CPP := histext2fs.cpp
SRCS_C   := ext2fs_print.c

# Corresponding object files
OBJS := histext2fs.o ext2fs_print.o

# Header dependencies
HDRS := ext2fs.h ext2fs_print.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile the C++ source
histext2fs.o: histext2fs.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c histext2fs.cpp -o histext2fs.o

# Compile the C source (provides print_super_block, etc.)
ext2fs_print.o: ext2fs_print.c $(HDRS)
	$(CC) $(CFLAGS) -c ext2fs_print.c -o ext2fs_print.o

clean:
	-@rm -f $(OBJS) $(TARGET)
