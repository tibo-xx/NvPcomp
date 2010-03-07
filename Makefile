#
#	basic Makefile for NvPcomp
#
# Common Defines
CXXFLAGS = -O0 -g3 -Wall -fmessage-length=0
CXX = gcc
# Main program declarations
TARGET = ./bin/NvPcomp
OBJS = ./src/symTable/symNode.o
OBJS += ./src/symTable/symTable.o
INCS =	-I./src/
INCS += -I./src/symTable
INCS += -I./src/test
INCS += -I/usr/include/cppunit
LIBS = -lstdc++
# Test program declarations
TEST_TARGET = ./bin/test
TEST_OBJS =  ./src/test/NvPcompTestSuite.o
TEST_OBJS += ./src/test/symNodeTest.o
TEST_OBJS += $(OBJS)
TEST_LIBS = $(LIBS) -lcppunit -ldl
# Generic Object file compilation
.cpp.o:
	@echo "\nbuilding object file: " $@ "\n"
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@
all: 
# Main Program Make
all: test

# Test Program Make
test: $(TEST_OBJS)
	@echo "\nbuilding Test Suite...\n"
	$(CXX) $(CXXFLAGS) $(INCS) -o $(TEST_TARGET) $(TEST_OBJS) $(TEST_LIBS)
	
clean:
	@echo "\nCleaning up...\n"
	rm -f $(TEST_TARGET) $(TARGET) $(OBJS)
	
	
