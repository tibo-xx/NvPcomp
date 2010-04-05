########################################################################
#
# basic Makefile for AST class library
#
########################################################################
# Tool Defines
########################################################################
CXXFLAGS = -O1 -g3 -Wall -fmessage-length=0
CXX = g++
########################################################################
# Sources
########################################################################
SRC =  	file1.cpp file2.cpp file3.cpp

SRC = 	 src/translation_unit.cpp  src/external_declaration.cpp  src/function_definition.cpp  src/declaration.cpp  src/declaration_list.cpp  src/declaration_specifiers.cpp  src/storage_class_specifier.cpp  src/type_specifier.cpp  src/type_qualifier.cpp  src/struct_or_union_specifier.cpp  src/struct_or_union.cpp  src/struct_declaration_list.cpp  src/init_declarator_list.cpp  src/init_declarator.cpp  src/struct_declaration.cpp  src/specifier_qualifier_list.cpp  src/struct_declarator_list.cpp  src/struct_declarator.cpp  src/enum_specifier.cpp  src/enumerator_list.cpp  src/enumerator.cpp  src/declarator.cpp  src/direct_declarator.cpp  src/pointer.cpp  src/type_qualifier_list.cpp  src/parameter_type_list.cpp  src/parameter_list.cpp  src/parameter_declaration.cpp  src/identifier_list.cpp  src/initializer.cpp  src/initializer_list.cpp  src/type_name.cpp  src/abstract_declarator.cpp  src/direct_abstract_declarator.cpp  src/statement.cpp  src/labeled_statement.cpp  src/expression_statement.cpp  src/compound_statement.cpp  src/statement_list.cpp  src/selection_statement.cpp  src/iteration_statement.cpp  src/jump_statement.cpp  src/expression.cpp  src/assignment_expression.cpp  src/assignment_operator.cpp  src/conditional_expression.cpp  src/constant_expression.cpp  src/logical_or_expression.cpp  src/logical_and_expression.cpp  src/inclusive_or_expression.cpp  src/exclusive_or_expression.cpp  src/and_expression.cpp  src/equality_expression.cpp  src/relational_expression.cpp  src/shift_expression.cpp  src/additive_expression.cpp  src/multiplicative_expression.cpp  src/cast_expression.cpp  src/unary_expression.cpp  src/unary_operator.cpp  src/postfix_expression.cpp  src/primary_expression.cpp  src/argument_expression_list.cpp  src/constant.cpp  src/string.cpp  src/identifier.cpp 

OBJ = $(SRC:.cpp=.o)

TARGET = astlib.a

INCS = -I. -I../include/ 
INCS += -I./src/
INCS += -I./../parser
INCS += -I./../logging

# library paths
LIBS = -lstdc++

.SUFFIXES: .cpp

default: $(TARGET)

.cpp.o:
	$(CXX) $(INCS) $(CCFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	ar rcs $(TARGET) $(OBJ)

depend: dep

dep:
	makedepend -- $(CXXFLAGS) -- $(INCS) $(SRC)

clean:
	rm -f $(OBJ) $(TARGET)
