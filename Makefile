BUILD_DIR := ./build
SRC_DIR := ./src

all: $(BUILD_DIR) test.exe

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/longfloat.o: $(SRC_DIR)/longfloat.cpp
	g++ -c $(SRC_DIR)/longfloat.cpp -o $(BUILD_DIR)/longfloat.o

$(BUILD_DIR)/test.o: $(SRC_DIR)/test.cpp
	g++ -c $(SRC_DIR)/test.cpp -o $(BUILD_DIR)/test.o

$(BUILD_DIR)/lftfuncs.o: $(SRC_DIR)/lftfuncs.cpp
	g++ -c $(SRC_DIR)/lftfuncs.cpp -o $(BUILD_DIR)/lftfuncs.o

test.exe: $(BUILD_DIR)/test.o $(BUILD_DIR)/longfloat.o $(BUILD_DIR)/lftfuncs.o
	g++ $(BUILD_DIR)/test.o $(BUILD_DIR)/longfloat.o $(BUILD_DIR)/lftfuncs.o -o test -lgtest -lpthread

clean:
	rm -rf $(BUILD_DIR)
	rm test
