CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iexternal

SRC = src/main.cpp src/video.cpp src/hashtable.cpp src/videostore.cpp src/user.cpp src/engine.cpp
OUT = bin/main

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
