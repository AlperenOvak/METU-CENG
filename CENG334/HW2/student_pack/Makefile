# Makefile: build hw2 and run the 20-scenario test harness

CXX      = g++
CXXFLAGS = -std=c++11 -Wall -pthread

all: testrun
	@echo
	@echo "================================"
	@echo "  Running Full 20-Scenario Test "
	@echo "================================"
	@./testrun

testrun: hw2.o testrun.o
	$(CXX) $(CXXFLAGS) -o $@ hw2.o testrun.o

hw2.o: hw2.cpp hw2.h monitor.h
	$(CXX) $(CXXFLAGS) -c hw2.cpp

testrun.o: testrun.cpp hw2.h monitor.h
	$(CXX) $(CXXFLAGS) -c testrun.cpp

clean:
	rm -f *.o testrun

