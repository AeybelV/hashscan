CC= g++
CFLAGS= -g -Wall -O3
CPPSTD=c++17
SRC_DIR=src/
BUILD_DIR=build

TARGET=$(BUILD_DIR)/hashscan

all: $(TARGET)


SOURCES=src/util.cpp src/main.cpp 

$(TARGET): $(SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -Ihyperscan/src -lhs -Llib/hyperscan/lib/ -o $(TARGET)

clean:
	rm $(TARGET)
