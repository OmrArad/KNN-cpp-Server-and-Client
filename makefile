# compiler
CXX = g++

# compiler flags
CXXFLAGS = -Wall -g -std=c++11

# include directories
#INCLUDES = -I./src/**

# source files
SRC_DIR = cli knnserver knnset

SRC_ALL = $(wildcard src/cli/*.cpp) $(wildcard src/knnserver/*.cpp) $(wildcard src/knnset/*.cpp)

SRCS1 = $(SRC_ALL) src/main/server_main.cpp

SRCS2 = $(SRC_ALL) src/main/client_main.cpp

# object files
OBJS1 = $(SRCS1:.cpp=.o)
OBJS2 = $(SRCS2:.cpp=.o)


all: server.out client.out

server.out: $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $@ $^
client.out: $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean_objs:
	rm -f $(OBJS1) $(OBJS2)
clean:
	rm -f $(OBJS1) $(OBJS2) *.out