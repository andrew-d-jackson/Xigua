CPP_FILES := $(wildcard src/*.cpp)

compile: $(CPP_FILES)
	g++ -std=c++11 $(CPP_FILES) -o xigua
	
run: compile
	./xigua.exe
