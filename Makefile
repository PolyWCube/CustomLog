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

compile-example: $(EXAMPLE_EXECUTE)
compile-benchmark: $(BENCHMARK_EXECUTE)
compile-source: $(SOURCE_LIBRARY)

$(EXAMPLE_EXECUTE): $(SOURCE_LIBRARY) $(OBJECT_DIRECTORY)/example.o
	$(CXX) $(CXX_FLAG) -L$(LIBRARY_DIRECTORY) -l$(LIBRARY) -Wl,-rpath=$(LIBRARY_DIRECTORY) $(OBJECT_DIRECTORY)/example.o -o $(EXAMPLE_EXECUTE)

$(BENCHMARK_EXECUTE): $(SOURCE_LIBRARY) $(OBJECT_DIRECTORY)/benchmark.o
	$(CXX) $(CXX_FLAG) -L$(LIBRARY_DIRECTORY) -l$(LIBRARY) -Wl,-rpath=$(LIBRARY_DIRECTORY) $(OBJECT_DIRECTORY)/benchmark.o -o $(BENCHMARK_EXECUTE)

$(SOURCE_LIBRARY): $(OBJECT_DIRECTORY)/Formatter.o $(OBJECT_DIRECTORY)/Logger.o
	$(CXX) $(CXX_FLAG) $(LIBRARY_FLAG) $(OBJECT_DIRECTORY)/Formatter.o $(OBJECT_DIRECTORY)/Logger.o -o $(SOURCE_LIBRARY)

$(OBJECT_DIRECTORY)/Formatter.o: src/Formatter.hpp src/Formatter.cpp src/FormatCode.hpp
	$(CXX) $(CXX_FLAG) -c src/Formatter.cpp -o $(OBJECT_DIRECTORY)/Formatter.o

$(OBJECT_DIRECTORY)/Logger.o: src/Logger.hpp src/Logger.cpp include/Log.hpp src/Formatter.hpp
	$(CXX) $(CXX_FLAG) -c src/Logger.cpp -o $(OBJECT_DIRECTORY)/Logger.o

$(OBJECT_DIRECTORY)/example.o: example/example.cpp include/Log.hpp
	$(CXX) $(CXX_FLAG) -c example/example.cpp -o $(OBJECT_DIRECTORY)/example.o

$(OBJECT_DIRECTORY)/benchmark.o: example/benchmark.cpp include/Log.hpp
	$(CXX) $(CXX_FLAG) -c example/benchmark.cpp -o $(OBJECT_DIRECTORY)/benchmark.o

clean:
	rm -rf $(BUILD_DIRECTORY)

.PHONY: clean