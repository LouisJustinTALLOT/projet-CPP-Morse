CXX = g++
CXXFLAGS = -Wall 

all : app

app : main.cpp to_audio.hpp
	$(CXX) main.cpp to_audio.cpp -o main

clean : 
	rm main