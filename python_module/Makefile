CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: test

test: language.o moduleTest.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@ -framework Python

language.o: Language.cpp Language.h
	$(CXX) $(CPPFLAGS) $< -c -o $@