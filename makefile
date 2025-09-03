# Compiler and flags
CXX = g++         
LDFLAGS = -lreadline

# Target executable name
TARGET = shell

# All source files
SRCS = terminal.cpp ls.cpp pwd.cpp echo.cpp search.cpp cd.cpp systemCommand.cpp history.cpp ioRedirection.cpp pipeline.cpp pinfo.cpp

# Default target: directly compile into final executable
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(SRCS) -o $(TARGET) $(LDFLAGS)

# Clean target: remove the executable
clean:
	rm -f $(TARGET)
