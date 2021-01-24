CXX = g++
CXXFLAGS = -Wall 

all : app

app : src/main.cpp src/to_audio.cpp src/from_audio.cpp include/to_audio.hpp include/from_audio.hpp 
	$(CXX) src/main.cpp src/to_audio.cpp src/from_audio.cpp -Iinclude -o main

clean : 
	rm main