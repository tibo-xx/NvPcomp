########################################################################
#
#	basic Makefile for NvPcomp
#
########################################################################
# Tool Defines
########################################################################
CXXFLAGS = -O1 -g3 -Wall -fmessage-length=0
CXX = gcc
LEX = flex++
YACC = bison
LEXFLAGS = -+
########################################################################
# Main program declarations
########################################################################
TARGET = ./bin/NvPcomp
OBJS = ./src/symTable/symNode.o
OBJS += ./src/symTable/symTable.o
OBJS += ./src/parser/parse.o
INCS =	-I./src/
INCS += -I./src/symTable
INCS += -I./src/logging
INCS += -I./src/scanner
INCS += -I./src/parser
INCS += -I./src/test
INCS += -I./src/test/logging
INCS += -I./src/test/unit_test
INCS += -I/usr/include/cppunit
LIBS = -lstdc++
########################################################################
# Sanner and Parser
########################################################################
$SCAN_IN = ./src/scanner/scanner.lex
$SCAN_OUTPUT = ./src/scanner/lex.yy.cc
$PARSE_IN = ./src/parser/parse.y
$PARSE_OUTPUT = ./src/parser/parse.cc ./src/parser/parse.hh
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
.cc.o:
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
# Scanner:
########################################################################
lex.yy.cc: $(SCAN_IN)
	@echo "\nBuilding Scanner...\n"
	$(LEX) $(LEXFLAGS) $<
	mv lex.* ./src/scanner/
########################################################################
# Parser:
########################################################################
parse.cc: $(PARSE_IN)
	@echo "\nBuilding Parser...\n"
	$(YACC) -d -o parse.cc $<
	mv parse.* ./src/parser/
########################################################################
# Clean up (more of a clobber really)
########################################################################
clean:
	@echo "\nCleaning up...\n"
	rm -f $(TEST_TARGET) $(TARGET) $(OBJS) $(TEST_OBJS) $(LOG_TEST_OBJS) $(SCAN_OUTPUT) $(PARSE_OUTPUT) 
