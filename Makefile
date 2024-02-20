CC := g++
CXXFLAGS = -std=c++20
BUILD_DIR := ./build
SRC_DIR := ./src
OBJS := $(BUILD_DIR)/test.o $(BUILD_DIR)/longfloat.o $(BUILD_DIR)/lftfuncs.o
SRCS := $(SRC_DIR)/test.cpp $(SRC_DIR)/longfloat.cpp $(SRC_DIR)/lftfuncs.cpp

all: $(BUILD_DIR) test

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

test: $(BUILD_DIR) $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o test -lgtest -lpthread

run_test: test
	./test

coverage: CXXFLAGS += --coverage
coverage: run_test
	lcov --directory ./build/ --no-recursion -c -o app_coverage.info
	genhtml -o build/coverage/ -t "Application Coverage Report" --legend --num-spaces 4 app_coverage.info

clean:
	rm -rf $(BUILD_DIR)
	rm test
	rm app_coverage.info
