########################################################################
#
#	basic Makefile for NvPcomp
#
########################################################################
# Common Defines
########################################################################
CXXFLAGS = -O1 -g3 -Wall -fmessage-length=0
CXX = gcc
########################################################################
# Main program declarations
########################################################################
TARGET = ./bin/NvPcomp
OBJS = ./src/symTable/symNode.o
OBJS += ./src/symTable/symTable.o
INCS =	-I./src/
INCS += -I./src/symTable
INCS += -I./src/logging
INCS += -I./src/test
INCS += -I./src/test/logging
INCS += -I./src/test/unit_test
INCS += -I/usr/include/cppunit
LIBS = -lstdc++
########################################################################
# Test program declarations
########################################################################
TEST_TARGET = ./bin/UnitTest
TEST_OBJS =  ./src/test/unit_test/NvPcompTestSuite.o
TEST_OBJS += ./src/test/unit_test/symNodeTest.o
TEST_OBJS += ./src/test/unit_test/symTableTest.o
TEST_OBJS += $(OBJS)
TEST_LIBS = $(LIBS) -lcppunit -ldl
########################################################################
# Generic Object file compilation
########################################################################
.cpp.o:
	@echo "\nBuilding object file: " $@ "\n"
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@
########################################################################
# Multiples
########################################################################
all: test NvPcomp
test: test_logging UnitTest
########################################################################
# Main Program
########################################################################
NvPcomp: $(OBJS)
	@echo "\nBuilding NvPcomp... \n"
	$(CXX) $(CXXFLAGS) $(INCS) -o $(TARGET) $(OBJS) $(LIBS)
########################################################################
# Test program for Logging
########################################################################
LOG_TEST_OBJS = ./src/test/logging/log_test.o
test_logging: $(LOG_TEST_OBJS)
	@echo "\nbuilding Logger Test...\n"
	$(CXX) $(CXXFLAGS) $(INCS) -o ./bin/log_test $(LOG_TEST_OBJS) $(LIBS)
########################################################################
# UnitTest Executable
########################################################################
UnitTest: $(TEST_OBJS)
	@echo "\nbuilding Test Suite...\n"
	$(CXX) $(CXXFLAGS) $(INCS) -o $(TEST_TARGET) $(TEST_OBJS) $(TEST_LIBS)
########################################################################
# Clean up (more of a clobber really)
########################################################################
clean:
	@echo "\nCleaning up...\n"
	rm -f $(TEST_TARGET) $(TARGET) $(OBJS) $(TEST_OBJS) $(LOG_TEST_OBJS)
