CXX       := g++
CXXFLAGS  := -Wall -Wextra -std=c++17 -Iinclude

SRCDIR    := src
OBJDIR    := obj
BINDIR    := bin

SOURCES   := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS   := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

TARGET        := $(BINDIR)/app
DEBUG_TARGET  := $(BINDIR)/app_debug

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/*

run: $(TARGET)
	@if [ -f $(TARGET) ]; then \
		./$(TARGET) input/base-sample.fasta; \
	else \
		echo "Error: Executable $(TARGET) not found. Please build it first."; \
		exit 1; \
	fi