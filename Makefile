CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -Isrc -lsqlite3
SRCDIRS = src/core/BranchSelector src/core src/config src/util src
OBJDIR = obj
TARGET = fast_git_grep

SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SOURCES)))
VPATH := $(SRCDIRS)

default: 
	make build

build: format
	make $(TARGET)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: format
format:
	find bench include src test -name *.c -o -name *.cc -o -name *.cpp -o -name *.h -o -name *.hh -o -name *.hpp | xargs clang-format -i -style=file --verbose
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)
