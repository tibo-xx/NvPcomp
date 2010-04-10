########################################################################
#
#	basic Makefile for NvPcomp
#
########################################################################
# Tool Defines
########################################################################
# CXXFLAGS = -O1 -g3 -Wall -fmessage-length=0
CXXFLAGS = -O1 -g3 -Wall -fmessage-length=0 -ansi
CXX = g++
LEX = flex++
#YACC = /home/thibec/usr/share/bison-2.4.1/bin/bison
YACC = bison
LEXFLAGS = -+

ARCH =$(shell /bin/uname -m)

########################################################################
# Main program declarations
########################################################################
TARGET = ./bin/NvPcomp
OBJS = ./src/symTable/symNode.o
OBJS += ./src/symTable/symTable.o
OBJS += ./src/buffer/sourceBuffer.o
OBJS += ./src/scanner/lex.yy.o
OBJS += ./src/parser/parse.o
OBJS += ./src/comLineParser/comLineParser.o
OBJS += ./src/ast/ast.o
OBJS += ./src/ast/astNode.o
OBJS += ./src/tac/tacNode.o
OBJS += ./src/tac/tacTree.o

INCS =	-I./src/
INCS += -I./src/symTable
INCS += -I./src/logging
INCS += -I./src/scanner
INCS += -I./src/parser
INCS += -I./src/comLineParser
INCS += -I./src/ast/
INCS += -I./src/tac/
INCS += -I./src/ast/src/
INCS += -I./src/buffer
INCS += -I./src/test
INCS += -I./src/test/logging
INCS += -I./src/test/unit_test
INCS += -I/usr/include/cppunit

ifeq ($(ARCH),x86_64)
	SHARED_OBJS = ./lib/argtable2-12/lib/libargtable2.a
	INCS += -I./lib/argtable2-12/include
	LIBS = -lstdc++ -lfl -lm -L./src/ast/ -last
else
	
	LIBS = -lstdc++ -lfl -lm -L./src/ast/ -last -largtable2
endif

########################################################################
# Scanner and Parser
########################################################################
SCAN_OUTPUT = ./src/scanner/lex.yy.cc
PARSE_OUTPUT  = ./src/parser/parse.cc ./src/parser/parse.hh 
PARSE_OUTPUT += ./src/parser/location.hh ./src/parser/stack.hh
PARSE_OUTPUT += ./src/parser/position.hh ./src/parser/parse.output

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
.yy.cc.o:
	@echo "\nBuilding object file: " $@ "\n"
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@	
########################################################################
# Multiples
########################################################################
all: parser scanner ast_lib NvPcomp test
test: test_logging UnitTest

########################################################################
# Main Program
########################################################################
NvPcomp: $(OBJS) ./src/main.o
	@echo "\nBuilding NvPcomp... \n"
	$(CXX) $(CXXFLAGS) $(INCS) -o $(TARGET) $(OBJS) $(SHARED_OBJS) ./src/main.o $(LIBS)

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
UnitTest: parser scanner $(TEST_OBJS)
	@echo "\nbuilding Test Suite...\n"
	$(CXX) $(CXXFLAGS) $(INCS) -o $(TEST_TARGET) $(TEST_OBJS) $(SHARED_OBJS) $(TEST_LIBS)

########################################################################
# Scanner:
########################################################################
scanner: ./src/scanner/scanner.lex
	@echo "\nBuilding Scanner...\n"
	$(LEX) $(LEXFLAGS) $<
	mv lex.* ./src/scanner/
	$(CXX) $(CXXFLAGS) $(INCS) -c ./src/scanner/lex.yy.cc -o ./src/scanner/lex.yy.o
########################################################################
# Parser:
########################################################################
parser: ./src/parser/parse.yy
	@echo "\nBuilding Parser...\n"
	$(YACC) --verbose -t -d -o parse.cc $<
	mv parse.* ./src/parser/
	mv *.hh ./src/parser/
	$(CXX) $(CXXFLAGS) $(INCS) -c ./src/parser/parse.cc -o ./src/parser/parse.o
########################################################################
# AST Library
########################################################################
ast_lib:
	@echo "\nMaking AST Library...\n"
	cd src/ast/; make;

########################################################################
# Clean up (more of a clobber really)
########################################################################
clean:
	@echo "\nCleaning up...\n"
	rm -f $(TEST_TARGET) $(TARGET) $(OBJS) $(TEST_OBJS) $(LOG_TEST_OBJS) $(SCAN_OUTPUT) $(PARSE_OUTPUT) ./bin/log_test ./src/*.o;
	cd src/ast/; make clean;
