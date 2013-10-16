CPP_FILES := $(wildcard src/*.cpp) $(wildcard src/stdlib/*.cpp)

compile: $(CPP_FILES)
	g++ -Wall -O2 -std=c++11 $(CPP_FILES) -o xigua
	
run-mac: compile
	./xigua examples/hello_world.xigua

run-win: compile
	xigua.exe examples/hello_world.xigua
