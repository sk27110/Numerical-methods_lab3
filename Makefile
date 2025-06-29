CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -I. -O2

SRCS := coef.cpp main.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)