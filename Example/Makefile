CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = project.cpp input.cpp cache.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = project

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)