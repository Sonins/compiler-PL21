CC=g++
CXXFLAGS=

SRC_DIR = src
BUILD_DIR = build
TARGET = compiler
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(subst ${SRC_DIR},${BUILD_DIR},${SOURCES:.cpp=.o})

all: dir $(BUILD_DIR)/$(TARGET)

dir:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(TARGET): ${OBJECTS}
	$(CC) $^ -o $@

${OBJECTS}:
	gcc -c -o $@ $(subst ${BUILD_DIR},${SRC_DIR},$*.cpp)


clean:
	rm -rf ${BUILD_DIR}
