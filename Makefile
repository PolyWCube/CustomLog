ifeq ($(OS),Windows_NT)
	EXECUTE_EXTENSION = .exe
	LIBRARY_EXTENSION = .dll
	LIBRARY_FLAG = -shared
else # Linux/Unix
	EXECUTE_EXTENSION = 
	LIBRARY_EXTENSION = .so
	LIBRARY_FLAG = -shared -fPIC
endif

CXX = g++

CXX_FLAG = -std=c++26 -Wall -Wextra -pedantic -Iinclude -O3

BUILD_DIRECTORY = build
OBJECT_DIRECTORY = $(BUILD_DIRECTORY)/object
LIBRARY_DIRECTORY = $(BUILD_DIRECTORY)/library

LIBRARY = CustomL
EXAMPLE_EXECUTE = $(BUILD_DIRECTORY)/Example$(EXECUTE_EXTENSION)
BENCHMARK_EXECUTE = $(BUILD_DIRECTORY)/Benchmark$(EXECUTE_EXTENSION)
SOURCE_LIBRARY = $(LIBRARY_DIRECTORY)/$(LIBRARY)$(LIBRARY_EXTENSION)

build:
	mkdir -p $(OBJECT_DIRECTORY)
	mkdir -p $(LIBRARY_DIRECTORY)
	${MAKE} compile-source
	${MAKE} compile-example
	${MAKE} compile-benchmark
rebuild:
	${MAKE} clean
	${MAKE} build

compile-source: $(SOURCE_LIBRARY)
compile-example: $(EXAMPLE_EXECUTE)
compile-benchmark: $(BENCHMARK_EXECUTE)

$(EXAMPLE_EXECUTE): $(SOURCE_LIBRARY) $(OBJECT_DIRECTORY)/example.o
	$(CXX) $(CXX_FLAG) -L$(LIBRARY_DIRECTORY) -l$(LIBRARY) -Wl,-rpath=$(LIBRARY_DIRECTORY) $(OBJECT_DIRECTORY)/example.o -o $(EXAMPLE_EXECUTE)

$(BENCHMARK_EXECUTE): $(SOURCE_LIBRARY) $(OBJECT_DIRECTORY)/benchmark.o
	$(CXX) $(CXX_FLAG) -L$(LIBRARY_DIRECTORY) -l$(LIBRARY) -Wl,-rpath=$(LIBRARY_DIRECTORY) $(OBJECT_DIRECTORY)/benchmark.o -o $(BENCHMARK_EXECUTE)

$(SOURCE_LIBRARY): $(OBJECT_DIRECTORY)/Formatter.o $(OBJECT_DIRECTORY)/Logger.o include/Log.hpp
	$(CXX) $(CXX_FLAG) $(LIBRARY_FLAG) $(OBJECT_DIRECTORY)/Formatter.o $(OBJECT_DIRECTORY)/Logger.o -o $(SOURCE_LIBRARY)

$(OBJECT_DIRECTORY)/Formatter.o: source/Formatter.hpp source/Formatter.cpp configuration/Configuration.hpp
	$(CXX) $(CXX_FLAG) -c source/Formatter.cpp -o $(OBJECT_DIRECTORY)/Formatter.o

$(OBJECT_DIRECTORY)/Logger.o: source/Logger.hpp source/Logger.cpp source/Formatter.hpp source/Formatter.cpp
	$(CXX) $(CXX_FLAG) -c source/Logger.cpp -o $(OBJECT_DIRECTORY)/Logger.o

$(OBJECT_DIRECTORY)/example.o: example/example.cpp include/Log.hpp
	$(CXX) $(CXX_FLAG) -c example/example.cpp -o $(OBJECT_DIRECTORY)/example.o

$(OBJECT_DIRECTORY)/benchmark.o: example/benchmark.cpp include/Log.hpp
	$(CXX) $(CXX_FLAG) -c example/benchmark.cpp -o $(OBJECT_DIRECTORY)/benchmark.o

clean:
	rm -rf $(BUILD_DIRECTORY)

.PHONY: clean