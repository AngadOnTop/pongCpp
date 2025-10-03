CXX = g++
CXXFLAGS = -I/opt/homebrew/include -std=c++17
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = pong

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
