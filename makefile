CPP_FILES := $(wildcard src/xigua/*.cpp) $(wildcard src/xigua/stdlib/*.cpp)
O_FILES := $(patsubst %.cpp, %.o, $(subst xigua/,, $(subst src/,, $(subst stdlib/,,$(CPP_FILES)))))
TEST_FILES := $(wildcard tests/*.cpp)

compile: $(CPP_FILES)
	g++ -Iinclude -Isrc -Wall -O2 -std=c++11 $(CPP_FILES) -o xigua

shared: $(CPP_FILES)
	g++ -Iinclude -Isrc -Wall -O2 -std=c++11 -c $(CPP_FILES)
	ar -rv libxigua.a $(O_FILES)
	rm $(O_FILES)

compile-gtest: googletest/src/gtest-all.cc
	g++ -isystem googletest/include -Igoogletest -pthread -c googletest/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
	rm gtest-all.o

compile-test: $(CPP_FILES) compile-gtest
	g++ -Iinclude -Isrc -DTEST -isystem googletest/include -isystem src -Wall -O2 -std=c++11 $(CPP_FILES) $(TEST_FILES) libgtest.a -o xiguatest

run-mac: compile
	./xigua examples/hello_world.xigua

run-win: compile
	xigua.exe examples/hello_world.xigua

run-test-mac: compile-test
	./xiguatest

run-test-win: compile-test
	xiguatest.exe

compile-repl: shared examples/repl.cpp
	g++ -Iinclude -Isrc -Wall -O2 -std=c++11 examples/repl.cpp libxigua.a -o repl

