# Define the CXX compiler
CXX = g++

# Define the CXX compiler flags
CXXFLAGS = -O3 -Wall -Wextra -std=c++17 -march=native

# Define the source files
SRCS = $(wildcard *.cxx)

# Define the object files
OBJS = $(SRCS:.cxx=.o)

# Define the executable
EXE = lmast2per.x

# Define the all target to build the executable
all: $(EXE)

# Compile the source files to object files
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the object files to the executable
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXE)

# Clean up
clean:
	rm -f $(OBJS) $(EXE)