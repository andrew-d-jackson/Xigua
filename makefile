CPP_FILES := $(wildcard src/*.cpp) $(wildcard src/stdlib/*.cpp)
TEST_FILES := $(wildcard tests/*.cpp)

compile: $(CPP_FILES)
	g++ -Wall -O2 -std=c++11 $(CPP_FILES) -o xigua

compile-gtest:
	g++ -isystem gtest/include -Igtest -pthread -c gtest/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

compile-test: $(CPP_FILES) compile-gtest
	g++ -DTEST -isystem gtest/include -isystem src -Wall -O2 -std=c++11 $(CPP_FILES) $(TEST_FILES) libgtest.a -o xiguatest

run-mac: compile
	./xigua examples/hello_world.xigua

run-win: compile
	xigua.exe examples/hello_world.xigua

run-test-mac: compile-test
	./xiguatest

run-test-win: compile-test
	xiguatest.exe
