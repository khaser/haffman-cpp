CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++17 -Iinclude
# CXXFLAGS = -g -O0 -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = 

EXE = hw-02_huffman
TESTEXE = run_test
SRCDIR = src
OBJDIR = obj/project
TESTDIR = test
TEST_OBJ_DIR = obj/test

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(wildcard $(TESTDIR)/*.cpp))

all: $(EXE) $(TESTEXE) 

smoke: $(EXE)
	@sh smoke.sh

$(TESTEXE): $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) $(TEST_OBJECTS) $(filter-out $(OBJDIR)/main.o,$(OBJECTS)) -o run_test $(LDFLAGS)
	@./$(TESTEXE)
	@rm $(TESTEXE)

$(TEST_OBJ_DIR)/%.o: $(TESTDIR)/%.cpp | $(TEST_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)
include $(wildcard $(TEST_OBJ_DIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

clean:
	rm -rf $(OBJDIR) $(TEST_OBJ_DIR) $(EXE) $(TESTEXE)

.PHONY: clean all
