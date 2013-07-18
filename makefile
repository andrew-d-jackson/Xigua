CPP_FILES := $(wildcard src/*.cpp)

compile: $(CPP_FILES)
	g++ -std=c++11 $(CPP_FILES) -o xigua
	
run-mac: compile
	./xigua examples/print.xi

run-win: compile
	./xigua.exe examples/print.xi
