CXX = g++
CXXFLAGS = -Wall -std=c++23
SRC = main.cpp Board.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = 2048

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp Board.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)