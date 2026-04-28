CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O1

TARGET = main
SRCS = main.cpp menu.cpp io.cpp student.cpp

TEST_TARGET = test
TEST_SRCS = test.cpp student.cpp io.cpp

GTEST_FLAGS = -lgtest -lgtest_main -pthread \
              -I/opt/homebrew/include \
              -L/opt/homebrew/lib

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

$(TEST_TARGET): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $(TEST_TARGET) $(GTEST_FLAGS)

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o