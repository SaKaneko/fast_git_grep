CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2 -Isrc -lsqlite3
SRCDIRS = src/core/SearchManager src/core/BranchSelector src/core src/config src/util src
OBJDIR = obj
TARGET = fast_git_grep

SOURCES := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
OBJECTS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SOURCES)))
VPATH := $(SRCDIRS)

default: 
	make build

build:
	make $(TARGET)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.PHONY: format
format:
	find bench include src test -name *.c -o -name *.cc -o -name *.cpp -o -name *.h -o -name *.hh -o -name *.hpp | xargs clang-format -i -style=file --verbose
APPNAME = fast_git_grep
SPECFILE = $(APPNAME).spec

# RPM build settings
RPMBUILD = rpmbuild
RPMDIR = build
OBJDIR = obj

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET) $(RPMDIR) $(OBJDIR)
	rm -rf ./*.rpm



.PHONY: clean format rpm
rpm: clean $(TARGET)
	mkdir -p $(RPMDIR)/BUILD $(RPMDIR)/RPMS $(RPMDIR)/SOURCES $(RPMDIR)/SPECS $(RPMDIR)/SRPMS
	git ls-files | tar --transform "s,^,$(APPNAME)-1.0/," -czf $(RPMDIR)/SOURCES/$(APPNAME)-1.0.tar.gz -T -
	cp $(SPECFILE) $(RPMDIR)/SPECS/
	$(RPMBUILD) --define "_topdir $(CURDIR)/$(RPMDIR)" -ba $(RPMDIR)/SPECS/$(SPECFILE)
	cp $(RPMDIR)/RPMS/*/*.rpm ./
