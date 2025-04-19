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
		./$(TARGET) \
		input/.config \
		input/Covid_Australia.fasta \
		input/Covid_Brazil.fasta \
		input/Covid_India.fasta \
		input/Covid_USA-CA4.fasta \
		input/Covid_Wuhan.fasta \
		input/MERS_2012_KF600620.fasta \
		input/MERS_2014_KY581694.fasta \
		input/MERS_2014_USA_KP223131.fasta \
		input/SARS_2003_GU553363.fasta \
		input/SARS_2017_MK062179.fasta \
		; \
	else \
		echo "Error: Executable $(TARGET) not found. Please build it first."; \
		exit 1; \
	fi