XIGUA_FILES := $(wildcard src/xigua/*.cpp) $(wildcard src/xigua/stdlib/*.cpp)
TEST_FILES := $(wildcard src/tests/*.cpp)
SHELL_FILES := $(wildcard src/shell/*.cpp)

O_FILES := $(patsubst %.cpp, %.o, $(subst xigua/,, $(subst src/,, $(subst stdlib/,, $(XIGUA_FILES)))))

library: $(XIGUA_FILES)
	g++ -Iinclude -Isrc -Wall -O2 -std=c++11 -c $(XIGUA_FILES)
	ar -rv libxigua.a $(O_FILES)

shell: library $(SHELL_FILES)
	g++ -Iinclude -Isrc -Wall -O2 -std=c++11 $(SHELL_FILES) libxigua.a -o xigua

compile-gtest: googletest/src/gtest-all.cc
	g++ -isystem googletest/include -Igoogletest -pthread -c googletest/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

test: compile-gtest library $(TEST_FILES)
	g++ -DTEST -Iinclude -Isrc -isystem googletest/include -Wall -O2 -std=c++11 $(TEST_FILES) libxigua.a libgtest.a -o test

run-shell: shell
	./xigua

run-test: test
	./test

clean:
	rm -f $(wildcard *.o)

travis-ci:
	g++-4.8 -Iinclude -Isrc -Wall -O2 -std=c++11 -c $(XIGUA_FILES)
	ar -rv libxigua.a $(O_FILES)
	g++-4.8 -isystem googletest/include -Igoogletest -c googletest/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o
	g++-4.8 -DTEST -Iinclude -Isrc -isystem googletest/include -Wall -O2 -std=c++11 $(TEST_FILES) libxigua.a libgtest.a -o test